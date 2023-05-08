#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define PB  "3"
#define YEAR  "2018"
#define BASE_URL  "https://adventofcode.com/"
#define STRLEN  255

struct Rectangle
{
    int x;
    int y;
    int lx;
    int ly;
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


int solve() {
    long int somme = 0;
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    char line[STRLEN];
    struct Rectangle* rectangles = malloc(sizeof(struct Rectangle)*2000);
    int tid;
    int num = 0, nover = 0;
    int xmax=0, ymax= 0;
    int claims[1000][1000] = {{0}};
    bool is_ok = true;
    bool found = false;
    while (fgets(line,sizeof(line),fileptr)) 
    {
        sscanf(line,"#%i @ %i,%i: %ix%i",&tid,&rectangles[num].x,&rectangles[num].y,&rectangles[num].lx,&rectangles[num].ly);
        num ++;
    }
    fclose(fileptr);
    for (int i=0;i<num;i++)
    {
        for (int dx=rectangles[i].x;dx<rectangles[i].x+rectangles[i].lx;dx++)
        {
            for (int dy=rectangles[i].y;dy<rectangles[i].y+rectangles[i].ly;dy++)
            {
                claims[dx][dy]++;
            }
        }
    }
    num = 0;
    /* C'est le bon rectangle si la partie couverte ne contient que des 1*/
    while (!found) 
    {   
        is_ok = true;
        for (int dx=rectangles[num].x;dx<rectangles[num].x+rectangles[num].lx;dx++)
        {
            for (int dy=rectangles[num].y;dy<rectangles[num].y+rectangles[num].ly;dy++)
                {
                if (claims[dx][dy]>1) is_ok=false;
                }
        }
        if (is_ok) found=true;
        num++;
    }
    return num;
}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}