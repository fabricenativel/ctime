#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct worker
{
    int task; // -1  si ouvrier dispo
    int start_time;
    int end_time;
};
typedef struct worker worker;


const char PB[] = "7";
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

char* available_task(char task[26][26], bool given[26])
{
    char *available = malloc(sizeof(char)*26);
    int nb_av = 0;
    for (int i = 0; i < 26; i++)
    {
        if (strlen(task[i]) == 0 && !given[i])
        {
            available[nb_av++]=(char)(i+65);
        }
    }
    //available[nb_av]='\0';
    return available;
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

// Renvoie le temps nécessaire pour accomplir une tâche
unsigned int calc_time(char c)
{
    return  (int)(c) - 4;
}


// Renvoie le numéro du premier worker disponible et -1 si tous occupé
int available_worker(worker workers[5])
{
    for (int i=0;i<5;i++)
    {
        if (workers[i].task==-1)
        {
            return i;
        }
    }
    return -1;
}

unsigned int inc_time(worker workers[5],int ctime)
{
    for (int i=0;i<5;i++)
    {
        if (workers[i].end_time == ctime)
        {
            workers[i].task = -1;
        }
    }
    return ctime+1;
}

/* Codage des sous forme d'une chaine de caractères qui vaut :
- "[" si la tâche est terminée (caratère situé juste après "Z" en ASCII)
- "" si la tâche peut être effectuée
- la liste des tâches à effectuée avant (eg "RDE")
*/
int solve(bool simple)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    char line[STRLEN];
    char t1, t2;
    char task[26][26] = {{""}};
    bool given[26] = {false};
    worker workers[5]; 
    unsigned int ctime = 0;
    unsigned int clen;
    int nw=0, ntask_done = 0;
    char *nt;
    for (int i=0;i<5;i++)
    {
        workers[i].task = -1;
        workers[i].start_time = -1;
        workers[i].end_time = -1;
    }
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
    // Tant qu'il y a des tâches dispo et des travailleurs dispos attribuer, sinon incrémenter le temps ...
    nw = available_worker(workers);
    nt = available_task(task,given);
    while (ntask_done<26)
    {
    while (strcmp(nt,"")!=0 && nw!=-1)
    {
        printf("Seconde %i : Attribution de %c à worker %i temps : %i\n",ctime,nt[0],nw,calc_time(nt[0]));
        given[char_index(nt[0])] = true;
        workers[nw].task = nt[0];
        workers[nw].start_time = ctime;
        workers[nw].end_time = ctime + calc_time(nt[0]);
        nw = available_worker(workers);
        remove_char(nt,nt[0]);
    }
    while ((strcmp(nt,"")==0 || nw==-1) && ntask_done<26)
    {
        ctime++;
        for (int i=0;i<5;i++)
        {
            if (workers[i].end_time == ctime)
            {   printf("Seconde %i : Fin de la tâche %c libération worker %i \n",ctime,workers[i].task,i);
                ntask_done++;
                for (int j=0;j<26;j++)
                {
                 remove_char(task[j],workers[i].task);
                }
                workers[i].task = -1;
                workers[i].start_time = -1;
                workers[i].end_time = -1;
                nt = available_task(task,given);
                nw = available_worker(workers);
            }
        }
    }
    }
    return ctime;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    int rep = solve(simple);
    printf("Réponse : %i \n", rep);
}