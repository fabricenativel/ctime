#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

const char PB[] = "13";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const long unsigned int STRLEN = 255;

int ml;
int mc;

struct cart
{
    int lig;
    int col;
    char dir;
    char turn;
};
typedef struct cart cart;

void start()
{
    printf("AoC Année %s - Probleme %s \n", YEAR, PB);
    char url[STRLEN];
    strcpy(url, BASE_URL);
    strcat(url, YEAR);
    strcat(url, "/day/");
    strcat(url, PB);
    strcat(url, "\n");
    printf("%s", url);
}

char *get_filename(bool simple)
{
    char *filename = malloc(sizeof(char) * STRLEN);
    strcpy(filename, "input");
    strcat(filename, PB);
    // Possibilité de sélectionner l'input simple depuis la ligne de commande
    if (simple)
    {
        strcat(filename, "simple.txt");
    }
    else
    {
        strcat(filename, ".txt");
    }
    return filename;
}

char next_direction(char current, char next)
{   
    switch (current)
    {
    case '>':
        if (next == '-')
            return '>';
        if (next == '\\')
            return 'v';
        if (next == '/')
            return '^';
        break;
    case '<':
        if (next == '-')
            return '<';
        if (next == '/')
            return 'v';
        if (next == '\\')
            return '^';
        break;
    case '^':
        if (next == '|')
            return '^';
        if (next == '\\')
            return '<';
        if (next == '/')
            return '>';
        break;
    case 'v':
        if (next == '|')
            return 'v';
        if (next == '\\')
            return '>';
        if (next == '/')
            return '<';
        break;
    default:
        printf("BUG\n");
        abort();
        return ' ';
    }
}

bool collision(cart carts[], int nb_carts, int *lig_collision, int *col_collision)
{
    bool seen[ml][mc];
    for (int i = 0; i < ml; i++)
    {
        for (int j = 0; j < mc; j++)
        {
            seen[i][j] = false;
        }
    }
    for (int i = 0; i < nb_carts; i++)
    {
        if (seen[carts[i].lig][carts[i].col])
        {
            *lig_collision = carts[i].lig;
            *col_collision = carts[i].col;
            return true;
        }
        else
        {
            seen[carts[i].lig][carts[i].col] = true;
        }
    }
    return false;
}

char next_turn(char turn)
{
    if (turn == 'L')
        return 'S';
    if (turn == 'S')
        return 'R';
    return 'L';
}

void affiche(char map[200][200], cart carts[], int nb_carts)
{   char lmap[200][200] = {{0}};
    for (int n=0;n<nb_carts;n++)
    {
        lmap[carts[n].lig][carts[n].col] = carts[n].dir;
    }
    for (int i=0;i<ml;i++) 
    {
        for (int j=0;j<mc;j++)
        {
            if (lmap[i][j]==0)
            {printf("%c",map[i][j]);}
            else
            {printf("%c",lmap[i][j]);}
        }
        printf("\n");
    }
}

char set_dir(char current, char turn)
{
    char nd = 'E';
    switch (current)
    {
    case '>':
        if (turn == 'L')
            nd = '^';
        if (turn == 'S')
            nd = '>';
        if (turn == 'R')
            nd = 'v';
        break;
    case '<':
        if (turn == 'L')
            nd = 'v';
        if (turn == 'S')
            nd = '<';
        if (turn == 'R')
            nd = '^';
        break;
    case '^':
        if (turn == 'L')
            nd = '<';
        if (turn == 'S')
            nd = '^';
        if (turn == 'R')
            nd = '>';
        break;
    case 'v':
        if (turn == 'L')
            nd = '>';
        if (turn == 'S')
            nd = 'v';
        if (turn == 'R')
            nd = '<';
    }
    if (nd=='E') {
        printf("BUG dans le traitement d'une intersection");
        abort();
    }
    return nd;
}

void move(cart carts[], char map[200][200], int nb_carts)
{
    for (int i = 0; i < nb_carts; i++)
    {
        switch (carts[i].dir)
        {
        case '>':
            carts[i].col++;
            break;
        case '<':
            carts[i].col--;
            break;
        case '^':
            carts[i].lig--;
            break;
        case 'v':
            carts[i].lig++;
            break;
        default:
            printf("BUG");
            abort();
        }
        if (map[carts[i].lig][carts[i].col] == '+')
        {
            carts[i].dir = set_dir(carts[i].dir,carts[i].turn);
            carts[i].turn = next_turn(carts[i].turn);
        }
        else
        {   
            carts[i].dir = next_direction(carts[i].dir, map[carts[i].lig][carts[i].col]);
        }
    }
}

int solve(bool simple)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    char map[200][200];
    cart carts[100];
    int nb_carts = 0;
    int lig_collision, col_collision;
    int cc=0, nb_tours=0;
    char rc;
    while ((rc=(char)fgetc(fileptr))!=EOF)
    {
        if (rc!='\n') 
        {map[ml][cc++]=rc;}
        else
        {   mc=cc;
            cc=0;
            ml++;
        }

    }
    printf("Taille de la map : %i lignes, %i colonnes \n",ml,mc);
    for (int l = 0; l < ml; l++)
    {
        for (int c = 0; c < mc; c++)
        {
            if (map[l][c] == '>' || map[l][c] == '<' || map[l][c] == '^' || map[l][c] == 'v')
            {
                carts[nb_carts].lig = l;
                carts[nb_carts].col = c;
                carts[nb_carts].dir = map[l][c];
                carts[nb_carts].turn = 'L';
                if (map[l][c] == '>' || map[l][c] == '<')
                    map[l][c] = '-';
                if (map[l][c] == '^' || map[l][c] == 'v')
                    map[l][c] = '|';
                nb_carts++;
            }
        }
    }
    for (int i=0;i<nb_carts;i++){
        printf("Position kart %i (%i,%i) en direction %c sur %c (turn :%c) \n",i,carts[i].lig,carts[i].col,carts[i].dir,map[carts[i].lig][carts[i].col],carts[i].turn);}
    while (!collision(carts, nb_carts, &lig_collision, &col_collision))
    {
        move(carts, map, nb_carts);
        nb_tours++;
        //affiche(map,carts,nb_carts);
        //rc = (char)getchar();
    }
    printf("Collision en (%i,%i) après %i tours \n", col_collision, lig_collision,nb_tours);
    for (int i=0;i<nb_carts;i++){
        printf("Position kart %i (%i,%i) en direction %c sur %c (turn :%c) \n",i,carts[i].lig,carts[i].col,carts[i].dir,map[carts[i].lig][carts[i].col],carts[i].turn);}
    return 0;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    printf("Résultat = %i\n", solve(simple));
}