#include "sauvegarde.h"
#include "screens/gameplay.h"
#include "stdio.h"
#include "stdlib.h"
#include <dirent.h>
#include "time.h"
#include "assert.h"

/// Donne la date de la sauvegarde effectuée.
/// @param gameplay - structure générale du jeu.
/// @return void.
void get_time_sauvegarde(GameplayScreen_t *gameplay) {
    time_t t;
    time(&t);

    gameplay->state.stateToolbar.saveHistory.sauvegardes_time[gameplay->state.stateToolbar.saveHistory.nb_sauvegardes] = ctime(
            &t);
}

/// Fonction qui trouve les noms et le nombre de sauvegardes dans le dossier du jeu.
/// @return int - nombre de sauvegardes dans le dossier de sauvegarde.
int nombredeSauvegardes(GameplayScreen_t *gameplay) {
    int nbSauvegarde = 0, compteur = 0, i;

    struct dirent *dir;
    DIR *d = opendir(SAVE_DIRECTORY_PATH);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (compteur > 1) {
                strcpy(gameplay->state.stateToolbar.saveHistory.nom_sauvegardes[nbSauvegarde], dir->d_name);
                nbSauvegarde++;
            }
            compteur++;
        }
        closedir(d);
    }

    return (nbSauvegarde);
}

void update_nom_nb_sauvegardes(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.stateMenuSave.resetNbSauvegardes) {
        gameplay->state.stateToolbar.saveHistory.nb_sauvegardes = nombredeSauvegardes(gameplay);
        gameplay->state.stateToolbar.stateMenuSave.resetNbSauvegardes = false;
    }
}

void ouvrirFichier(GameplayScreen_t *gameplayScreen, const char *nomFichier) {
    sim_world_destroy(gameplayScreen->world);
    gameplayScreen->world = sim_world_create(0, Communiste_t);
    sim_charger(gameplayScreen->world, nomFichier);
}

void sauvegarder_partie(GameplayScreen_t *gameplayScreen) {
    char chemin[100];
    const char *extension = ".txt";

    if (!DirectoryExists(SAVE_DIRECTORY_PATH))
        mkdir(SAVE_DIRECTORY_PATH);

    sprintf(chemin, SAVE_DIRECTORY_PATH"%s%s", gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier, extension);
    printf("CHEMIN DE SAVE : %s", chemin);
    sim_sauvegarder(gameplayScreen->world, chemin);
}


char hab2char(Habitation_t *hab) {
    switch (hab->niveau) {
        case NIVEAU_RUINE:
            return 'R';
        case NIVEAU_TERRAIN_VAGUE:
            return 'V';
        case NIVEAU_CABANE:
            return 'C';
        case NIVEAU_GRATTE_CIEL:
            return 'G';
        case NIVEAU_MAISON:
            return 'M';
        case NIVEAU_IMMEUBLE:
            return 'I';
        case NIVEAU_IMMEUBLE_CAP:
            return 'i';
        case NIVEAU_MAISON_CAP:
            return 'm';
        case NIVEAU_CABANE_CAP:
            return 'c';
        case NIVEAU_TERRAIN_VAGUE_CAP:
            return 'v';
    }
}

NiveauHabitation_t char2hab(char c) {
    switch (c) {
        case 'R':
            return NIVEAU_RUINE;
        case 'V':
            return NIVEAU_TERRAIN_VAGUE;
        case 'C':
            return NIVEAU_CABANE;
        case 'G':
            return NIVEAU_GRATTE_CIEL;
        case 'M':
            return NIVEAU_MAISON;
        case 'I':
            return NIVEAU_IMMEUBLE;
        case 'i':
            return NIVEAU_IMMEUBLE_CAP;
        case 'v':
            return NIVEAU_TERRAIN_VAGUE_CAP;
        case 'c':
            return NIVEAU_CABANE_CAP;
        case 'm':
            return NIVEAU_MAISON_CAP;
        default:
            break;
    }
}

struct bat_data {
    CaseKind_t type;
    int extra; // données supplémentaires
};

void sim_charger(SimWorld_t *world, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    assert(fichier != NULL && "Impossible d'ouvrir le fichier de sauvegarde pour lecture.");

    struct bat_data data[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {0};

    /// on charge depuis le fichier texte les positions des batiments dans une matrice
    /// on écrit directement dans le monde les routes.
    for (int i = 0; i < SIM_MAP_HAUTEUR;) {
        for (int j = 0; j < SIM_MAP_LARGEUR;) {
            char cs = fgetc(fichier);
            switch (cs) {
                case '0':
                    world->map[j][i].type = KIND_VIDE;
                    ++j;
                    break;

                case 'l':
                    world->map[j][i].type = KIND_ROUTE;
                    ++j;
                    break;

                case 'J':
                    data[j][i].type = KIND_CENTRALE;
                    ++j;
                    break;

                case 'W':
                    data[j][i].type = KIND_CHATEAU;
                    ++j;
                    break;

                case 'R':
                case 'V':
                case 'C':
                case 'G':
                case 'M':
                case 'I':
                case 'i':
                case 'm':
                case 'c':
                case 'v': {
                    data[j][i].type = KIND_HABITATION;
                    data[j][i].extra = char2hab(cs);
                    ++j;
                }
                    break;

                case 'P': {
                    data[j][i].type = KIND_CASERNE;
                    ++j;
                }

                default:
                    break;
            }
        }
        i++;
    }

    fscanf(fichier, "%d", &world->monnaie);
    fscanf(fichier, "%d", &world->n_ticks);
    fscanf(fichier, "%d", &world->rules);

    bool visited[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {false};

    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            if (!visited[j][i]) {
                switch (data[j][i].type) {
                    case KIND_HABITATION: {
                        for (int k = 0; k < 3; ++k) {
                            for (int l = 0; l < 3; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_HABITATION, j, i, false);
                        ((Habitation_t *) world->map[j][i].donnees)->niveau = data[j][i].extra;
                    }
                        break;
                    case KIND_CENTRALE: {
                        for (int k = 0; k < 6; ++k) {
                            for (int l = 0; l < 4; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_CENTRALE, j, i, false);
                    }
                        break;
                    case KIND_CHATEAU: {
                        for (int k = 0; k < 4; ++k) {
                            for (int l = 0; l < 6; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_CHATEAU, j, i, false);
                    }
                        break;

                    case KIND_CASERNE: {
                        for (int k = 0; k < 6; ++k) {
                            for (int l = 0; l < 4; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_CASERNE, j, i, false);
                    }
                        break;

                    default:
                        break;
                }
            }
        }
    }

    sim_update_voisins(world);

    fclose(fichier);
}

void sim_sauvegarder(SimWorld_t *world, const char *nomFichier) {
    ensure_save_directory_exists();

    FILE *fichier = fopen(nomFichier, "w+");
    assert(fichier != NULL && "Impossible d'ouvrir le fichier de sauvegarde pour écriture.");
    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            switch (world->map[j][i].type) {
                case KIND_VIDE:
                    fprintf(fichier, "0");
                    break;
                case KIND_ROUTE:
                    fprintf(fichier, "l");
                    break;
                case KIND_HABITATION: {
                    Habitation_t *hab = world->map[j][i].donnees;
                    fprintf(fichier, "%c", hab2char(hab));
                }
                    break;
                case KIND_CENTRALE:
                    fprintf(fichier, "J");
                    break;
                case KIND_CHATEAU:
                    fprintf(fichier, "W");
                    break;
                case KIND_CASERNE:
                    fprintf(fichier, "P");
                    break;
                default:
                    break;
            }
        }
        fprintf(fichier, "\n");
    }
    /// monnaie
    fprintf(fichier, "%d\n", world->monnaie);
    /// temps ecoule
    fprintf(fichier, "%d\n", world->n_ticks);
    /// mode de jeu
    fprintf(fichier, "%d\n", world->rules);

    fflush(fichier);
    fclose(fichier);
}

void ensure_save_directory_exists() {
    mkdir(SAVE_DIRECTORY_PATH);
}

void afficher_saisie_nom_fichier(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.stateMenuSave.modeAjout) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.75f));
        DrawRectangleRounded((Rectangle) {200, 300, 1200, 300}, 0.1f, 8, (Color) {0, 194, 255, 255});
        DrawText("Saisir le nom de la sauvegarde :", 420, 315, 48, WHITE);
        DrawRectangleRounded((Rectangle) {350, 400, 900, 150}, 0.1f, 8, WHITE);
        DrawText(TextFormat("%s.txt", gameplay->state.stateToolbar.stateMenuSave.nomFichier), 475, 430, 30, BLACK);
    }
}

void saisir_nom_fichier_sauvegarde(GameplayScreen_t *gameplayScreen) {
    if (gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout) {
        char touche = GetCharPressed();
        int key = GetKeyPressed();

        if (key == KEY_BACKSPACE) {
            gameplayScreen->state.stateToolbar.stateMenuSave.indice--;
            gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[gameplayScreen->state.stateToolbar.stateMenuSave.indice] = '\0';
        } else if (key == KEY_ENTER) {
            get_time_sauvegarde(gameplayScreen);
            sauvegarder_partie(gameplayScreen);
            gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout = false;
        } else if (touche != '\0' && gameplayScreen->state.stateToolbar.stateMenuSave.indice < 10) {
            gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[strlen(
                    gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier)] = touche;
            gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[
                    gameplayScreen->state.stateToolbar.stateMenuSave.indice + 1] = '\0';
            gameplayScreen->state.stateToolbar.stateMenuSave.indice++;
        }
    }
}

void update_composant_sauvegarde(GameplayScreen_t *gameplay, Vector2 pos, int i) {
    if (CheckCollisionPointRec(pos, (Rectangle) {150, 186 + 100 * (float) i, 1300, 80})) {
        /// On sélectionne une sauvegarde
        gameplay->state.stateToolbar.stateMenuSave.num_component_hover = i;
        gameplay->state.stateToolbar.stateMenuSave.hoverComponent = true;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(pos, (Rectangle) {150, 186 + 100 * (float) i, 1300, 80})) {
            /// On sélectionne une sauvegarde
            gameplay->state.stateToolbar.stateMenuSave.num_component_select = i;
            gameplay->state.stateToolbar.stateMenuSave.select_component = true;
        }
    }
}

void update_menu_sauvegarde(GameplayScreen_t *gameplay) {

    update_nom_nb_sauvegardes(gameplay);

    if (gameplay->state.stateToolbar.stateMenuSave.modeSave) {
        gameplay->state.stateToolbar.stateMenuSave.hoverComponent = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverAdd = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverCancel = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverSel = false;
        gameplay->state.stateToolbar.stateMenuSave.clickAdd = false;
        gameplay->state.stateToolbar.stateMenuSave.clickSel = false;
        gameplay->state.stateToolbar.stateMenuSave.clickCancel = false;

        saisir_nom_fichier_sauvegarde(gameplay);

        Vector2 pos = (Vector2) {GetMouseX(), GetMouseY()};
        if (CheckCollisionPointRec(pos, (Rectangle) {1393, 108, 40, 40})) {
            /// On sauvegarde la partie actuelle
            gameplay->state.stateToolbar.stateMenuSave.hoverAdd = true;
        }

        if (CheckCollisionPointRec(pos, (Rectangle) {820, 803, 40, 40})) {
            /// On charge la partie sélectionnée
            gameplay->state.stateToolbar.stateMenuSave.hoverSel = true;
        }

        if (CheckCollisionPointRec(pos, (Rectangle) {740, 803, 40, 40})) {
            /// On désélectionne la partie sélectionnée
            gameplay->state.stateToolbar.stateMenuSave.hoverCancel = true;
        }

        for (int i = 0; i < gameplay->state.stateToolbar.saveHistory.nb_sauvegardes; i++) {
            update_composant_sauvegarde(gameplay, pos, i);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(pos, (Rectangle) {1393, 108, 40, 40})) {
                /// On sauvegarde la partie actuelle
                gameplay->state.stateToolbar.stateMenuSave.clickAdd = true;
                gameplay->state.stateToolbar.stateMenuSave.modeAjout = true;
                gameplay->state.stateToolbar.stateMenuSave.indice = 0;
                strcpy(gameplay->state.stateToolbar.stateMenuSave.nomFichier, "");

            }

            if (CheckCollisionPointRec(pos, (Rectangle) {820, 803, 40, 40})) {
                /// On charge la partie sélectionnée
                gameplay->state.stateToolbar.stateMenuSave.clickSel = true;
                if (gameplay->state.stateToolbar.stateMenuSave.num_component_select != -1 &&
                    gameplay->state.stateToolbar.stateMenuSave.select_component) {
                    strcpy(gameplay->state.stateToolbar.stateMenuSave.nomFichierOuverture,
                           gameplay->state.stateToolbar.saveHistory.nom_sauvegardes[gameplay->state.stateToolbar.stateMenuSave.num_component_select]);
                    gameplay->state.stateToolbar.stateMenuSave.modeSave = false;
                    /// chargement de partie
                    ouvrirFichier(gameplay, TextFormat("%s%s", SAVE_DIRECTORY_PATH,
                                                       gameplay->state.stateToolbar.stateMenuSave.nomFichierOuverture));
                }
            }

            if (CheckCollisionPointRec(pos, (Rectangle) {740, 803, 40, 40})) {
                /// On désélectionne la partie sélectionnée et on sort du menu sauvegarde
                gameplay->state.stateToolbar.stateMenuSave.clickCancel = true;
                gameplay->state.stateToolbar.stateMenuSave.modeSave = false;
            }
        }
    }
}

void affichage_composant_sauvegarde(GameplayScreen_t *gameplay, int i) {
    Color color = (gameplay->state.stateToolbar.stateMenuSave.num_component_hover == i) &&
                  gameplay->state.stateToolbar.stateMenuSave.hoverComponent ? (Color) {98, 98, 98, 200} : (Color) {237,
                                                                                                                   225,
                                                                                                                   225,
                                                                                                                   240};
    if ((gameplay->state.stateToolbar.stateMenuSave.num_component_select == i) &&
        gameplay->state.stateToolbar.stateMenuSave.select_component) {
        color = (Color) {60, 60, 60, 200};
    }
    DrawRectangleRounded((Rectangle) {150, 186 + 100 * (float) i, 1300, 80}, 0.1f, 8, color);
    DrawText(TextFormat("%#d - %s", i, gameplay->state.stateToolbar.saveHistory.nom_sauvegardes[i]), 160, 196 + 100 * i,
             48, BLACK);
}

void affichage_menu_sauvegarde(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.stateMenuSave.modeSave) {

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.75f));

        DrawRectangleRounded((Rectangle) {100, 68, 1400, 800}, 0.1f, 8, (Color) {0, 194, 255, 220});
        DrawText("Menu Sauvegarde :", 575, 108, 48, WHITE);

        for (int i = 0; i < gameplay->state.stateToolbar.saveHistory.nb_sauvegardes; i++) {
            affichage_composant_sauvegarde(gameplay, i);
        }

        if (gameplay->state.stateToolbar.stateMenuSave.hoverCancel) {
            DrawCircle(761, 824, 30, (Color) {0, 0, 0, 20});
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickCancel) {
            DrawCircle(761, 824, 30, (Color) {0, 0, 0, 45});
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_CANCEL], 740, 803,
                    gameplay->state.stateToolbar.stateMenuSave.clickCancel ? YELLOW : WHITE);
        if (gameplay->state.stateToolbar.stateMenuSave.hoverSel) {
            DrawCircle(841, 824, 30, (Color) {0, 0, 0, 20});
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickSel) {
            DrawCircle(841, 824, 30, (Color) {0, 0, 0, 45});
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_CHECK], 820, 803,
                    gameplay->state.stateToolbar.stateMenuSave.clickSel ? YELLOW : WHITE);
        if (gameplay->state.stateToolbar.stateMenuSave.hoverAdd) {
            DrawCircle(1414, 129, 30, (Color) {0, 0, 0, 20});
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickAdd) {
            DrawCircle(1414, 129, 30, (Color) {0, 0, 0, 45});
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_ADD], 1393, 108,
                    gameplay->state.stateToolbar.stateMenuSave.clickAdd ? YELLOW : WHITE);

        afficher_saisie_nom_fichier(gameplay);

    }
}