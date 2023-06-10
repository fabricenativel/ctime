#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char PB[] = "8";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;


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
    return 0;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    int rep = solve(simple);
    printf("Réponse : %i \n", rep);
}