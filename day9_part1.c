#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

const char PB[] = "9";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

// Liste circulaire doublement chainées
struct node
{
    struct node* previous;
    int value;
    struct node* next;
};
typedef struct node node;


node* make_circle(int val)
{
    node *new_node = malloc(sizeof(node));
    new_node->previous =new_node;
    new_node->value=val;
    new_node->next=new_node;
    return new_node;
}

// Dans les règles on ajoute toujours à droite > le cas d'un ajout à gauche de la position courante n'est pas traité
node* add_node(node* current_node,int val,int offset)
{
    node *new_node = malloc(sizeof(node));
    new_node->value = val;
    for (int i=0;i<offset;i++)
    {   
        current_node = current_node->next;
    }
    new_node->next = current_node->next;
    new_node->previous = current_node;
    current_node->next->previous = new_node;
    current_node->next = new_node;
    return new_node;
}

// Idem on enlève toujours à gauche de la position courante
node* remove_node(node *current_node, int offset, unsigned int* points)
{
    for (int i=0;i<offset;i++)
    {   
        current_node = current_node->previous;
    }
    (current_node->next)->previous = current_node->previous;
    (current_node->previous)->next = current_node->next;
    *points = current_node->value;    
    return current_node->next;
}

void disp_circle(node* current_node)
{
    int start_value = current_node->value; // Que des valeurs différents on arrête l'affichage si on rencontre la même valeur
    printf("(%i) ",start_value);
    while ((current_node->next)->value != start_value)
    {
        current_node = current_node->next;
        printf("%i ",current_node->value);
    }
    printf("\n");
}

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

node* play_game(node* circle,int nb_players,int nb_marbles, unsigned int* max_points)
{
    int current_player = 1;
    unsigned int points[nb_players+1];
    unsigned int inc  = 0;
    for (int i=1;i<nb_players+1;i++)
    {
        points[i] = 0;
    }
    for (int i=1; i<nb_marbles+1; i++)
    {   
        // Cas normal : ajout du pion 1 cran après le pion courant
        if (i%23 != 0)
        {
            circle = add_node(circle,i,1);
        }
        else
        // Cas gains de points
        {   
            circle = remove_node(circle,7,&inc);
            points[current_player] += i;
            points[current_player] += inc;
            if (points[current_player] > *max_points)
            {
                *max_points = points[current_player];
            }
        }
        current_player++;
        if (current_player>nb_players)
        {
            current_player = 1;
        }
    }

    return circle;
}

int solve(bool simple)
{
    char* filename = get_filename(simple);
    FILE* fileptr = fopen(filename,"r");
    node* circle;
    unsigned int max_pts =0;
    int nb_players, nb_marbles;
    fscanf(fileptr,"%d players; last marble is worth %d points",&nb_players,&nb_marbles);
    circle = make_circle(0);
    circle = play_game(circle,nb_players,nb_marbles,&max_pts);
    return max_pts;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    unsigned int rep = solve(simple);
    printf("Réponse : %i \n", rep);
}