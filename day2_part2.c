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

int *get_count(char* word, int count[])
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

int max(int val1, int val2) {
    if (val1 > val2)
    {
        return val1;
    }
    else
    {
        return val2;
    }
}


int diff_count(char *word1, char *word2) {
    int diff = 0;
    for (int i=0;i<max(strlen(word1),strlen(word2));i++)
    {
        if (word1[i]!=word2[i])
        {
            diff++;
        }
    }
    return diff;
}

char *common(char *word1,char *word2) {
    char *id = malloc(sizeof(sizeof(char))*(max(strlen(word1),strlen(word2))+1));
    int idx = 0;
    for (int i=0;i<max(strlen(word1),strlen(word2));i++)
    {
        if (word1[i]==word2[i])
        {
            id[idx] = word1[i];
            idx++;
        }
    }
    id[idx] = '\0';
    return id;
}

char *solve() {
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    char line[STRLEN];
    int nb_words = 0;
    /* D'après l'input on sait qu'il y a moins de 300 mots */
    char word[300][255];
    while (fgets(line,sizeof(line),fileptr)) 
    {
        strcpy(word[nb_words],line);
        nb_words++;
    }
    fclose(fileptr);
    for (int i=0;i<nb_words;i++) 
    {
        for (int j=i+1;j<nb_words;j++)
        {
            if (diff_count(word[i],word[j])==1)
            {
                return common(word[i],word[j]);
            }
        }
    }
    return "Bug";
}

int main() {
    start();
    char *rep = solve();
    printf("Réponse : %s \n",rep);
    
}