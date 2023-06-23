#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

const char PB[] = "11";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;
const int SIZE = 301; 

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

int cell_value(int sn, int x, int y)
{
    int value = ((x+10)*y + sn)*(x+10);
    value = ((value/100)%10)-5;
    return value;

}

int square_value(int grid[SIZE][SIZE], int x, int y, int square_size )
{
    int total = 0;
    for (int i=0;i<square_size;i++)
    {
        for (int j=0;j<square_size;j++)
        {
            total += grid[y+i][x+j];
        }
    }
    return total;
}

int get_max(int grid[SIZE][SIZE],int *xmax, int *ymax, int square_size)
{
    int cmax = 0;
    for (int y=1;y<SIZE-square_size+1;y++)
    {
        for (int x=1;x<SIZE-square_size+1;x++)
        {
            if (square_value(grid, x, y,square_size)>cmax)
            {
                cmax = square_value(grid, x, y,square_size);
                *xmax = x;
                *ymax = y;
            }
        }
    }
    return cmax;
}

void solve(int serial_number,int *xmax, int *ymax)
{   
    int omax = 0; 
    int ox, oy, smax;
    int grid[SIZE][SIZE];
    for (int y=1;y<SIZE;y++)
    {
        for (int x=1;x<SIZE;x++)
        {
            grid[y][x] = cell_value(serial_number,x,y);
        }
    }
    for (int ss=1;ss<300;ss++)
    { printf("Test des carrés de taille %i \n",ss);
     if (get_max(grid,xmax,ymax,ss)>omax)
     {
        omax = get_max(grid,xmax,ymax,ss);
        ox = *xmax;
        oy = *ymax;
        smax =ss;
     };
    }
    printf("Max  atteint en (%i,%i,%i) : %i\n",ox,oy,smax,omax);
}

int main(int argc, char *argv[])
{
    int serial_number;
    int xmax, ymax;
    start();
    if (argc != 2) 
    {printf("Un seul paramètre accepté \n");}
    else
    {
        serial_number = atoi(argv[1]);
        solve(serial_number, &xmax, &ymax);
        printf("Input = %i\n",serial_number);
        printf("Résulat = (%i, %i) \n",xmax,ymax);
    }
}