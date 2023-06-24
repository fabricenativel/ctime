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
    bool moved;
    bool active;
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
    }
    printf("BUG !\n");
    return ' ';
}

int get_cn(int l, int c, cart carts[], int nb_carts)
{
    for (int i = 0; i < nb_carts; i++)
    {
        if (carts[i].lig == l && carts[i].col == c && carts[i].active)
            return i;
    }
    return -1;
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
{
    char lmap[200][200] = {{0}};
    for (int n = 0; n < nb_carts; n++)
    {
        if (carts[n].active) {lmap[carts[n].lig][carts[n].col] = carts[n].dir;}
    }
    for (int i = 0; i < ml; i++)
    {
        for (int j = 0; j < mc; j++)
        {
            if (lmap[i][j] == 0)
            {
                printf("%c", map[i][j]);
            }
            else
            {
                printf("%c", lmap[i][j]);
            }
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
    if (nd == 'E')
    {
        printf("BUG dans le traitement d'une intersection");
        abort();
    }
    return nd;
}

bool move(cart carts[], char map[200][200], int nb_carts, int cart_number, int *lig_collision, int *col_collision, int *other)
{
    switch (carts[cart_number].dir)
    {
    case '>':
        carts[cart_number].col++;
        break;
    case '<':
        carts[cart_number].col--;
        break;
    case '^':
        carts[cart_number].lig--;
        break;
    case 'v':
        carts[cart_number].lig++;
        break;
    default:
        printf("BUG");
        abort();
    }
    if (map[carts[cart_number].lig][carts[cart_number].col] == '+')
    {
        carts[cart_number].dir = set_dir(carts[cart_number].dir, carts[cart_number].turn);
        carts[cart_number].turn = next_turn(carts[cart_number].turn);
    }
    else
    {
        carts[cart_number].dir = next_direction(carts[cart_number].dir, map[carts[cart_number].lig][carts[cart_number].col]);
    }
    for (int n = 0; n < nb_carts; n++)
    {
        if (n != cart_number && carts[cart_number].lig == carts[n].lig && carts[cart_number].col == carts[n].col && carts[n].active)
        {
            *lig_collision = carts[cart_number].lig;
            *col_collision = carts[cart_number].col;
            *other = n;
            return true;
        }
    }
    return false;
}

int solve(bool simple, int *lig_collision, int *col_collision)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    char map[200][200];
    cart carts[100];
    int nb_carts = 0;
    int cc = 0, nb_tours = 0, cn;
    int il = 0, ic = 0;
    char rc;
    bool collision_detected = false;
    int remaining; 
    int other;
    while ((rc = (char)fgetc(fileptr)) != EOF)
    {
        if (rc != '\n')
        {
            map[ml][cc++] = rc;
        }
        else
        {
            mc = cc;
            cc = 0;
            ml++;
        }
    }
    printf("Taille de la map : %i lignes, %i colonnes \n", ml, mc);
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
                carts[nb_carts].moved = false;
                carts[nb_carts].active = true;
                if (map[l][c] == '>' || map[l][c] == '<')
                    map[l][c] = '-';
                if (map[l][c] == '^' || map[l][c] == 'v')
                    map[l][c] = '|';
                nb_carts++;
            }
        }
    }
    printf("Il y a %i karts\n",nb_carts);
    remaining = nb_carts;
    while (remaining != 1)
    {
        while (!collision_detected)
        {
            ic++;
            if (ic == mc)
            {
                ic = 0;
                il++;
                if (il == ml)
                {
                    il = 0;
                    for (int i = 0; i < nb_carts; i++)
                    {
                        carts[i].moved = false;
                    }
                    nb_tours++;
                }
            }
            cn = get_cn(il, ic, carts, nb_carts);
            if (cn != -1 && !carts[cn].moved)
            {
                collision_detected = move(carts, map, nb_carts, cn, lig_collision, col_collision,&other);
                carts[cn].moved = true;
                //affiche(map,carts,nb_carts);
                //rc = getchar();
            }

        }
        carts[cn].active = false;
        carts[other].active =  false;
        remaining -= 2;
        printf("Retrait des karts %i et %i\n",cn,other);
        collision_detected = false;
    }
    for (int i=0;i<nb_carts;i++)
    {
        if (carts[i].active)
        {
            collision_detected = move(carts, map, nb_carts, i, lig_collision, col_collision,&other);
            *lig_collision = carts[i].lig;
            *col_collision = carts[i].col;
            //printf("Survivant (cart %i) en (%i,%i)\n",i,carts[i].col,carts[i].lig);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    bool simple;
    int lig, col;
    start();
    simple = (argc >= 2);
    solve(simple, &lig, &col);
    printf("Résultat : survivant en (%i,%i)\n", col, lig);
}