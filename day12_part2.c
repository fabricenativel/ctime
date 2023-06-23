#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

const char PB[] = "12";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const long unsigned int STRLEN = 255;


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

int encode(char old[5])
{
    int res = 0;
    for (int i=0;i<5;i++)
    {
        if (old[4-i]=='#')
        { res+=(int)pow(2,i);}
    }
    return res;
}

char* get_five(char * state,long unsigned int pos)
{
    char *rep = malloc(sizeof(char)*5);
    for (long unsigned int i=0;i<5;i++)
    {
        rep[i] = state[pos-2+i];
    }
    return rep;
}


int solve(bool simple)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    char pots[1000];
    char state[100000000000];
    char next_state[100000000000];
    int res = 0;
    int offset=-2;
    char evolution[32];
    char old[5];
    char new;
    state[0] = '.';
    state[1] = '.';
    for (int i=0;i<32;i++)
    {
        evolution[i] = '.';
    }
    // Lecture état initial
    fscanf(fileptr,"initial state: %s\n",pots);
    strcat(state,pots);
    strcat(state,"..");
    // Lecture des evolutions des motifs
    while (fscanf(fileptr,"%s => %c\n",old,&new)==2)
    {   
        evolution[encode(old)] = new;
    }
    // Evolutions 
    evolution[0] = '.';
    //printf("Etat 0 : %s\n",state);
    for (long unsigned int nb_evol =0;nb_evol<50000000000;nb_evol++)
    {   next_state[0] = '.';
        next_state[1] = '.';
        for (long unsigned int i=2;i<strlen(state)-2;i++)
        {
            next_state[i]  = evolution[encode(get_five(state,i))];
        }
        strcat(next_state,"..");
        //printf("Etat %i : %s\n",nb_evol+1,next_state);
        strcpy(state,"..");
        strcat(state,next_state);
        strcat(state,"..");
        offset = offset-2;
    }
    for (int i=0;i<(int)strlen(state);i++)
    {
        if (state[i]=='#')
        {
            res = res+ i+offset;
        }
    }
    return res;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    printf("Résultat = %i\n",solve(simple));
}