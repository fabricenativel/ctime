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

#define SIZE 100000000
            
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

void make_new(short int rec1, short int rec2, short int new_recipes[], int *num_new_recipes)
{
    short int sum_rec = rec1 + rec2;
    *num_new_recipes = 0;
    if (sum_rec < 10)
    {
        new_recipes[0] = sum_rec;
        *num_new_recipes = 1;
    }
    else
    {
        new_recipes[0] = sum_rec / 10;
        new_recipes[1] = sum_rec % 10;
        *num_new_recipes = 2;
    }
}

void affiche(int elf1, int elf2, short int recipes[SIZE], int number_recipes)
{
    char car1, car2;
    for (int n = 0; n < number_recipes; n++)
    {
        car1 = ' ';
        car2 = ' ';
        if (n == elf1)
        {
            car1 = '(';
            car2 = ')';
        }
        if (n == elf2)
        {
            car1 = '[';
            car2 = ']';
        }
        printf(" %c%i%c ", car1, recipes[n], car2);
    }
    printf("\n");
}

int number_digits(int n)
{
    int nd = 0;
    if (n == 0)
    {
        nd = 1;
    }
    else
    {
        while (n != 0)
        {
            nd++;
            n = n / 10;
        }
    }
    return nd;
}

int solve(int target)
{
    short int *recipes = calloc(SIZE, sizeof(short int));
    int elf1 = 0, elf2 = 1;
    short int new_recipes[20];
    int number_recipes = 2;
    int number_new_recipes;
    int test_value, weight;
    bool found = false;
    recipes[0] = 3;
    recipes[1] = 7;
    int offset = 0;
    while (!found)
    {
        assert(number_recipes < SIZE);
        make_new(recipes[elf1], recipes[elf2], new_recipes, &number_new_recipes);
        for (int i = number_recipes; i < number_recipes + number_new_recipes; i++)
        {
            recipes[i] = new_recipes[i - number_recipes];
        }
        number_recipes += number_new_recipes;
        test_value = 0;
        weight = 1;
        if (number_recipes > number_digits(target))
        {
            for (int i = number_recipes - 1; i > number_recipes - number_digits(target) - 1; i--)
            {
                test_value += recipes[i] * weight;
                weight = weight * 10;
            }
            //printf("Test value = %i (recette 1) \n",test_value);
            found = (test_value == target);
            if (!found && number_new_recipes == 2)
            {
                test_value = 0;
                weight = 1;
                for (int i = number_recipes - 2; i > number_recipes - number_digits(target) - 2; i--)
                {
                    test_value += recipes[i] * weight;
                    weight = weight * 10;
                }
                //printf("Test value = %i (recette 2) \n",test_value);
                found = (test_value == target);
                if (found) {offset = 1;}
            }
        }

        elf1 = (elf1 + 1 + recipes[elf1]) % number_recipes;
        elf2 = (elf2 + 1 + recipes[elf2]) % number_recipes;
        //affiche(elf1,elf2,recipes,number_recipes);
    }
    return number_recipes - number_digits(target) - offset;
}

int main(int argc, char *argv[])
{
    int rep;
    assert(argc != 1);
    start();
    rep = solve(atoi(argv[1]));
    printf("Résultat : %i\n", rep);
}