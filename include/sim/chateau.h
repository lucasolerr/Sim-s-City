
#ifndef ECECITY_CHATEAU_H
#define ECECITY_CHATEAU_H

#include <stdlib.h>
#include <utils/grille.h>
#include "utils/vector.h"

#define CHATEAU_PRIX_CONSTRUCTION 100000
#define CAPACITE_CHATEAU_EAU 5000

/// Représente un château d'eau simulé.
typedef struct ChateauEau_t {
    /// La capacité restante du château d'eau.
    int capacite;
    /// La liste des bâtiments deservis par le château.
    Vector_t* habitations;
    /// La position du château sur la carte.
    Vector2I position;
} ChateauEau_t;

/// Crée un château d'eau.
ChateauEau_t* chateau_alloc();

/// Détruit un château d'eau.
void chateau_free(ChateauEau_t* chateau);

/// Incrémente d'un tick la simulation d'un château d'eau.
void chateau_step(ChateauEau_t* chateau, SimRules_t rules);

/// Distribue l'eau restante aux bâtiments.
void chateau_step_communist(ChateauEau_t* chateau, int* remaining_total_cap);

/// Donne de l'eau à un bâtiment.
int chateau_dispense(ChateauEau_t* chateau, int quantite);

#endif //ECECITY_CHATEAU_H
