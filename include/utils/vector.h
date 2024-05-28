
#ifndef ECECITY_VECTOR_H
#define ECECITY_VECTOR_H

#include <stdlib.h>
#include <stdint.h>

/// Un tableau dynamique générique.
typedef struct Vector_t {
    void** data;
    size_t taille;
    size_t capacite;
} Vector_t;

/// Crée un tableau dynamique.
Vector_t* vector_alloc(size_t initialCap);

/// Détruit un tableau dynamique.
void vector_free(Vector_t* vector);

/// Ajoute un élément à la fin du tableau dynamique.
void vector_push(Vector_t* vector, void* data);

/// Supprime un élément à la fin du tableau dynamique.
void* vector_pop(Vector_t* vector);

/// Retourne l'élément à l'index donné.
void* vector_get(Vector_t* vector, size_t index);

/// Fixe l'élément à l'index donné.
void vector_set(Vector_t* vector, size_t index, void* data);

/// Trie le tableau dynamique avec la fonction de comparaison donnée.
void vector_sort(Vector_t* vector, int (*compar)(const void*, const void*));

/// Vide le tableau
void vector_clear(Vector_t* vector);

void vector_free_clear(Vector_t* vector);

#endif //ECECITY_VECTOR_H
