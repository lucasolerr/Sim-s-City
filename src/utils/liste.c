#include "utils/liste.h"


/// Crée une liste vide.
Liste_t* liste_alloc() {
    Liste_t *liste = malloc(sizeof(Liste_t));
    liste->premier = NULL;
    liste->dernier = NULL;
    liste->taille = 0;
    return liste;
}

void liste_free(Liste_t* liste) {
    struct Maillon_t *maillon = liste->premier;
    while (maillon != NULL) {
        struct Maillon_t *tmp = maillon;
        maillon = maillon->next;
        free(tmp);
    }
    free(liste);
}

/// Regarde si la liste est vide.
bool liste_estVide(Liste_t *liste) {
    return liste->taille == 0;
}

/// Ajoute un élément à la fin de la liste.
void liste_ajouter_fin(Liste_t *liste, void *data) {
    struct Maillon_t *maillon = malloc(sizeof(struct Maillon_t));
    maillon->data = data;
    maillon->next = NULL;
    maillon->prev = liste->dernier;

    if (liste->taille == 0)
        liste->premier = maillon;
    else
        liste->dernier->next = maillon;

    liste->dernier = maillon;
    liste->taille++;
}

/// Supprime un élément en fin de liste et le retourne.
void* liste_supprimer_fin(Liste_t *liste) {
    if (liste->taille == 0)
        return NULL;

    struct Maillon_t *maillon = liste->dernier;
    void *data = maillon->data;

    if (liste->taille == 1) {
        liste->premier = NULL;
        liste->dernier = NULL;
    } else {
        liste->dernier = maillon->prev;
        liste->dernier->next = NULL;
    }

    free(maillon);
    liste->taille--;

    return data;
}

/// Ajoute un élément en début de liste.
void liste_ajouter_debut(Liste_t *liste, void *data) {
    struct Maillon_t *maillon = malloc(sizeof(struct Maillon_t));
    maillon->data = data;
    maillon->next = liste->premier;
    maillon->prev = NULL;

    if (liste->taille == 0)
        liste->dernier = liste->premier = maillon;
    else
        liste->premier->prev = maillon;

    liste->premier = maillon;
    liste->taille++;
}

/// Supprime un élément en début de liste et le retourne.
void* liste_supprimer_debut(Liste_t *liste) {
    if (liste->taille == 0)
        return NULL;

    struct Maillon_t *maillon = liste->premier;
    void *data = maillon->data;

    if (liste->taille == 1) {
        liste->premier = NULL;
        liste->dernier = NULL;
    } else {
        liste->premier = maillon->next;
        liste->premier->prev = NULL;
    }

    free(maillon);
    liste->taille--;

    return data;
}

void liste_ajout_tri(Liste_t *liste, void *data, int (*comparateur)(void *, void *)) {
    struct Maillon_t *maillon = malloc(sizeof(struct Maillon_t));
    maillon->data = data;

    if (liste->taille == 0) {
        maillon->next = NULL;
        maillon->prev = NULL;
        liste->premier = maillon;
        liste->dernier = maillon;
    } else {
        struct Maillon_t *tmp = liste->premier;
        while (tmp != NULL && comparateur(tmp->data, data) < 0)
            tmp = tmp->next;

        if (tmp == NULL) {
            maillon->next = NULL;
            maillon->prev = liste->dernier;
            liste->dernier->next = maillon;
            liste->dernier = maillon;
        } else if (tmp->prev == NULL) {
            maillon->next = tmp;
            maillon->prev = NULL;
            tmp->prev = maillon;
            liste->premier = maillon;
        } else {
            maillon->next = tmp;
            maillon->prev = tmp->prev;
            tmp->prev->next = maillon;
            tmp->prev = maillon;
        }
    }

    liste->taille++;
}


void liste_supprimer(Liste_t *liste, void *data) {
    struct Maillon_t *maillon = liste->premier;
    while (maillon != NULL && maillon->data != data)
        maillon = maillon->next;

    if (maillon == NULL)
        return;

    if (maillon->prev == NULL)
        liste->premier = maillon->next;
    else
        maillon->prev->next = maillon->next;

    if (maillon->next == NULL)
        liste->dernier = maillon->prev;
    else
        maillon->next->prev = maillon->prev;

    free(maillon);
    liste->taille--;
}

void liste_vider(Liste_t* liste) {
    while (!liste_estVide(liste))
        liste_supprimer_fin(liste);
}
