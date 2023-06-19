#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static const char PB[] = "1";
static const char YEAR[] = "2018";
static const char BASE_URL[] = "https://adventofcode.com/";
static const int DEFAULT_LINE_LENGTH = 255;

static void start(void) {
    printf("AoC Année %s - Probleme %s\n", YEAR, PB);
    printf("%s%s/day/%s\n", BASE_URL, YEAR, PB);
}

static long int solve(void) {
    char filename[sizeof(char)*DEFAULT_LINE_LENGTH];
    snprintf(filename, DEFAULT_LINE_LENGTH,  "input%s.txt", PB);
    FILE* fileptr = fopen(filename,"r");

    long int somme = 0;
    char line[DEFAULT_LINE_LENGTH];
    while (fgets(line,sizeof(line),fileptr)) {
        somme += atoi(line);
    }
    fclose(fileptr);

    return somme;
}

int main(void) {
    start();
    printf("Réponse : %li \n", solve());
}
