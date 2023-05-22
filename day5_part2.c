#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

const char PB[] = "5";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

int start()
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

char *get_filename()
{
    char *filename = malloc(sizeof(char) * STRLEN);
    strcpy(filename, "input");
    strcat(filename, PB);
    strcat(filename, ".txt");
    return filename;
}

bool to_remove(char char1, char char2)
{
    int asc1 = (int)(char1);
    int asc2 = (int)(char2);
    return (abs(asc1 - asc2) == 32);
}

void extrait(char* source,int idx)
{
    char *pread = source,  *pwrite = source;
    int i = 0;
    while (*pread)
    {
        if (i!=idx && i!=idx+1)
        {
            *pwrite = *pread;
            pwrite++;
        }
        pread++;
        i++;
    }
    *pwrite = '\0';
}

void remove_all(char *source, char caractere)
{
    char *pread = source, *pwrite = source;
    while (*pread)
    {
        if (*pread != caractere && *pread != tolower(caractere))
        {
            *pwrite = *pread;
            pwrite++;
        }
        pread++;
    }
    *pwrite = '\0';
}

int solve()
{
    char *filename = get_filename();
    FILE *fileptr = fopen(filename, "r");
    char *polymer = malloc(sizeof(char) * 60000);
    bool tr = false;
    int idx = 0;
    int current_min = 50000;
    for (int cindex = 65; cindex < 91; cindex++)
    {
        fgets(polymer, 60000, fileptr); // Il y a un retour chariot à la fin de l'input, donc 1 de plus à la longueur attendue (on enlève à la fin)
        rewind(fileptr);
        idx = 0;
        remove_all(polymer, (char)(cindex));
        while (idx < strlen(polymer))
        {
            while (!tr && idx < strlen(polymer)) // tr est un booléen qui détecte si les 2 caractères situés en position idx et idx+1 doivent être supprimés de la chaine
            {
                tr = to_remove(polymer[idx], polymer[idx++]); // pas très joli mais pratique : on utilise idx++ pour incrémenter et utiliser en même temps la nouvelle valeur
            }
            if (tr)
            {
                extrait(polymer, idx - 1);
                idx = 0;
                tr = false;
            }
        }
        printf("Enlever tous les %c donne une taille %li\n",(char)(cindex),strlen(polymer));
        if (strlen(polymer) < current_min)
        {
            current_min = strlen(polymer);
        }
    }
    fclose(fileptr);
    return current_min - 1;
}

int main()
{
    start();
    int rep = solve();
    printf("Réponse : %i \n", rep);
}