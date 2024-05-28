
#include <stdio.h>
#include "sim/sim.h"
#include "bfs.h"
#include "sim/casernes.h"

void sim_reset_flow_distribution(SimWorld_t* world);
void sim_update_voisins_chateaux(SimWorld_t* world);
void sim_update_voisins_centrales(SimWorld_t* world);
void sim_update_voisins_casernes(SimWorld_t* world);


/// Fonctions de visite des noeuds de BFS pour la connexion des châteaux d'eau et d'eau aux habitations / routes.

bool bfs_visiteur_connexite_eau(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial);
bool bfs_visiteur_connexite_elec(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial);
bool bfs_visiteur_connexite_caserne(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial);


/// Fonction qui génére un fond de map aléatoire (arbres, herbe, terre, ...).
/// @return enum SPRITE_MAP - sprite du terrain du fond de la carte de simulation.
enum SPRITE_MAP rand_sprite_terrain(){
    int rand_sprite_terrain = rand() % 1001;
    enum SPRITE_MAP sprite_terrain;
    if(rand_sprite_terrain < 800){
        sprite_terrain = SPRITE_TERRAIN_0;
    } else if (rand_sprite_terrain > 800 && rand_sprite_terrain < 840){
        sprite_terrain = SPRITE_TERRAIN_1;
    } else if (rand_sprite_terrain > 840 && rand_sprite_terrain < 880){
        sprite_terrain = SPRITE_TERRAIN_2;
    } else if (rand_sprite_terrain > 880 && rand_sprite_terrain < 920){
        sprite_terrain = SPRITE_TERRAIN_3;
    } else if (rand_sprite_terrain > 920 && rand_sprite_terrain < 960){
        sprite_terrain = SPRITE_TERRAIN_4;
    } else if (rand_sprite_terrain > 960 && rand_sprite_terrain < 1000){
        sprite_terrain = SPRITE_TERRAIN_5;
    } else {
        sprite_terrain = SPRITE_TERRAIN_6;
    }
    return sprite_terrain;
}

/// Crée un monde de simulation vide.
/// @param monnaie, rules - monnaie (argent dans le jeu), mode de jeu (communiste, capitaliste) - valeurs lues depuis le fichier txt.
/// @return SimWorld_t* world - monde de simulation.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie) {
    SimWorld_t* world = malloc(sizeof(SimWorld_t));
    world->habitations = liste_alloc();
    world->centrales = liste_alloc();
    world->chateaux = liste_alloc();
    world->casernes = liste_alloc();
    world->casernes = liste_alloc();
    world->nb_total_habitants = 0;

    // mise à zéro de la carte.
    for (int i = 0; i < SIM_MAP_LARGEUR; i++) {
        for (int j = 0; j < SIM_MAP_HAUTEUR; j++) {
            world->map[i][j].donnees = NULL;
            world->map[i][j].type = KIND_VIDE;
            world->map[i][j].connexe_eau = 0;
            world->map[i][j].connexe_elec = 0;
            world->map[i][j].sprite_terrain = rand_sprite_terrain();
        }
    }

    world->monnaie = monnaie;
    world->rules = rules;
    world->n_ticks = 0;
    world->qte_dispo_eau = 0;
    world->qte_dispo_elec = 0;
    world->qte_max_eau = 0;
    world->qte_max_elec = 0;
    world->sim_running = true;

    return world;
}

/// Détruit un monde de simulation.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_world_destroy(SimWorld_t* world) {
    liste_free(world->habitations);
    liste_free(world->centrales);
    liste_free(world->chateaux);
    liste_free(world->casernes);
    free(world);
}

/// Avance d'une étape la simulation du monde.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_world_step(SimWorld_t* world) {

    if (!world->sim_running)
        return;

    world->n_ticks++;
    world->nb_total_habitants = 0;

    /// évolution et récolte des impôts des habitations
    struct Maillon_t *maisons = world->habitations->premier;
    while (maisons) {
        Habitation_t *hab = (Habitation_t *) maisons->data;
        world->monnaie += habitation_step(hab, world->rules);
        world->nb_total_habitants += habitation_get_nb_habitants(hab);
        maisons = maisons->next;
    }

    /// quatrième étape: sim des capacités d'évolution des bâtiments.
}

/// Remet à zéro la répartition de l'eau et de l'électricité pour les bâtiments.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation
/// @return void.
void sim_reset_flow_distribution(SimWorld_t* world) {
    struct Maillon_t *maisons = world->habitations->premier;
    while (maisons) {
        Habitation_t *hab = (Habitation_t *) maisons->data;
        hab->eau = 0;
        hab->electricite = 0;
        maisons = maisons->next;
    }

    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        centrale_step((CentraleElectrique_t *) centrales->data, world->rules);
        centrales = centrales->next;
    }

    struct Maillon_t* chateau_eau = world->chateaux->premier;
    while (chateau_eau) {
        chateau_step((ChateauEau_t *) chateau_eau->data, world->rules);
        chateau_eau = chateau_eau->next;
    }
}

void sim_step_resources(SimWorld_t* world) {
    world->qte_dispo_eau = 0;
    world->qte_dispo_elec = 0;
    world->qte_max_eau = 0;
    world->qte_max_elec = 0;

    sim_reset_flow_distribution(world);

    {
        /// maj des qte d'eau et d'électricité
        struct Maillon_t *chateaux = world->chateaux->premier;
        while (chateaux) {
            world->qte_dispo_eau += ((ChateauEau_t *) chateaux->data)->capacite;
            world->qte_max_eau += CAPACITE_CHATEAU_EAU;
            chateaux = chateaux->next;
        }
    }

    if (world->rules == Communiste_t)
    {
        {
            /// l'eau qui reste pour la deuxieme passe.
            int remaining_water = world->qte_dispo_eau;
            struct Maillon_t *chateaux = world->chateaux->premier;
            while (chateaux) {
                ChateauEau_t *chateau = (ChateauEau_t *) chateaux->data;
                chateau_step_communist(chateau, &remaining_water);
                chateaux = chateaux->next;
            }

            world->qte_dispo_eau = remaining_water;
        }
    }



    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        world->qte_max_elec += CAPACITE_CENTRALE_ELECTRIQUE;
        world->qte_dispo_elec += ((CentraleElectrique_t*)centrales->data)->capacite;
        centrales = centrales->next;
    }

    if (world->rules == Communiste_t)
    {
        {
            /// l'électricité qui reste pour la deuxieme passe.
            int remaining_elec = world->qte_dispo_elec;
            struct Maillon_t *centrales = world->centrales->premier;
            while (centrales) {
                CentraleElectrique_t *centrale = (CentraleElectrique_t *) centrales->data;
                centrale_step_communist(centrale, &remaining_elec);
                centrales = centrales->next;
            }

            world->qte_dispo_elec = remaining_elec;
        }
    }
}

/// Place une entité dans la carte de la simulation aux coordonnées données.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param type - type de case de la simulation du monde (Habitation, route, terrain, ...).
/// @param x, y - coordonnées en isométrique du placement sur le monde de simulation.
/// @param reload - si l'entité placée est une centrale, caserne, château d'eau alors permet d'actualiser ses voisins.
/// @return void.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y, bool reload) {
    switch (type) {
        case KIND_HABITATION:
        {
            NiveauHabitation_t def_lvl = world->rules == Capitaliste_t ? NIVEAU_TERRAIN_VAGUE_CAP : NIVEAU_TERRAIN_VAGUE;
            Habitation_t* habitation = habitation_alloc(def_lvl);
            habitation->position = (Vector2I) {x, y};

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    world->map[x + i][y + j].type = KIND_HABITATION;
                    world->map[x + i][y + j].donnees = habitation;
                }
            }

            liste_ajout_tri(world->habitations, habitation, habitation_tri_par_distance);
        }
        break;

        case KIND_CENTRALE:
        {
            CentraleElectrique_t* centrale = centrale_alloc();
            centrale->position = (Vector2I) {x, y};
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 4; ++j) {
                    world->map[x + i][y + j].type = KIND_CENTRALE;
                    world->map[x + i][y + j].donnees = centrale;
                }
            }

            liste_ajouter_fin(world->centrales, centrale);
        }
        break;

        case KIND_CHATEAU: {
            ChateauEau_t* chateau = chateau_alloc();
            chateau->position = (Vector2I) {x, y};
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 6; ++j) {
                    world->map[x + i][y + j].type = KIND_CHATEAU;
                    world->map[x + i][y + j].donnees = chateau;
                }
            }

            liste_ajouter_fin(world->chateaux, chateau);
        }
        break;

        case KIND_CASERNE: {
            CasernePompier_t *casernes = alloc_caserne();
            casernes->position = (Vector2I) {x, y};
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 4; ++j) {
                    world->map[x + i][y + j].type = KIND_CASERNE;
                    world->map[x + i][y + j].donnees = casernes;
                }
            }
            liste_ajouter_fin(world->casernes, casernes);
            break;
        }


            case KIND_ROUTE: {
            world->map[x][y].type = KIND_ROUTE;
            world->map[x][y].donnees = NULL;
        }
        break;

        default:
            break;
    }

    if (reload)
        sim_update_voisins(world);
}

/// Vérifie si un bâtiment de dimensions précisées peut être placé à une position donnée.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param isBat - différencie le placement d'une route (1X1) et d'un bâtiment (3X3, 4X6, 6X4) où il faut vérifier les cases adjacentes pour placer l'entité.
/// @param x, y - coordonnées en isométrique du placement sur le monde de simulation.
/// @param w, h - hauteur et largeur de l'entité à placer.
/// @return booléen - true si le placement de l'entité est possible - false sinon.
bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h) {
    // Si le bâtiment dépasse du terrain, on ne peut pas le placer.
    if (x < 0 || y < 0 || x + w > SIM_MAP_LARGEUR || y + h > SIM_MAP_HAUTEUR)
        return false;

    // on vérifie d'abord que la surface de la grille ou l'on veut placer le bâtiment est vide.
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (world->map[x + i][y + j].type != KIND_VIDE)
                return false;
        }
    }

    if (isBat) {
        // on vérifie ensuite que les cases adjacentes sont vides.
        for (int i = 0; i < w; ++i) {
            if (world->map[x + i][y - 1].type == KIND_ROUTE || world->map[x + i][y + h].type == KIND_ROUTE)
                return true;
        }

        for (int i = 0; i < h; ++i) {
            if (world->map[x - 1][y + i].type == KIND_ROUTE || world->map[x + w][y + i].type == KIND_ROUTE)
                return true;
        }
    } else
        return true;

    return false;
}

/// Détruit l'entité sélectionnée.
/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @param x, y - coordonnées en isométrique de la destruction sur le monde de simulation.
/// @return void.
void sim_destroy_entity(SimWorld_t* world, int x, int y) {
    if (x >= SIM_MAP_LARGEUR || y >= SIM_MAP_HAUTEUR || x < 0 || y < 0)
        return;

    if (world->map[x][y].type != KIND_VIDE) {
        switch (world->map[x][y].type) {
            case KIND_HABITATION:
            {
                Habitation_t* habitation = (Habitation_t *) world->map[x][y].donnees;
                liste_supprimer(world->habitations, habitation);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        world->map[habitation->position.x + i][habitation->position.y + j].type = KIND_VIDE;
                        world->map[habitation->position.x + i][habitation->position.y + j].donnees = NULL;
                    }
                }
                habitation_free(habitation);
            }
            break;

            case KIND_CENTRALE:
            {
                CentraleElectrique_t* centrale = (CentraleElectrique_t *) world->map[x][y].donnees;
                liste_supprimer(world->centrales, centrale);
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        world->map[centrale->position.x + i][centrale->position.y + j].type = KIND_VIDE;
                        world->map[centrale->position.x + i][centrale->position.y + j].donnees = NULL;
                    }
                }
                centrale_free(centrale);
            }
            break;

            case KIND_CHATEAU:
            {
                ChateauEau_t* chateau = (ChateauEau_t *) world->map[x][y].donnees;
                liste_supprimer(world->chateaux, chateau);
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        world->map[chateau->position.x + i][chateau->position.y + j].type = KIND_VIDE;
                        world->map[chateau->position.x + i][chateau->position.y + j].donnees = NULL;
                    }
                }
                chateau_free(chateau);
            }
            break;

            case KIND_CASERNE:
            {
                CasernePompier_t* caserne = (CasernePompier_t *) world->map[x][y].donnees;
                liste_supprimer(world->casernes, caserne);
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        world->map[caserne->position.x + i][caserne->position.y + j].type = KIND_VIDE;
                        world->map[caserne->position.x + i][caserne->position.y + j].donnees = NULL;
                    }
                }
                caserne_free(caserne);
            }
                break;

            case KIND_ROUTE: {
                world->map[x][y].type = KIND_VIDE;
                world->map[x][y].donnees = NULL;
            }
            break;

            default:
                break;
        }

        sim_update_voisins(world);
    }
}

/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_update_voisins(SimWorld_t* world) {
    struct Maillon_t* habs = world->habitations->premier;
    while (habs) {
        ((Habitation_t*)habs->data)->alimentee_en_eau = false;
        ((Habitation_t*)habs->data)->alimentee_en_electricite = false;
        ((Habitation_t*)habs->data)->relie_caserne = false;
        habs = habs->next;
    }

    for (int i = 0; i < SIM_MAP_LARGEUR; ++i) {
        for (int j = 0; j < SIM_MAP_HAUTEUR; ++j) {
            world->map[i][j].connexe_eau = false;
            world->map[i][j].connexe_elec = false;
            world->map[i][j].connexe_caserne = false;
        }
    }

    sim_update_voisins_chateaux(world);
    sim_update_voisins_centrales(world);
    sim_update_voisins_casernes(world);
}

/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_update_voisins_chateaux(SimWorld_t* world) {
    struct Maillon_t* chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t* chateau = chateaux->data;

        /// on vide la liste des chemins calculés.
        vector_free_clear(chateau->habitations);

        /// on fait le BFS depuis le point mentionné
        bfs(world, chateau->position, chateau, chateau->habitations, bfs_visiteur_connexite_eau);

        /// on ajoute les chemins
        for (int i = 0; i < chateau->habitations->taille; ++i) {
            HabitationNode_t* node = chateau->habitations->data[i];
            /// on marque que l'habitation est connectée au réseau éléctrique.
            node->habitation->alimentee_en_eau = true;
        }

        chateaux = chateaux->next;
    }
}

/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_update_voisins_centrales(SimWorld_t* world) {
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centrale = centrales->data;

        vector_free_clear(centrale->habitations);

        bfs(world, centrale->position, centrale, centrale->habitations, bfs_visiteur_connexite_elec);

        for (int i = 0; i < centrale->habitations->taille; ++i) {
            HabitationNode_t* node = centrale->habitations->data[i];
            node->habitation->alimentee_en_electricite = true;
        }

        centrales = centrales->next;
    }
}

/// @param world - adresse de structure world allouée dynamiquement - monde de simulation.
/// @return void.
void sim_update_voisins_casernes(SimWorld_t* world) {
    struct Maillon_t* casernes = world->casernes->premier;
    while (casernes) {
        CasernePompier_t* caserne = casernes->data;

        vector_free_clear(caserne->habitations);

        bfs(world, caserne->position, caserne, caserne->habitations, bfs_visiteur_connexite_caserne);

        casernes = casernes->next;
    }
}

/// Fonction visiteuse de noeuds qui définit la connexité d'une habitation / route au réseau des casernes.
/// @param caseActuelle - adresse de structure Case_t - case sur laquelle s'effectue le bfs.
/// @param distance - int - distance à laquelle se trouve la caserne de la caseActuelle
/// @param resultats - adresse de structure Vector_t - ?
/// @param batInitial - void* pointeur sur structure CasernePompier_t - permet de connaître le bâtiment depuis lequel on effectue le parcours en largeur.
/// @return booléen - true si l'habitation de la caseActuelle est à moins de 20 blocs d'une caserne - false sinon.
bool bfs_visiteur_connexite_caserne(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial) {
    if (caseActuelle->type == KIND_ROUTE){
        caseActuelle->connexe_caserne = true;
    }

    if (caseActuelle->type == KIND_HABITATION) {
        Habitation_t* hab = (Habitation_t*) caseActuelle->donnees;
        if (distance <= 20) {
            hab->relie_caserne = true;
            return bfs_visiteur_habitation(caseActuelle, distance, resultats, batInitial);
        }
    }
    return false;
}

/// Fonction visiteuse de noeuds qui définit la connexité d'une habitation / route au réseau d'eau.
/// @param caseActuelle - adresse de structure Case_t - case sur laquelle s'effectue le bfs.
/// @param distance - int - distance à laquelle se trouve la caserne de la caseActuelle
/// @param resultats - adresse de structure Vector_t - ?
/// @param batInitial - void* pointeur sur structure CasernePompier_t - permet de connaître le bâtiment depuis lequel on effectue le parcours en largeur.
/// @return booléen - true si l'habitation est connectée au réseau d'eau - false sinon.
bool bfs_visiteur_connexite_eau(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial) {
    if (caseActuelle->type == KIND_ROUTE)
        caseActuelle->connexe_eau = true;

    return bfs_visiteur_habitation(caseActuelle, distance, resultats, batInitial);
}

/// Fonction visiteuse de noeuds qui définit la connexité d'une habitation / route au réseau électrique.
/// @param caseActuelle - adresse de structure Case_t - case sur laquelle s'effectue le bfs.
/// @param distance - int - distance à laquelle se trouve la caserne de la caseActuelle
/// @param resultats - adresse de structure Vector_t - ?
/// @param batInitial - void* pointeur sur structure CasernePompier_t - permet de connaître le bâtiment depuis lequel on effectue le parcours en largeur.
/// @return booléen - true si l'habitation est connectée au réseau électrique - false sinon.
bool bfs_visiteur_connexite_elec(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batInitial) {
    if (caseActuelle->type == KIND_ROUTE)
        caseActuelle->connexe_elec = true;

    return bfs_visiteur_habitation(caseActuelle, distance, resultats, batInitial);
}