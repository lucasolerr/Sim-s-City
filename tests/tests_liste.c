#include <assert.h>
#include <stdio.h>
#include "utils/liste.h"

int main() {
    printf("Creation de la liste\n");
    Liste_t* list = liste_alloc();
    assert(list != NULL);

    printf("Ajout d'un element en fin de liste\n");
    liste_ajouter_fin(list, 0xDEADBEEF);
    assert(list->taille == 1);

    printf("Ajout d'un element en debut de liste\n");
    liste_ajouter_debut(list, 0xCAFEBABE);
    assert(list->taille == 2);

    printf("Suppression d'un element en debut de liste\n");
    assert(liste_supprimer_debut(list) == 0xCAFEBABE);

    assert(liste_supprimer_fin(list) == 0xDEADBEEF);

    printf("La liste est vide\n\r");
    assert(liste_estVide(list) == true);

    printf("Test iteration\n\r");
    liste_ajouter_fin(list, 1);
    liste_ajouter_fin(list, 2);
    liste_ajouter_fin(list, 3);

    struct Maillon_t* maillon = list->premier;
    assert(maillon->data == 1);

    maillon = maillon->next;
    assert(maillon->data == 2);

    maillon = maillon->next;
    assert(maillon->data == 3);
     return 0;
}