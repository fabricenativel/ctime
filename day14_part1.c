#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

const char PB[] = "14";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const long unsigned int STRLEN = 255;

#define SIZE 1000000

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

void make_new(int rec1,int rec2, int new_recipes[], int *num_new_recipes)
{
    int sum_rec = rec1 + rec2;
    *num_new_recipes = 0;
    if (sum_rec<10)
    {
        new_recipes[0] = sum_rec;
        *num_new_recipes=1;
    }
    else
    {
        new_recipes[0] = sum_rec/10;
        new_recipes[1] = sum_rec%10;
        *num_new_recipes=2;
    }
}

void affiche(int elf1, int elf2, int recipes[SIZE],int number_recipes)
{
    char car1, car2;
    for (int n=0;n<number_recipes;n++)
    {
        car1 = ' ';
        car2 = ' ';
        if (n==elf1) {car1='('; car2=')';}
        if (n==elf2) {car1='['; car2=']';}
        printf(" %c%i%c ",car1,recipes[n],car2);
    }
    printf("\n");
}

void solve(int number,char* rep)
{
    int recipes[SIZE] = {3, 7};
    int elf1 = 0, elf2 = 1;
    int new_recipes[20];
    int number_recipes = 2;
    int number_new_recipes;
    
    while (number_recipes<number+10)
    {
    make_new(recipes[elf1], recipes[elf2], new_recipes, &number_new_recipes);
    for (int i = number_recipes; i < number_recipes + number_new_recipes; i++)
    {
        recipes[i] = new_recipes[i - number_recipes];
    }
    number_recipes += number_new_recipes;
    elf1 = (elf1 + 1 + recipes[elf1]) % number_recipes;
    elf2 = (elf2 + 1 + recipes[elf2]) % number_recipes;
    //affiche(elf1,elf2,recipes,number_recipes);
    }
    for (int i = number;i<number+10;i++)
    {
        rep[i-number]=(char)(48 + recipes[i]) ;
    }
}

int main(int argc, char *argv[])
{
    char rep[10];
    assert(argc != 1);
    start();
    solve(atoi(argv[1]),rep);
    printf("Résultat : %s\n", rep);
}