#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static const char PB[] = "1";
static const char YEAR[] = "2018";
static const char BASE_URL[] = "https://adventofcode.com/";
static const int DEFAULT_LINE_LENGTH = 255;

static void start(void) {
    printf("AoC Année %s - Probleme %s \n",YEAR,PB);
    printf("%s%s/day/%s\n", BASE_URL, YEAR, PB);
}

bool is_in(long int value, long int tab[], long int tab_size) {
    for (int i=0;i<tab_size;i++)
    {
        if (tab[i] == value) return true;
    }
    return false;
}


int solve() {
    long int somme = 0;

    char filename[sizeof(char)*DEFAULT_LINE_LENGTH];
    snprintf(filename, DEFAULT_LINE_LENGTH,  "input%s.txt", PB);

    FILE* fileptr = fopen(filename,"r");
    char line[DEFAULT_LINE_LENGTH];
    long int size = 0;
    long int tab[200000];
    while (true) {
    while (fgets(line,sizeof(line),fileptr)) {
        somme += atoi(line);
        if (size>0 && is_in(somme,tab,size))
            {return somme;}
        else
            {tab[size++]=somme;
            }
    }
    rewind(fileptr);
    }
    fclose(fileptr);
}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}
