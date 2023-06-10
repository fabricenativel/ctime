#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

const char PB[] = "8";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;


// Prend en argument un pointeur sur un fichier (contenant des entiers séparés par des espaces) et renvoie un tableau contenant les n premiers entiers 
int* read_int(FILE* fileptr, int n)
{   
    int *val = malloc(sizeof(int)*n);
    for (int i=0;i<n;i++)
    {
        fscanf(fileptr,"%d ",&val[i]);
    }
    return val;
}

int sum_int(int * val, int size)
{   
    int s = 0;
    for (int i = 0;i<size;i++)
    {
        s += val[i];
    }
    return s;
}

unsigned int node_value(FILE *fileptr)
{
    unsigned int nv = 0;
    int* header = malloc(sizeof(int)*2);
    header = read_int(fileptr,2); //header[0] : nb fils et header[1] : nb meta
    int* meta_data = malloc(sizeof(int)*header[1]);
    if (header[0]==0) // A noeud sans fils a pour valeur la somme de ses meta data
    {   
        meta_data = read_int(fileptr,header[1]);
        nv = sum_int(meta_data,header[1]);
        return nv;
    }
    else // Sinon on calcule la valeur de chacun des fils
    {   
        int* child_values = malloc(sizeof(int)*header[1]);
        for (int i=0; i<header[0];i++)
        {
            child_values[i] = node_value(fileptr);
        }
        meta_data = read_int(fileptr,header[1]); //on somme les valeurs des noeuds fils (les meta data sont les index des noeuds à sommer)
        for (int i=0;i<header[1];i++)
        {
            if (1<=meta_data[i] && meta_data[i]<=header[0])
            {
                nv += child_values[meta_data[i]-1];
            }
        }
        return nv;
    }
}

// Calcul récursivement la somme des meta données
unsigned int sum_meta(FILE *fileptr)
{
    unsigned int sm = 0;
    int* header = malloc(sizeof(int)*2);
    header = read_int(fileptr,2); //header[0] : nb fils et header[1] : nb meta
    int* meta_data = malloc(sizeof(int)*header[1]);
    if (header[0] == 0)
    {
        meta_data = read_int(fileptr,header[1]);
        sm = sum_int(meta_data,header[1]);
        return sm;
    }
    else
    {
        for (int i=0; i<header[0];i++)
        {
            sm += sum_meta(fileptr);
        }
        meta_data = read_int(fileptr,header[1]);
        return sm + sum_int(meta_data,header[1]);
    }
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

int solve(bool simple)
{
    char* filename = get_filename(simple);
    FILE* fileptr = fopen(filename,"r");
    return node_value(fileptr);
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    int rep = solve(simple);
    printf("Réponse : %i \n", rep);
}