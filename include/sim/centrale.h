
#ifndef ECECITY_CENTRALE_H
#define ECECITY_CENTRALE_H

#include <stdlib.h>
#include <stdbool.h>
#include <utils/grille.h>
#include <utils/vector.h>
#include "habitation.h"

#define CENTRALE_PRIX_CONSTRUCTION 100000
#define CAPACITE_CENTRALE_ELECTRIQUE 5000

/// Représente une centrale électrique simulée.
typedef struct CentraleE_t {
    /// Flot d'électricité disponible pour la centrale.
    /// Réinitialisé à chaque début de tick de simulation.
    int capacite;

    /// Liste des habitations reliées à la centrale.
    Vector_t* habitations;

    /// Position de la centrale sur la carte (en isométrique).
    Vector2I position;
} CentraleElectrique_t;

/// Crée une centrale électrique.
CentraleElectrique_t* centrale_alloc();

/// Détruit une centrale électrique.
void centrale_free(CentraleElectrique_t* centrale);

/// Réinitialise la capacité de la centrale.
/// A appeler au début de chaque tick de simulation.
void centrale_step(CentraleElectrique_t* centrale, SimRules_t rules);

/// Répartit la capacité restante de la centrale
void centrale_step_communist(CentraleElectrique_t* centrale, int* remaining_total_cap);

/// Donne de l'électricité à une habitation.
int centrale_dispense(CentraleElectrique_t* centrale, int quantite);


#endif //ECECITY_CENTRALE_H
