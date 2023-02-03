
#ifndef ECECITY_HABITATION_H
#define ECECITY_HABITATION_H

#include <stdbool.h>
#include <stdlib.h>
#include "spritesheet.h"

#include "utils/grille.h"

#define HABITATION_PRIX_CONSTRUCTION 10000
#define N_TICKS_EVOLUTION 15
#define IMPOT_PAR_HABITANT 10

/// Enum contenant les différents états possibles pour une habitation allant de la ruine au gratte-ciel
typedef enum NiveauHabitation_t {
    NIVEAU_TERRAIN_VAGUE_CAP = -99999,
    NIVEAU_CABANE_CAP,
    NIVEAU_MAISON_CAP,
    NIVEAU_IMMEUBLE_CAP,
    NIVEAU_RUINE = 0,
    NIVEAU_TERRAIN_VAGUE,
    NIVEAU_CABANE,
    NIVEAU_MAISON,
    NIVEAU_IMMEUBLE,
    NIVEAU_GRATTE_CIEL,
} NiveauHabitation_t;


/// Représente une habitation simulée.
typedef struct Habitation_t {
    /// Niveau de l'habitation.
    NiveauHabitation_t niveau;
    /// Flot d'eau disponible pour l'habitation.
    int eau;
    /// Flot d'électricité disponible pour l'habitation.
    int electricite;
    /// Compteur de ticks avant prochaine évolution.
    int update_ticks;
    /// La position du bâtiment.
    Vector2I position;
    /// L'habitation est-elle reliée au réseau d'eau?
    bool alimentee_en_eau;
    /// L'habitation est-elle reliée au réseau d'électrique?
    bool alimentee_en_electricite;
    /// L'habitation est-elle reliée à une caserne à une distance de 20 blocs?
    bool relie_caserne;
    /// Le bat a 1/10 d'etre en feu
    bool enfeu;
    /// Initialisé à vrai sauf si caserne connexe, il devient faux et au prochain cycle enfeu deviendra faux sinon l'habitation devient une ruine
    bool enfeu_prochain_cycle;
} Habitation_t;

/// Crée une habitation.
/// @param niveau - niveau de l'habitation a alloué (Ruine, Terrain vague, etc.).
/// @return Habitation_t habitation - adresse structure habitation allouée dynamiquement.
Habitation_t* habitation_alloc(NiveauHabitation_t niveau);

/// Détruit une habitation.
/// @param habitation - adresse structure habitation allouée dynamiquement.
void habitation_free(Habitation_t* habitation);

/// Incrémente d'un tick la simulation d'un bâtiment.
/// Retourne les impôts générés par l'habitation.
int habitation_step(Habitation_t* habitation, SimRules_t rules);

/// Fait évoluer un bâtiment en fonction des ticks d'évolution / régression.
void habitation_evolve(Habitation_t* habitation, SimRules_t rules);

/// Retourne le nombre d'habitants dans l'habitation.
int habitation_get_nb_habitants(Habitation_t* habitation);

/// Retourne la qte d'eau nécessaire pour l'habitation pour qu'elle évolue (MODE CAPITALISTE)
int habitation_get_required_water(Habitation_t* habitation, SimRules_t rules);

/// Retourne la qte de ressource (eau / elec) nécessaire pour passer au niveau suivant (MODE COMMUNISTE)
int habitation_get_required_for_next_level(Habitation_t* habitation);

/// Retourne la qte d'eau nécessaire pour l'habitation pour qu'elle évolue. (MODE CAPITALISTE)
int habitation_get_required_energy(Habitation_t* habitation, SimRules_t rules);

/// Retourne la qte d'energie nécessaire pour l'habitation pour qu'elle évolue. (MODE CAPITALISTE)
int habitation_get_remaining_required_energy(Habitation_t* habitation, SimRules_t rules);

/// Retourne la qte d'eau nécessaire pour l'habitation pour qu'elle évolue. (MODE CAPITALISTE)
int habitation_get_remaining_required_water(Habitation_t* habitation, SimRules_t rules);

/// Fonction de tri pour trier les habitations par distance lors de la distribution.
int habitation_tri_par_distance(Habitation_t* a, Habitation_t* b);

/// Chaque habitation lors de son cycle de 15s a une chance sur 10 de prendre feu
void habitation_enfeu(Habitation_t *habitation);
/// S'il n'y a pas de casernes autour de l'habitation alors elle tombe en état de ruine
void habitation_brule(Habitation_t *habitation);
/// Si une caserne se trouve à une distance de 20 blocs et moins alors l'habitation continue d'évoluer normalement
void habitation_sauvee(Habitation_t*habitation);

#endif //ECECITY_HABITATION_H
