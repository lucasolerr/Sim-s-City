#include "sim/chateau.h"
#include "bfs.h"

ChateauEau_t* chateau_alloc() {
    ChateauEau_t* chateau = malloc(sizeof(ChateauEau_t));
    chateau->capacite = CAPACITE_CHATEAU_EAU;
    chateau->habitations = vector_alloc(10);
    return chateau;
}

void chateau_free(ChateauEau_t* chateau) {
    free(chateau);
}

int chateau_dispense(ChateauEau_t* chateau, int quantite) {
    int dispensed = MIN(chateau->capacite, quantite);
    chateau->capacite -= dispensed;
    return dispensed;
}

void chateau_step(ChateauEau_t* chateau, SimRules_t rules) {
    chateau->capacite = CAPACITE_CHATEAU_EAU;

    // prépasse pour déterminer le mode de distribution (plus proche vs minimisation des pertes d'habitants)
    int demande = 0;
    vector_sort(chateau->habitations, trier_noeux_habitations_par_distance);
    for (int i = 0; i < chateau->habitations->taille; ++i)
        demande += habitation_get_remaining_required_water(((HabitationNode_t*)chateau->habitations->data[i])->habitation, rules);

    if (demande > CAPACITE_CHATEAU_EAU)
        vector_sort(chateau->habitations, trier_noeux_habitations_par_niveau);

    /// distribution de l'eau pour remplir jusqu'à la demande du niveau actuel (demande du mode communiste)
    for (int i = 0; i < chateau->habitations->taille; ++i) {
        HabitationNode_t* habitation = chateau->habitations->data[i];
        habitation->habitation->eau += chateau_dispense(chateau, habitation_get_remaining_required_water(habitation->habitation, rules));
    }
}

void chateau_step_communist(ChateauEau_t* chateau, int* remaining_total_cap) {
    /// distribution de l'eau restante pour remplir jusqu'à la demande du niveau actuel (demande du mode communiste)
    for (int i = 0; i < chateau->habitations->taille; ++i) {
        HabitationNode_t* habitation = chateau->habitations->data[i];
        int needed_rem = habitation_get_required_for_next_level(habitation->habitation) - habitation->habitation->eau;
        if (needed_rem <= *remaining_total_cap) {
            int dispensed = chateau_dispense(chateau, needed_rem);
            habitation->habitation->eau += dispensed;
            *remaining_total_cap -= dispensed;
        }
    }
}