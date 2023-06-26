#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>

const char PB[] = "1";
const char YEAR[] = "2018";
const char BASE_URL[] = "https://adventofcode.com/";
const long unsigned int DEFAULT_LINE_LENGTH = 255;

#define HASHTABLE_SIZE  10000

typedef struct node
{
    int value;
    struct node *next;
} node;

bool is_in_list(node *linked_list,int val)
{
    while (linked_list!=NULL)
    {
        if (linked_list->value == val) return true; else linked_list = linked_list->next;
    }
    return false;
}


node* insert_in_list(node *linked_list,int val)
{
    node *new_node = malloc(sizeof(node));
    new_node->value = val;
    new_node->next = linked_list;
    return new_node;
}

void view_list(node *linked_list)
{
    printf("-> ");
    while (linked_list!=NULL)
    {
        printf("%i -> ",linked_list->value);
        linked_list = linked_list->next;
    }
    printf("\n");
}

int get_hash(int value)
{
    return abs(value % HASHTABLE_SIZE);
}


void view_hashtable(node** hastable)
{
    for (int i=0;i<HASHTABLE_SIZE;i++)
    {
        printf("Bucket %i : ",i);
        view_list(hastable[i]);
    }
}

bool is_in_hashtable(node** hashtable, int val)
{
    int bucket_number = get_hash(val);
    return is_in_list(hashtable[bucket_number],val);
}

void insert_in_hashtable(node** hashtable, int val)
{
    int bucket_number = get_hash(val);
    hashtable[bucket_number] = insert_in_list(hashtable[bucket_number],val);
}


void start(void) {
    printf("AoC Année %s - Probleme %s \n", YEAR, PB);
    printf("%s%s/day/%s\n", BASE_URL, YEAR, PB);
}

void destroy_linked_list(node *list) {
    while (list != NULL) {
       node *backup = list->next;
       free(list);
       list = backup;
    }
}

void destroy_hash_table(node **hashtable) {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        destroy_linked_list(hashtable[i]);
    }
}


int solve() {
    int somme = 0;
    char filename[sizeof(char)*DEFAULT_LINE_LENGTH];
    snprintf(filename, DEFAULT_LINE_LENGTH,  "input%s.txt", PB);
    FILE* fileptr = fopen(filename,"r");

    node* hashtable[HASHTABLE_SIZE]={NULL};

    char line[DEFAULT_LINE_LENGTH];
    while (true) {
    while (fgets(line,(int)sizeof(line),fileptr)) {
        somme += atoi(line);
        if (is_in_hashtable(hashtable,somme)) {
            destroy_hash_table(hashtable);
            fclose(fileptr);
            return somme;
        }
        else {
            insert_in_hashtable(hashtable,somme);
        }
    }
    rewind(fileptr);
    }
    fclose(fileptr);


}

int main() {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
    return 0;
}
