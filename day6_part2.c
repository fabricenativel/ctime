#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const char PB[] = "6";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const int STRLEN = 255;

// Point repéré par sa ligne et sa colonne, dans les fonctions on donne indice de ligne avant
struct Point
{   
    int l;
    int c;
};
typedef struct Point Point;


int manhattan(Point p1, Point p2)
{
    return abs(p1.c-p2.c)+abs(p1.l-p2.l);
}

int sum_distance(Point orig,Point *points, int nmax)
{
    unsigned int sd = 0;
    for (int i=0;i<nmax;i++)
    {
        sd+=manhattan(orig, points[i]);
    }
    return sd;
}


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

char *get_filename(bool simple) {
    char* filename = malloc(sizeof(char)*STRLEN);
    strcpy(filename,"input");
    strcat(filename,PB) ;
    // Possibilité de sélectionner l'input simple depuis la ligne de commande
    if (simple)
    {
        strcat(filename,"simple.txt") ;
    }
    else
    {
        strcat(filename,".txt") ;
    }   
    return filename;
}

int solve(bool simple) 
{
    char* filename = get_filename(simple);
    FILE* fileptr = fopen(filename,"r");
    Point* points = malloc(sizeof(Point)*2000);
    Point current_point;
    char line[STRLEN];
    unsigned int num_points=0,cmax=0,lmax=0,cmin=__INT_MAX__,lmin=__INT_MAX__,max_size = 0;
    unsigned int neighbour,c,l;
    unsigned int are_ok = 0;
    printf("Fichier d'input : %s\n",filename);
    while (fgets(line,sizeof(line),fileptr)) 
    {
        int ok=sscanf(line,"%i,%i",&points[num_points].c,&points[num_points].l);
        if (ok!=0)
        {
            if (points[num_points].c>cmax)
            {
                cmax = points[num_points].c;
            }
            if (points[num_points].c<cmin)
            {
                cmin = points[num_points].c;
            }
            if (points[num_points].l>lmax)
            {
                lmax = points[num_points].l;
            }
            if (points[num_points].l<lmin)
            {
                lmin = points[num_points].l;
            }
            //printf("Point %i :  coordonnées (%i,%i) \n",num_points,points[num_points].l,points[num_points].c);
            num_points ++;
        }
    }
    printf("Il y a %i points, %i<=ligne<=%i, %i<=colonne<=%i\n",num_points,lmin,lmax,cmin,cmax);
    fclose(fileptr);
    for (int l=lmin-1;l<=lmax+1;l++)
    {
        for (int c=cmin-1;c<=cmax+1;c++)
        {   
            current_point.l = l;
            current_point.c = c;
            if (sum_distance(current_point,points,num_points) < 10000)
            {
                are_ok++;
            }            
        }
    }
    return are_ok;
}

int main(int argc, char* argv[]) {
    bool simple;
    start();
    simple = (argc>=2);
    int rep = solve(simple);
    printf("Réponse : %i \n",rep);
}