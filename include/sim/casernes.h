#ifndef ECECITY_POMPIER_H
#define ECECITY_POMPIER_H
#include <stdlib.h>
#include <utils/grille.h>
#include <utils/vector.h>
#include "utils/liste.h"
#include "sim.h"

#define CASERNE_PRIX_CONSTRUCTION 10000

typedef struct CasernePompier_t {
    /// La liste des bâtiments desservis par la caserne.
    Vector_t* habitations;
    /// La position de la caserne sur la carte.
    Vector2I position;
} CasernePompier_t;

///Créer une caserne
CasernePompier_t* alloc_caserne();

/// Affichage d'une icône "feu" quand une habitation est en feu
void draw_enfeu(SimWorld_t *world, SpriteSheet_t* sheet);

/// Détruit une caserne.
void caserne_free(CasernePompier_t* caserne);

#endif //ECECITY_POMPIER_H
