#ifndef ECECITY_BFS_H
#define ECECITY_BFS_H

#include "utils/grille.h"
#include "utils/liste.h"
#include "sim/sim.h"
#include "utils/vector.h"

/// Représente une habitation identifiée lors du parcours en largeur.
typedef struct HabitationNode_t {
    int distance;
    Habitation_t* habitation;
} HabitationNode_t;

int trier_noeux_habitations_par_distance(HabitationNode_t* node, HabitationNode_t* node2);

int trier_noeux_habitations_par_niveau(HabitationNode_t* node, HabitationNode_t* node2);

int trier_noeux_habitations_par_eau(HabitationNode_t* node, HabitationNode_t* node2);

/// Un pointeur de fonction sur une fonction visiteuse de noeud.
/// Retourne true si les voisins du noeud ne doivent pas êtres visités.
typedef bool (*VisiteurBFS_t)(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batId);

/// Fonction visiteuse de noeud pour BFS.
/// Ajoute s'il s'agit d'une habitation, cette habitation à la liste d'adjacence de la centrale.
bool bfs_visiteur_habitation(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batId);

void bfs(SimWorld_t* world, Vector2I start, void* batId, Vector_t* resultats, VisiteurBFS_t visiteur);

#endif //ECECITY_BFS_H
