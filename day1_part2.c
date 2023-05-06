#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char PB[] = "1";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

int start() {
    printf("AoC Année %s - Probleme %s \n",YEAR,PB);
    char url[STRLEN] ;
    strcpy(url,BASE_URL);
    strcat(url,YEAR);
    strcat(url,"/day/");
    strcat(url,PB);
    strcat(url,"\n");
    printf("%s",url);
}

bool is_in(long int value, long int tab[], long int tab_size) {
    for (int i=0;i<=tab_size;i++) 
    {
        if (tab[i] == value) return true;
    }
    return false;
}

char *get_filename() {
    char* filename = malloc(sizeof(char)*STRLEN);
    strcpy(filename,"input");
    strcat(filename,PB) ;
    strcat(filename,".txt") ;
    return filename;
}



int solve() {
    long int somme = 0;
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    char line[STRLEN];
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