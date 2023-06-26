#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

static const char PB[] = "1";
static const char YEAR[] = "2018";
static const char BASE_URL[] = "https://adventofcode.com/";
static const int DEFAULT_LINE_LENGTH = 255;

static const size_t MAX_ARRAY_SIZE = 200000;

static void start(void) {
    printf("AoC Année %s - Probleme %s \n", YEAR, PB);
    printf("%s%s/day/%s\n", BASE_URL, YEAR, PB);
}

bool is_in(int64_t value, int64_t tab[], int64_t tab_size) {
    for (int i=0;i<tab_size;i++)
    {
        if (tab[i] == value) return true;
    }

    return false;
}

size_t get_upper_pair(size_t number) {
    if (number % 2 == 0) {
        return number;
    }

    return number + 1;
}

/*
  Si l'élément appartient au tableau retourne l'index où se trouve l'élément
  Sinon retourne l'index où devrait se trouver l'élément
 */
size_t find_index_in_sorted_array(uint64_t elem, uint64_t *array, size_t array_size) {
    if (array_size == 0) {
        return 0;
    }

    const size_t max_iterations = 30;
    size_t current_iteration = 0;

    /* Recherche dichotomique */
    ssize_t min_index = -1;
    size_t max_index = array_size;
    size_t current_index = get_upper_pair(array_size) / 2 - 1;

    while (true) {
        /* Juste pour éviter une boucle infinie */
        assert(current_iteration++ < max_iterations);

        if (array[current_index] > elem) {
            max_index = current_index - 1;
        }
        else if (array[current_index] < elem) {
            min_index = current_index + 1;
        }
        else if (array[current_index] == elem) {
            return current_index;
        }

        /* On traite simplement le cas des bornes */
        if (max_index == 0) {
            return max_index;
        }
        else if ((min_index != -1) && (min_index >= array_size - 1)) {
            return min_index;
        }

        size_t old_index  = current_index;
        current_index = (get_upper_pair(max_index - min_index) / 2);
        if (min_index != -1) {
            current_index += min_index;
        }

        if (old_index == current_index) {
            return current_index;
        }

    }
}

bool is_in_sorted_array(uint64_t elem, uint64_t* array, size_t size) {
    if (size == 0) {
        return 0;
    }

    return array[find_index_in_sorted_array(elem, array, size)] == elem;
}


void insert_in_sorted_array(uint64_t *destination, uint64_t elem, size_t current_size) {
    /* Par sécurité on s'empêche de faire n'importe quoi */
    assert(current_size + 1 < MAX_ARRAY_SIZE);

    /* Trouver l'emplacement où ajouter l'élément */
    size_t index = find_index_in_sorted_array(elem, destination, current_size);

    /* Ici on décalle tous les éléments à droite de l'index de 1 */
    memmove(destination + index + 1, destination + index, (current_size - index) * sizeof(uint64_t));

    destination[index] = elem;
}

int solve(void) {
    int64_t somme = 0;

    char filename[sizeof(char)*DEFAULT_LINE_LENGTH];
    snprintf(filename, DEFAULT_LINE_LENGTH,  "input%s.txt", PB);
    FILE* fileptr = fopen(filename,"r");

    char line[DEFAULT_LINE_LENGTH];
    size_t size = 0;
    uint64_t tab[MAX_ARRAY_SIZE];
    while (true) {
    while (fgets(line,sizeof(line),fileptr)) {
        somme += atoi(line);
        if (size>0 && is_in_sorted_array(somme,tab,size)) {
            return somme;
        }
        else {
            insert_in_sorted_array(tab, somme, size++);
        }
    }
    rewind(fileptr);
    }
    fclose(fileptr);
}

void test(void) {
    /* Test suite primitive pour la dichotomie */
    uint64_t test_arr[8] = { 3, 5, 7, 19, 22, 0, 0, 0 };
    assert(find_index_in_sorted_array(5, test_arr, 5) == 1);
    assert(find_index_in_sorted_array(3, test_arr, 5) == 0);
    assert(find_index_in_sorted_array(19, test_arr, 5) == 3);
    assert(find_index_in_sorted_array(23, test_arr, 5) == 5);
    assert(find_index_in_sorted_array(100, test_arr, 5) == 5);
    assert(find_index_in_sorted_array(2, test_arr, 5) == 0);
    assert(find_index_in_sorted_array(9, test_arr, 5) == 3);

    insert_in_sorted_array(test_arr, 9, 5);
    assert(find_index_in_sorted_array(9, test_arr, 6) == 3);

    insert_in_sorted_array(test_arr, 383, 6);
    assert(find_index_in_sorted_array(383, test_arr, 7) == 6);

    insert_in_sorted_array(test_arr, 17, 7);
    assert(find_index_in_sorted_array(17, test_arr, 8) == 4);

    uint64_t test_arr2[4] = { 3, 5, 7, 19};
    assert(find_index_in_sorted_array(5, test_arr2, 4) == 1);
    assert(find_index_in_sorted_array(3, test_arr2, 4) == 0);
    assert(find_index_in_sorted_array(19, test_arr2, 4) == 3);
    assert(find_index_in_sorted_array(23, test_arr2, 4) == 4);
    assert(find_index_in_sorted_array(100, test_arr2, 4) == 4);
    assert(find_index_in_sorted_array(2, test_arr2, 5) == 0);
}

int main(void) {
    start();
    int rep = solve();
    printf("Réponse : %i \n",rep);
}
