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

int square_value(int grid[SIZE][SIZE], int x, int y )
{
    int total = 0;
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            total += grid[y+i][x+j];
        }
    }
    return total;
}

void get_max(int grid[SIZE][SIZE],int *xmax, int *ymax)
{
    int cmax = 0;
    for (int y=1;y<SIZE-2;y++)
    {
        for (int x=1;x<SIZE-2;x++)
        {
            if (square_value(grid, x, y)>cmax)
            {
                cmax = square_value(grid, x, y);
                *xmax = x;
                *ymax = y;
            }
        }
    }
}

void solve(int serial_number,int *xmax, int *ymax)
{
    int grid[SIZE][SIZE];
    for (int y=1;y<SIZE;y++)
    {
        for (int x=1;x<SIZE;x++)
        {
            grid[y][x] = cell_value(serial_number,x,y);
        }
    }
    get_max(grid,xmax,ymax);
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