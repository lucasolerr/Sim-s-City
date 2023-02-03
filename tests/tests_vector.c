#include "utils/vector.h"
#include <assert.h>

int sort_compar_croissant(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int sort_compar_decroissant(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main() {
    Vector_t* vec = vector_alloc(10);
    assert(vec->capacite == 10);

    vector_push(vec, (void*) 1);
    assert(vec->taille == 1);

    vector_push(vec, (void*) 2);
    vector_push(vec, (void*) 3);
    assert(vec->taille == 3);

    assert(vector_pop(vec) == 3);
    assert(vec->taille == 2);

    assert(vector_pop(vec) == 2);
    assert(vec->taille == 1);

    assert(vector_pop(vec) == 1);
    assert(vec->taille == 0);

    // test du sort

    vector_push(vec, (void*) 3);
    vector_push(vec, (void*) 1);
    vector_push(vec, (void*) 2);

    // tri dans l'ordre croissant (a - b)
    vector_sort(vec, sort_compar_croissant);

    assert(vector_pop(vec) == 3);
    assert(vector_pop(vec) == 2);
    assert(vector_pop(vec) == 1);


    vector_push(vec, (void*) 3);
    vector_push(vec, (void*) 1);
    vector_push(vec, (void*) 2);

    // tri dans l'ordre décroissant (b - a)
    vector_sort(vec, sort_compar_decroissant);

    assert(vector_pop(vec) == 1);
    assert(vector_pop(vec) == 2);
    assert(vector_pop(vec) == 3);

    return 0;
}