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

// Direction pour parcourir le carré représentant le cercle pour la distance de Manhattan
const Point direction[4]={{.c = -1, .l = -1}, {.c = -1, .l = 1}, {.c = 1, .l = 1}, {.c = 1, .l = -1}};

int manhattan(Point p1, Point p2)
{
    return abs(p1.c-p2.c)+abs(p1.l-p2.l);
}

bool in_grid(int l,int c, int lmax, int cmax)
{
    return (c >=0 && c<=cmax && l>=0 && l<=lmax);
}

int indexof(int l, int c, Point *points, int nmax)
{
    for (int n=0; n<nmax; n++)
        {
            if (points[n].l==l && points[n].c==c)
            {
                return n;
            }
        }
    return -1;
}

/* l et c sont les coordonnées d'un point de la grille et rayon un entier. La fonction renvoie :
- 0 si aucun point des données n'est sur le cercle de centre (l,c) et de rayon r
- le numéro du point appartenant aux données si c'est le seul point sur le cercle
- -1 si plusieurs points sont sur le cercle
*/
int get_neighbour(int l, int c, Point *points,int nmax,int lmax, int cmax)
{
    int nb_points, num_point;
    int pt_index;
    int r=1;
    int contact, idx_contact;
    int sc, sl, dc, dl;
    // Si le point est dans les données alors lui affecter son numéro
    pt_index = indexof(l,c,points,nmax);
    if (pt_index != -1) 
    {
        return pt_index+1;
    }
    // Sinon faire des cercles de + en  + grand jusqu'à trouver au moins un point des données
    contact = 0;
    while (contact == 0)
    {
        sc = c + r;
        sl = l;
        for (int d=0;d<4;d++)
        {       
            dc  = direction[d].c;
            dl  = direction[d].l;
            for (int k=0;k<r;k++)
            {
                if (in_grid(sl,sc,lmax,cmax))
                {
                    pt_index=indexof(sl,sc,points,nmax);
                    if (pt_index!=-1)
                    {
                        contact++;
                        idx_contact = pt_index;
                    }
                }
                sc += dc;
                sl += dl;
            }
        }
        r++;
    }
    if (contact==1)
    {
        return idx_contact+1;
    }
    else
    {
        return 0;
    }
    return 0;
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
    char line[STRLEN];
    unsigned int num_points=0,cmax=0,lmax=0,cmin=__INT_MAX__,lmin=__INT_MAX__,max_size = 0;
    unsigned int neighbour,c,l;
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
    unsigned int grille[lmax+2][cmax+2];
    unsigned int count_size[num_points];
    bool infinite[num_points];
    memset( grille, 0, (lmax+2)*(cmax+2)*sizeof(unsigned int));
    memset( infinite, false, num_points*sizeof(bool));
    memset( count_size,0,num_points*sizeof(unsigned int));
    for (int l=lmin-1;l<=lmax+1;l++)
    {
        for (int c=cmin-1;c<=cmax+1;c++)
        {
            neighbour = get_neighbour(l,c,points,num_points,lmax,cmax);
            grille[l][c] = neighbour;
            // On suppose que si un point apparaît sur le périmètre alors il s'étendra à l'infini (viable ?)
            if (neighbour!=0) 
            {
                count_size[neighbour-1]++;
                if ((l==lmin || l==lmax+1 || c==cmin || c==cmax+1) && !infinite[neighbour]) 
                {
                    infinite[neighbour] = true;
                }
            }
            //printf("%c",(char) 64+neighbour);
        }
        //printf("\n");
    }
    /* printf("Points à éliminer sur les %i points: ",num_points);
    for (int i=1;i<=num_points;i++)
    {
        if (infinite[i])
        {
            printf("%i ",i-1);
        }
    } 
    printf("\n"); */
    for (int i=0;i<num_points;i++)
    {
        //printf("Points %i, taille %i\n",i,count_size[i]);
        if (!infinite[i+1])
        {
            if (count_size[i]>max_size)
            {
                max_size = count_size[i];
            }
        }
    }
    return max_size;
}

int main(int argc, char* argv[]) {
    bool simple;
    start();
    simple = (argc>=2);
    int rep = solve(simple);
    printf("Réponse : %i \n",rep);
}