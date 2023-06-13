#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

const char PB[] = "10";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

struct points
{
    int x;
    int y;
    int vx;
    int vy;
};
typedef struct points points;

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

bool not_in(int x, int y, points pts[], int nb)
{
    for (int i = 0; i < nb; i++)
    {
        if (x == pts[i].x && y == pts[i].y)
        {
            return false;
        }
    }
    return true;
}

void get_lim(points *pts, int nb, int* xmin, int *xmax, int *ymin, int *ymax)
{
    *xmin = INT32_MAX;
    *xmax = INT32_MIN;
    *ymin = INT32_MAX;
    *ymax = INT32_MIN;
    for (int i = 0; i < nb; i++)
    { 
        if (pts[i].x < *xmin) *xmin = pts[i].x;
        if (pts[i].x > *xmax) *xmax = pts[i].x;
        if (pts[i].y < *ymin) *ymin = pts[i].y;
        if (pts[i].y > *ymax) *ymax = pts[i].y;
    }
}

void move(points *pts,int nb)
{
    for (int i = 0; i < nb; i++)
    { 
        pts[i].x += pts[i].vx;
        pts[i].y += pts[i].vy;
    }
}

bool alone(points* pts, int nb)
{
    for (int i = 0; i < nb; i++)
    {
        if  (
            not_in(pts[i].x-1,pts[i].y-1,pts,nb) &&
            not_in(pts[i].x-1,pts[i].y,pts,nb) &&
            not_in(pts[i].x-1,pts[i].y+1,pts,nb) &&
            not_in(pts[i].x,pts[i].y-1,pts,nb) &&
            not_in(pts[i].x,pts[i].y+1,pts,nb) &&
            not_in(pts[i].x+1,pts[i].y-1,pts,nb) &&
            not_in(pts[i].x+1,pts[i].y,pts,nb) &&
            not_in(pts[i].x+1,pts[i].y+1,pts,nb)
            )
            {return true;}
    }
    return false;
    
}

void display(points *pts, int nb)
{
    int xmin,xmax,ymin,ymax;
    get_lim(pts, nb, &xmin, &xmax, &ymin, &ymax);
    for (int y = ymin; y<=ymax;y++)
    {
        for (int x=xmin; x<=xmax; x++)
        {
        if (not_in(x,y,pts,nb))
        {
            printf(".");
        }
        else
        {
            printf("#");
        }
        }
        printf("\n");
    }
}


int solve(bool simple)
{
    char *filename = get_filename(simple);
    FILE *fileptr = fopen(filename, "r");
    int rx, ry, rvx, rvy;
    int nb_points = 0;
    int wait = 0;
    points pts[10000];
    while (fscanf(fileptr, "position=<%i,  %i> velocity=< %i, %i>\n", &rx, &ry, &rvx, &rvy) == 4)
    {
        pts[nb_points].x = rx;
        pts[nb_points].y = ry;
        pts[nb_points].vx = rvx;
        pts[nb_points].vy = rvy;
        nb_points++;
    }
    while (alone(pts, nb_points))
    {
        move(pts, nb_points);
        wait++;
    }
    display(pts, nb_points);
    return wait;
}

int main(int argc, char *argv[])
{
    bool simple;
    start();
    simple = (argc >= 2);
    printf("Temps d'attente = %i\n",solve(simple));
}