
#include "affichage.h"
#include "sim/habitation.h"
#include "stdio.h"

NiveauHabitation_t habitation_level_up(NiveauHabitation_t lvl, bool alimentee);
NiveauHabitation_t habitation_level_down(NiveauHabitation_t lvl, bool alimentee);

/// Crée une habitation.
/// @param niveau - niveau de l'habitation a alloué (Ruine, Terrain vague, etc.).
/// @return Habitation_t habitation - habitation allouée dynamiquement.
Habitation_t *habitation_alloc(NiveauHabitation_t niveau) {
    Habitation_t *habitation = malloc(sizeof(Habitation_t));
    habitation->niveau = niveau;
    habitation->update_ticks = 0;
    habitation->alimentee_en_eau = false;
    habitation->alimentee_en_electricite = false;
    habitation->eau = 0;
    habitation->electricite = 0;
    habitation->enfeu = 0;
    habitation->enfeu_prochain_cycle = 1;

    return habitation;
}

/// Détruit une habitation.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
void habitation_free(Habitation_t *habitation) {
    free(habitation);
}

/// Si une habitation brûle et qu'elle n'est pas connectée à une caserne elle tombe en ruine au cycle d'après.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
void habitation_brule(Habitation_t *habitation) {
    if (habitation->enfeu == true) {
        if (habitation->enfeu_prochain_cycle == true) {
            habitation->niveau = NIVEAU_RUINE;
            habitation->enfeu = false;
        }
    }
}

/// Si une habitation a été sauvée par une caserne de pompier, alors elle est éteinte.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
void habitation_sauvee_connexe_pompier_apres_15s(Habitation_t *habitation) {
    if (habitation->enfeu_prochain_cycle == false) {
            habitation->enfeu = false;
    }
}

/// Permet d'enlever le feu au prochain cycle si l'habitation est reliée à une caserne.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
void habitation_sauvee(Habitation_t *habitation) {
    if(habitation->relie_caserne){
        habitation->enfeu_prochain_cycle = false;
    }
}

/// Fonction qui détermine l'aléatoire pour prendre feu à chaque cycle d'habitation.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
void habitation_enfeu(Habitation_t *habitation) {
    //rand % max - min + 1.
    int a = rand() % 10 - 0 + 1;
    // 1 chance sur 10.
    if (a == 1) {
        habitation->enfeu = true;
        habitation->enfeu_prochain_cycle = true;
    }
}

/// Incrémente d'un tick la simulation d'un bâtiment.
/// Retourne les impôts à collecter lors d'un cycle du bâtiment.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
int habitation_step(Habitation_t *habitation, SimRules_t rules) {
    habitation->update_ticks++;

    /// Si l'habitation a passé un cycle de 15 ticks.
    if (habitation->update_ticks >= N_TICKS_EVOLUTION) {
        /// Reset des ticks.
        habitation->update_ticks = 0;
        /// L'habitation évolue selon les modes de jeu.
        habitation_evolve(habitation, rules);
        /// On check d'abord si lors de son précédent cycle l'habitation a été en feu et sauvée par une caserne.
        habitation_sauvee_connexe_pompier_apres_15s(habitation);
        /// Sinon elle brûle et devient une ruine.
        habitation_brule(habitation);
        /// L'habitation a 1/10 chances de prendre feu.
        habitation_enfeu(habitation);
        /// On regarde si l'habitation est connectée à une caserne pour la sauver au prochain cycle.
        habitation_sauvee(habitation);
        /// Retourne le nombre d'impôts à collecter à chaque cycle d'évolution.
        return habitation_get_nb_habitants(habitation) * IMPOT_PAR_HABITANT;
    }
    /// Si ce n'est pas encore un cycle on ne collecte pas d'impôts.
    return 0;
}

/// Fonction qui retourne le nombre d'habitant d'une habitation
/// @param habitation : une habitation louée dynamiquement faisant partie de la liste chaînée
/// @return int - nombre d'habitants de l'habitation
int habitation_get_nb_habitants(Habitation_t *habitation) {
    switch (habitation->niveau) {
        case NIVEAU_CABANE:
        case NIVEAU_CABANE_CAP:
            return 10;
        case NIVEAU_MAISON:
        case NIVEAU_MAISON_CAP:
            return 50;
        case NIVEAU_IMMEUBLE:
        case NIVEAU_IMMEUBLE_CAP:
            return 100;
        case NIVEAU_GRATTE_CIEL:
            return 1000;
        default:
            return 0;
    }
}

int habitation_get_required_water(Habitation_t *habitation, SimRules_t rules) {
    return habitation_get_nb_habitants(habitation);
}

int habitation_get_remaining_required_water(Habitation_t *habitation, SimRules_t rules) {
    return habitation_get_required_water(habitation, rules) - habitation->eau;
}

int habitation_get_required_energy(Habitation_t *habitation, SimRules_t rules) {
    return habitation_get_nb_habitants(habitation);
}

int habitation_get_remaining_required_energy(Habitation_t *habitation, SimRules_t rules) {
    return habitation_get_required_energy(habitation, rules) - habitation->electricite;
}

int habitation_get_required_for_next_level(Habitation_t* hab) {
    switch (hab->niveau) {
        case NIVEAU_TERRAIN_VAGUE:
        case NIVEAU_RUINE:
            return 10;
        case NIVEAU_CABANE:
            return 50;
        case NIVEAU_MAISON:
            return 100;
        case NIVEAU_IMMEUBLE:
        case NIVEAU_GRATTE_CIEL:
            return 1000;
        default:
            return 0;
    }
}

void habitation_evolve(Habitation_t *habitation, SimRules_t rules) {
    bool alimentee = habitation->alimentee_en_eau && habitation->alimentee_en_electricite;
    if (rules == Capitaliste_t) {
        if (habitation->niveau >= NIVEAU_TERRAIN_VAGUE_CAP && habitation->niveau <= NIVEAU_IMMEUBLE_CAP)
        {
            if (alimentee)
                habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
            else
                habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
        } else {
            if (habitation->eau == habitation_get_required_water(habitation, rules) && habitation->electricite == habitation_get_required_energy(habitation, rules) && alimentee)
                habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
            else
                habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
        }
    } else {
        int next_level_water = habitation_get_required_for_next_level(habitation), next_level_elec = next_level_water;

        /// On a les conditions d'évolution pour le prochain niveau, on évolue.
        if (habitation->eau == next_level_water && habitation->electricite == next_level_elec && alimentee)
            habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
        else if (habitation->eau == habitation_get_required_water(habitation, rules)
        && habitation->electricite == habitation_get_required_energy(habitation, rules) && alimentee)
            return;
        else
            habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
    }
}

int habitation_tri_par_distance(Habitation_t *a, Habitation_t *b) {
    Habitation_t *hab_a = (Habitation_t *) a;
    Habitation_t *hab_b = (Habitation_t *) b;
    if (hab_a->position.x < hab_b->position.x) {
        return -1;
    } else if (hab_a->position.x > hab_b->position.x) {
        return 1;
    } else {
        if (hab_a->position.y < hab_b->position.y) {
            return -1;
        } else if (hab_a->position.y > hab_b->position.y) {
            return 1;
        } else {
            return 0;
        }
    }
}

NiveauHabitation_t habitation_level_up(NiveauHabitation_t lvl, bool alimentee) {
    switch (lvl) {
        case NIVEAU_TERRAIN_VAGUE:
            return NIVEAU_CABANE;
        case NIVEAU_CABANE:
            return NIVEAU_MAISON;
        case NIVEAU_MAISON:
            return NIVEAU_IMMEUBLE;
        case NIVEAU_IMMEUBLE:
            return NIVEAU_GRATTE_CIEL;
        case NIVEAU_RUINE:
            return NIVEAU_CABANE;
        case NIVEAU_MAISON_CAP:
            return NIVEAU_IMMEUBLE_CAP;
        case NIVEAU_TERRAIN_VAGUE_CAP:
            return NIVEAU_CABANE_CAP;
        case NIVEAU_CABANE_CAP:
            return NIVEAU_MAISON_CAP;
        case NIVEAU_IMMEUBLE_CAP:
            return NIVEAU_GRATTE_CIEL; /// on repasse l'immeuble en mode de dev normal.
        default:
            return lvl;
    }
}

NiveauHabitation_t habitation_level_down(NiveauHabitation_t lvl, bool alimentee) {
    switch (lvl) {
        case NIVEAU_CABANE:
            return NIVEAU_RUINE;
        case NIVEAU_MAISON:
            return NIVEAU_CABANE;
        case NIVEAU_IMMEUBLE:
            return NIVEAU_MAISON;
        case NIVEAU_GRATTE_CIEL:
            return NIVEAU_IMMEUBLE;
        case NIVEAU_CABANE_CAP:
            return NIVEAU_RUINE;
        case NIVEAU_IMMEUBLE_CAP:
            return NIVEAU_MAISON;
        case NIVEAU_MAISON_CAP:
            return NIVEAU_CABANE;
        default:
            return lvl;
    }
}
