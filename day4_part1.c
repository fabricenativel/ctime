#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define PB  "4"
#define YEAR  "2018"
#define BASE_URL  "https://adventofcode.com/"
#define STRLEN  255

struct Entry
{   
    int guard;
    int year;
    int month;
    int day;
    int hour;
    int min;
    char* event;
};


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

int indexof(int value, int tab[], int tab_size) {
    for (int i=0;i<tab_size;i++) 
    {
        if (tab[i] == value) return i;
    }
    return -1;
}

int somme(int tab[],int tab_size) {
    int s = 0;
    for (int i=0;i<tab_size;i++)
    {
        s += tab[i];
    }
    return s;
}

int indexmax(int tab[], int tab_size)
{
    int i_max =0, current_max =0;
    for (int i=0;i<tab_size;i++)
    {
        if (tab[i]>current_max)
        {
            current_max=tab[i];
            i_max=i;
        }
    }
    return i_max;
}

/* qsort est dans la lib C, il faut écrire la fonction de comparaison en respectant la spécification*/
int compare(const void *event1, const void *event2)
{
    int year1 = ((struct Entry *)event1) -> year;
    int year2 = ((struct Entry *)event2) -> year;
    int month1 = ((struct Entry *)event1) -> month;
    int month2 = ((struct Entry *)event2) -> month;
    int day1 = ((struct Entry *)event1) -> day;
    int day2 = ((struct Entry *)event2) -> day;
    int hour1 = ((struct Entry *)event1) -> hour;
    int hour2 = ((struct Entry *)event2) -> hour;
    int min1 = ((struct Entry *)event1) -> min;
    int min2 = ((struct Entry *)event2) -> min;
    if (year1 != year2) 
        {return (year1>year2) ? 1 : -1;}
    else
    {
        if (month1 != month2)
        {return (month1>month2) ? 1 : -1;}
        else
        {
            if (day1 != day2)
            {return (day1>day2) ? 1: -1;}
            else
            {
                if (hour1 != hour2)
                {return (hour1>hour2) ?1 :-1;}
                else
                {return (min1>min2) ?1 : -1;}
            }
        }
    }

}

int solve() {
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    char line[STRLEN];
    struct Entry* entries = malloc(sizeof(struct Entry)*2000);
    int guards[100][60] = {{0}};
    int sleep_time[100] = {0};
    int guardnumber[100] = {0};
    int num = 0, current_guard_number, current_minute, gnumber=0;
    int opti_guard, opti_min;
    bool current_guard_state;
    char ev[80];
    while (fgets(line,sizeof(line),fileptr)) 
    {  
        entries[num].event = malloc(sizeof(char)*80);
        sscanf(line,"[%d-%d-%d %d:%d] %80[^\n]",&entries[num].year,&entries[num].month,&entries[num].day,&entries[num].hour,&entries[num].min,ev);
        strcpy(entries[num].event,ev);
        num ++;
        if (sscanf(ev,"Guard #%i begins shift",&current_guard_number)!=EOF)
        {
            if (indexof(current_guard_number,guardnumber,100)==-1)
            {
                guardnumber[gnumber]=current_guard_number;
                gnumber++;
            }
        }
    }
    fclose(fileptr);
    qsort((void*)entries,num,sizeof(entries[0]),compare);
    for (int i=0;i<num;i++)
    {
        if (strcmp(entries[i].event,"falls asleep")==0)
        {
            current_minute = entries[i].min;
        }
        else if (strcmp(entries[i].event,"wakes up")==0)
        {  
            for (int t=current_minute;t<entries[i].min;t++)
            {
                guards[indexof(current_guard_number,guardnumber,gnumber)][t]++;
            }
            current_minute = entries[i].min;
        }
        else 
        {
            sscanf(entries[i].event,"Guard #%i begins shift",&current_guard_number);
            current_guard_state = true;
            current_minute = 0;
        }
    }
    free(entries);
    for (int i=0;i<gnumber;i++)
    {   
        sleep_time[i] = somme(guards[i],60);   
    }
    opti_guard = guardnumber[indexmax(sleep_time,100)];
    opti_min = indexmax(guards[indexmax(sleep_time,100)],60);
    return opti_guard*opti_min;
}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}