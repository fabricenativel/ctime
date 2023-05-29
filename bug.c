#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char PB[] = "6";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

struct Point
{   
    int x;
    int y;
};
typedef struct Point Point;


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

char *get_filename() {
    char* filename = malloc(sizeof(char)*STRLEN);
    strcpy(filename,"input");
    strcat(filename,PB) ;
    strcat(filename,"simple.txt") ;
    return filename;
}

int solve() 
{
    long int somme = 0;
    char* filename = get_filename();
    FILE* fileptr = fopen(filename,"r");
    Point* points = malloc(sizeof(Point)*2000);
    char line[STRLEN];
    int num_points,xmax,ymax,max_size = 0;
    int neighbour,x,y;
    while (fgets(line,sizeof(line),fileptr)) 
    {
        sscanf(line,"%i,%i",&points[num_points].x,&points[num_points].y);
        if (points[num_points].x>xmax)
        {
            xmax = points[num_points].x;
        }
        if (points[num_points].y>ymax)
        {
            ymax = points[num_points].y;
        }
        num_points ++;
    }
    int grille[xmax+1][ymax+1];
    num_points--;
    int count_size[num_points];
    printf("Il y a %i points, xmax=%i, ymax=%i\n",num_points,xmax,ymax);
    fclose(fileptr);
    return num_points;
}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}