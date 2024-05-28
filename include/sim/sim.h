
#ifndef ECECITY_SIM_H
#define ECECITY_SIM_H

#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>
#include <utils/vector.h>

#define SIM_MAP_LARGEUR 45
#define SIM_MAP_HAUTEUR 35

#define ROUTE_PRIX_CONSTRUCTION 10

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/// Le type de case
typedef enum CaseKind_t {
    /// case vide
    KIND_VIDE = 0,
    /// KIND_HABITATION
    KIND_HABITATION,
    /// Centrale électrique
    KIND_CENTRALE,
    /// Château d'eau
    KIND_CHATEAU,
    /// Casernes
    KIND_CASERNE,
    /// KIND_ROUTE
    KIND_ROUTE,
    NB_CASE_KIND,
} CaseKind_t;

/// Une case dans la carte de la simulation.
typedef struct Case_t {
    /// Un pointeur vers la structure de données correspondant de la case.
    void* donnees;
    /// Le type de la case.
    CaseKind_t type;
    /// Permet d'indiquer si la case est connexe au réseau d'eau.
    bool connexe_eau;
    /// Permet d'indiquer si la case est connexe au réseau électrique.
    bool connexe_elec;
    /// Permet d'indiquer si la case est connexe aux casernes de pompier.
    bool connexe_caserne;
    /// Enum SPRITE_MAP pour avoir un fond de terrai non uniforme (arbres, herbe, ...).
    enum SPRITE_MAP sprite_terrain;
} Case_t;

/// Le monde de simulation du jeu.
typedef struct SimWorld_t {
    /// Liste chaînée des habitations du monde, pour un accès "linéaire".
    Liste_t* habitations;
    /// Liste chaînée des centrales électriques du monde, pour un accès "linéaire".
    Liste_t* centrales;
    /// Liste chaînée des châteaux d'eau du monde, pour un accès "linéaire".
    Liste_t* chateaux;
    /// Liste chaînée des casernes du monde, pour un accès "linéaire".
    Liste_t* casernes;
    /// Carte de la simulation (utilisé pour les parcours en largeur).
    Case_t map[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR];
    /// La qte de monnaie disponible.
    int monnaie;
    /// Nombre d'habitants dans le monde.
    int nb_total_habitants;
    /// Quantité d'eau disponible (mìse à dispo par les châteaux d'eau).
    int qte_dispo_eau;
    /// Quantité d'électricité disponible (mise à dispo par les centrales électriques).
    int qte_dispo_elec;
    /// Quantité max d'eau dispo.
    int qte_max_eau;
    int qte_max_elec;
    /// Les règles d'évolution pour la simulation.
    SimRules_t rules;
    /// Le temps écoulé depuis le début de la simulation (en ticks).
    int n_ticks;
    /// La simulation tourne-t-elle ?
    bool sim_running;
} SimWorld_t;

/// Crée un monde de simulation vide.
/// @param monnaie, rules - monnaie (argent dans le jeu), mode de jeu (communiste, capitaliste) - valeurs lues depuis le fichier txt.
/// @return SimWorld_t* world - monde de simulation.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie);

/// Avance d'une étape la simulation.
/// @param world - monde de simulation.
void sim_world_step(SimWorld_t* world);

/// Execute la répartition des ressources.
void sim_step_resources(SimWorld_t* world);

/// Détruit un monde de simulation.
/// @param world - monde de simulation.
void sim_world_destroy(SimWorld_t* world);

/// Détruit l'entitée séléctionnée.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param x, y - coordonnées en isométrique de la destruction sur le monde de simulation.
void sim_destroy_entity(SimWorld_t* world, int x, int y);

/// Place une entité dans la carte de la simulation aux coordonnées données.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param type - type de case de la simulation du monde (Habitation, route, terrain, ...).
/// @param x, y - coordonnées en isométrique du placement sur le monde de simulation.
/// @param reload - si l'entité placée est une centrale, caserne, château d'eau alors permet d'actualiser ses voisins.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y, bool reload);

/// Vérifie si un bâtiment de dimensions précisées peut être placé à une position donnée.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param isBat - différencie le placement d'une route (1X1) et d'un bâtiment (3X3, 4X6, 6X4) où il faut vérifier les cases adjacentes pour placer l'entité.
/// @param x, y - coordonnées en isométrique du placement sur le monde de simulation.
/// @param w, h - hauteur et largeur de l'entité à placer.
/// @return booléen - true si le placement de l'entité est possible - false sinon.
bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h);

/// Recalcule les voisins de chacunes des centrales & châteaux.
void sim_update_voisins(SimWorld_t* world);

#endif //ECECITY_SIM_H
