#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


const char PB[] = "2";
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

char *get_filename() 
{
    char* filename = malloc(sizeof(char)*STRLEN);
    strcpy(filename,"input");
    strcat(filename,PB) ;
    strcat(filename,".txt") ;
    return filename;
}

int *get_count(char* word, int* count)
{  for (int i=0;i<strlen(word);i++)
    {
        count[(int)word[i]-(int)'a']++;
    }
}

bool is_in(int value, int tab[], int tab_size) {
    for (int i=0;i<tab_size;i++) 
    {
        if (tab[i] == value) return true;
    }
    return false;
}

int solve() {
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    char line[STRLEN];
    int twice = 0, threetimes = 0;
    int count[26] = {0};
    while (fgets(line,sizeof(line),fileptr)) {
        get_count(line,count);
        if (is_in(2,count,26)) twice++;
        if (is_in(3,count,26)) threetimes++;
        for (int i=0;i<26;i++) 
        {
            count[i]=0;
        }
    }
    fclose(fileptr);
    return twice*threetimes;
}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}