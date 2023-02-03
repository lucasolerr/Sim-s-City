
#include <assert.h>
#include <stdio.h>
#include "sim/habitation.h"

int main() {
//    Habitation_t* habitation = habitation_alloc(NIVEAU_TERRAIN_VAGUE);
//
//    // test simulation avec conditions d'eau et d'electricité remplies.
//    printf("--------Création d'un terrain vague + sim 60 ticks (eau, elec)--------\n\r", habitation->niveau);
//
//    for (int i = 0; i < 15; ++i) {
//        habitation->eau = habitation_get_nb_habitants(habitation);
//        habitation->electricite = habitation_get_nb_habitants(habitation);
//
//        assert(habitation->niveau == NIVEAU_TERRAIN_VAGUE);
//        habitation_step(habitation, Communiste_t);
//
//        // vérifier que les flots sont réinitialisés après simulation du bâtiment
//        assert(habitation->eau == -1);
//        assert(habitation->electricite == -1);
//    }
//
//    printf("Niveau atteint: %d (NIVEAU_CABANE)\n\r", habitation->niveau);
//    assert(habitation->niveau == NIVEAU_CABANE);
//
//    for (int i = 0; i < 45; ++i) {
//        habitation->eau = habitation_get_nb_habitants(habitation);
//        habitation->electricite = habitation_get_nb_habitants(habitation);
//        habitation_step(habitation, Communiste_t);
//    }
//    assert(habitation->niveau == NIVEAU_GRATTE_CIEL);
//    printf("Niveau atteint: %d (NIVEAU_GRATTE_CIEL)\n\r", habitation->niveau);
//
//    printf("--------NIVEAU_GRATTE_CIEL en sous alimentation d'eau et d'électricité après 90 ticks--------\n\r");
//    for (int i = 0; i < 75; ++i) {
//        habitation->eau = 10;
//        habitation->electricite = habitation_get_nb_habitants(habitation) + 1;
//
//        habitation_step(habitation, Communiste_t);
//    }
//    printf("Niveau atteint: %d (NIVEAU_CABANE)\n\r", habitation->niveau);
//    assert(habitation->niveau == NIVEAU_CABANE);
//
//    printf("--------NIVEAU_CABANE en sous alimentation d'eau et d'électricité après 15 ticks--------\n\r");
//
//    for (int i = 0; i < 15; ++i)
//        habitation_step(habitation, Communiste_t);
//
//    printf("Niveau atteint: %d (NIVEAU_RUINE)\n\r", habitation->niveau);
//    assert(habitation->niveau == NIVEAU_RUINE);

    return 0;
}