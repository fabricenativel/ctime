#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char PB[] = "7";
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

int char_index(char c)
{
    return (int)(c)-65;
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

char get_next(char task[26][26])
{
    char current = '['; // le caractère [ est celui qui suit Z
    for (int i = 0; i < 26; i++)
    {
        if (strlen(task[i]) == 0)
        {
            if (current > (char)(i + 65))
            {
                current = (char)(i + 65);
            }
        }
    }
    return current;
}

// retire le caractère car de la chaine str
bool remove_char(char *str, char car)
{
    unsigned int slen = strlen(str), idx = 0;
    bool found = false;
    while (idx < slen && !found)
    {
        if (str[idx] == car)
        {
            found = true;
        }
        else
        {
            idx++;
        }
    }
    if (!found)
    {
        return false;
    }
    else
    {
        for (int i=idx;i<slen-1;i++)
        {
            str[i]=str[i+1];
        }
        str[slen-1]='\0';
        return true;
    }
}

/* Codage des sous forme d'une chaine de caractères qui vaut :
- "[" si la tâche est terminée (caratère situé juste après "Z" en ASCII)
- "" si la tâche peut être effectuée
- la liste des tâches à effectuée avant (eg "RDE")
*/
char* solve(bool simple)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    char line[STRLEN];
    char t1, t2;
    char task[26][26] = {{""}};
    char to_do;
    char *rep = malloc(sizeof(char) * 26); //La fonction renvoie une chaine de caractère, il faut donc allouer sur le tas et pas localement
    unsigned int clen;
    printf("Fichier d'input : %s\n", filename);
    while (fgets(line, sizeof(line), fileptr))
    {
        int ok = sscanf(line, "Step %c must be finished before step %c can begin.", &t1, &t2);
        if (ok != 0)
        {
            clen = strlen(task[char_index(t2)]);
            task[char_index(t2)][clen] = t1;
            task[char_index(t2)][clen + 1] = '\0';
        }
    }
    for (int tc=0;tc<26;tc++)
    {
        to_do = get_next(task);
        strcpy(task[char_index(to_do)],"]");
        rep[tc] = to_do;
        for (int i=0;i<26;i++)
        {
            remove_char(task[i],to_do);
        }
    }
    return rep;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    char* rep = solve(simple);
    printf("Réponse : %s \n", rep);
}