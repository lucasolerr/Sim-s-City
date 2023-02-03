
#include "utils/vector.h"


/// Crée un tableau dynamique.
Vector_t* vector_alloc(size_t initialCap) {
    Vector_t *vector = malloc(sizeof(Vector_t));
    vector->data = malloc(initialCap * sizeof(void*));
    vector->taille = 0;
    vector->capacite = initialCap;
    return vector;
}

/// Détruit un tableau dynamique.
void vector_free(Vector_t* vector) {
    free(vector->data);
    free(vector);
}

/// Ajoute un élément à la fin du tableau dynamique.
void vector_push(Vector_t* vector, void* data) {
    if (vector->taille == vector->capacite) {
        vector->capacite *= 2;
        vector->data = realloc(vector->data, vector->capacite * sizeof(void*));
    }
    vector->data[vector->taille] = data;
    vector->taille++;
}

/// Supprime un élément à la fin du tableau dynamique.
void* vector_pop(Vector_t* vector) {
    if (vector->taille == 0)
        return NULL;

    vector->taille--;
    return vector->data[vector->taille];
}

/// Retourne l'élément à l'index donné.
void* vector_get(Vector_t* vector, size_t index) {
    if (index >= vector->taille)
        return NULL;

    return vector->data[index];
}

/// Fixe l'élément à l'index donné.
void vector_set(Vector_t* vector, size_t index, void* data) {
    if (index >= vector->taille)
        return;

    vector->data[index] = data;
}

void vector_sort(Vector_t* vector, int (*compar)(const void*, const void*)) {
    // tri par insertion.
    for (size_t i = 1; i < vector->taille; i++) {
        void *tmp = vector->data[i];
        size_t j = i;
        while (j > 0 && compar(vector->data[j - 1], tmp) > 0) {
            vector->data[j] = vector->data[j - 1];
            j--;
        }
        vector->data[j] = tmp;
    }
}

/// Vide le tableau dynamique
void vector_clear(Vector_t* vector) {
    vector->taille = 0;
}

void vector_free_clear(Vector_t* vector) {
    for (size_t i = 0; i < vector->taille; i++) {
        free(vector->data[i]);
    }
    vector->taille = 0;
}