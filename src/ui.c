#include <stdio.h>
#include "ui.h"
#include "jeu.h"

const char* timeToDate(SimWorld_t* s) {
    const char* months[] = { "JAN", "FEV", "MAR", "AVR", "MAI", "JUN", "JUL", "AOU", "SEP", "OCT", "NOV", "DEC" };

    int year = (s->n_ticks / N_TICKS_EVOLUTION) / 12;
    int month = (s->n_ticks / N_TICKS_EVOLUTION) % 12;
    return TextFormat("%s %d", months[month], (s->rules == Communiste_t ? 1949 : 2000) + year);
}

void draw_affichage_niveaux(UIState* textures){
    DrawRectangleRounded((Rectangle) {15, 830, 300, 75}, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    if (textures->stateToolbar.hoverNiveauNormal) {
        DrawCircle(58, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->affichageNiveau == AFFICHAGE_NIVEAU_NONE) {
        DrawCircle(58, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_GRID], 40, 851, textures->affichageNiveau == AFFICHAGE_NIVEAU_NONE ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverNiveauElectricite) {
        DrawCircle(168, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->affichageNiveau == AFFICHAGE_NIVEAU_ELEC) {
        DrawCircle(168, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_ELECTRICITY_GRID], 150, 851, textures->affichageNiveau == AFFICHAGE_NIVEAU_ELEC ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverNiveauEau) {
        DrawCircle(283, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->affichageNiveau == AFFICHAGE_NIVEAU_EAU) {
        DrawCircle(283, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_WATER_GRID], 265, 851, textures->affichageNiveau == AFFICHAGE_NIVEAU_EAU ? YELLOW : WHITE);

}

void ui_charger_textures(UIState* textures) {
    textures->toolbarIcons[ICON_HAMBURGER] = LoadTexture("../assets/textures/icones/hamburger.png");
    textures->toolbarIcons[ICON_SAVE] = LoadTexture("../assets/textures/icones/save.png");
    textures->toolbarIcons[ICON_PEOPLE] = LoadTexture("../assets/textures/icones/people.png");
    textures->toolbarIcons[ICON_ENERGY] = LoadTexture("../assets/textures/icones/energy.png");
    textures->toolbarIcons[ICON_WATER] = LoadTexture("../assets/textures/icones/water.png");
    textures->toolbarIcons[ICON_BUILD] = LoadTexture("../assets/textures/icones/build.png");
    textures->toolbarIcons[ICON_DESTROY] = LoadTexture("../assets/textures/icones/destroy.png");
    textures->toolbarIcons[ICON_TIME] = LoadTexture("../assets/textures/icones/time.png");
    textures->toolbarIcons[ICON_ROAD] = LoadTexture("../assets/textures/icones/road.png");
    textures->toolbarIcons[ICON_HABITATION] = LoadTexture("../assets/textures/icones/house.png");
    textures->toolbarIcons[ICON_CENTRALE] = LoadTexture("../assets/textures/icones/industry.png");
    textures->toolbarIcons[ICON_CHATEAU] = LoadTexture("../assets/textures/icones/valve.png");
    textures->toolbarIcons[ICON_GRID] = LoadTexture("../assets/textures/icones/grid.png");
    textures->toolbarIcons[ICON_WATER_GRID] = LoadTexture("../assets/textures/icones/water_grid.png");
    textures->toolbarIcons[ICON_ELECTRICITY_GRID] = LoadTexture("../assets/textures/icones/electricity_grid.png");
    textures->toolbarIcons[ICON_CHECK] = LoadTexture("../assets/textures/icones/check.png");
    textures->toolbarIcons[ICON_CANCEL] = LoadTexture("../assets/textures/icones/cancel.png");
    textures->toolbarIcons[ICON_ADD] = LoadTexture("../assets/textures/icones/add.png");
    textures->toolbarIcons[ICON_CASERNE] = LoadTexture("../assets/textures/icones/caserne-de-pompiers.png");
    textures->toolbarIcons[ICON_PAUSE] = LoadTexture("../assets/textures/icones/pause.png");
}

void ui_draw_toolbar(UIState* states, SimWorld_t* sim) {
    DrawRectangle(0, 924, FENETRE_JEU_LARGEUR, 100, (Color) { 0, 194, 255, 191 });

    DrawRectangle(271, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(493, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(717, 954, 125, 40, (Color) { 238,238,238,200});

    DrawText(TextFormat("%d", sim->nb_total_habitants), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d / %d", sim->qte_dispo_elec, sim->qte_max_elec), 493, 954, 20, (Color) {0, 0, 0, 255 });
    DrawText(TextFormat("%d / %d", sim->qte_dispo_eau, sim->qte_max_eau), 717, 954, 20, (Color) {0, 0, 0, 255 });

    DrawTexture(states->toolbarIcons[ICON_HAMBURGER], 26, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_SAVE], 109, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_WATER], 668, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_PAUSE], 892, 954, sim->sim_running ? WHITE : ORANGE);
    DrawTexture(states->toolbarIcons[ICON_DESTROY], 1376, 954, states->currentBuildMode == BUILD_MODE_DESTROY ? YELLOW : WHITE);

    /// icône de l'echelle de temps.
    Color timeColor = WHITE;
    if (states->timeScale > 1.0f) {
        timeColor = YELLOW;
        DrawCircle(1483, 971, 35 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(states->toolbarIcons[ICON_TIME], 1466, 954, timeColor);
    DrawText(TextFormat("x%d", (int)states->timeScale), 1486, 994, 16, timeColor);

    /// icônes random
    DrawTexture(states->toolbarIcons[ICON_HAMBURGER], 26, 954, states->stateToolbar.stateMenuSave.modeMenu ? YELLOW : WHITE);
    DrawTexture(states->toolbarIcons[ICON_SAVE], 109, 954, states->stateToolbar.stateMenuSave.modeSave ? YELLOW : WHITE);
    DrawTexture(states->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(states->toolbarIcons[ICON_WATER], 668, 954, WHITE);


    if (states->currentBuildMode == BUILD_MODE_DESTROY)
        DrawCircle(1395, 975, 30 , (Color) { 0, 0, 0, 45 });
    DrawTexture(states->toolbarIcons[ICON_DESTROY], 1376, 954, states->currentBuildMode == BUILD_MODE_DESTROY ? YELLOW : WHITE);

    if (states->currentBuildMode == BUILD_MODE_ROUTE)
        DrawCircle(1030, 970, 30, (Color) { 0, 0, 0, 45 });
    DrawTexture(states->toolbarIcons[ICON_ROAD], 1012, 954, states->currentBuildMode == BUILD_MODE_ROUTE ? YELLOW : WHITE);

    if (states->currentBuildMode == BUILD_MODE_HABITATION)
        DrawCircle(1105, 975, 30, (Color) { 0, 0, 0, 45 });
    DrawTexture(states->toolbarIcons[ICON_HABITATION], 1082, 954, states->currentBuildMode == BUILD_MODE_HABITATION ? YELLOW : WHITE);

    if (states->currentBuildMode == BUILD_MODE_CENTRALE)
        DrawCircle(1180, 975, 30, (Color) { 0, 0, 0, 45 });
    DrawTexture(states->toolbarIcons[ICON_CENTRALE], 1159, 954, states->currentBuildMode == BUILD_MODE_CENTRALE ? YELLOW : WHITE);

    if (states->currentBuildMode == BUILD_MODE_CHATEAU)
        DrawCircle(1247, 975, 30 ,  (Color) { 0, 0, 0, 45 });
    DrawTexture(states->toolbarIcons[ICON_CHATEAU], 1229, 954, states->currentBuildMode == BUILD_MODE_CHATEAU ? YELLOW : WHITE);

    if (states->currentBuildMode == BUILD_MODE_CASERNE)
        DrawCircle(1317, 975, 30, (Color) {0, 0, 0, 45});
    DrawTexture(states->toolbarIcons[ICON_CASERNE], 1297, 954, states->currentBuildMode == BUILD_MODE_CASERNE ? YELLOW : WHITE);

    // dessin du temps actuel
    DrawRectangleRounded((Rectangle) {
        .x = -5,
        .y = -5,
        .width = 200,
        .height = 50
    }, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    DrawText(timeToDate(sim), 10, 10, 24, WHITE);

    // dessin du temps réel écoulé.
    DrawRectangleRounded((Rectangle) {
        .x = 205,
        .y = -5,
        .width = 200,
        .height = 50
    }, 0.2f, 8, DARKGRAY);
    DrawText(TextFormat("%.2d:%.2d:%.2d", sim->n_ticks / 3600, (sim->n_ticks / 60) % 24, sim->n_ticks % 60), 215, 10, 24, WHITE);

    DrawRectangleRounded((Rectangle) {
            .x = FENETRE_JEU_LARGEUR - 195,
            .y = -5,
            .width = 200,
            .height = 50
    }, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    DrawText(TextFormat("%d £", sim->monnaie), FENETRE_JEU_LARGEUR - 190, 10, 24, WHITE);


    /// dessin du mode actuel.
    Color modeCol = sim->rules == Communiste_t ? RED : BLUE;
    const char *mode = sim->rules == Communiste_t ? "Communiste" : "Capitaliste";
    DrawRectangleRounded((Rectangle) {
            .x = FENETRE_JEU_LARGEUR - 415,
            .y = -5,
            .width = 200,
            .height = 50
    }, 0.2f, 8, modeCol);
    DrawText(mode, FENETRE_JEU_LARGEUR - 400, 10, 24, WHITE);

    if (states->stateToolbar.stateMenuSave.modeMenu)
        draw_affichage_niveaux(states);
}

void ui_update_toolbar(UIState* textures, SimWorld_t* sim) {
    Vector2 mousePos = GetMousePosition();


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        if (CheckCollisionPointRec(mousePos, (Rectangle) {26, 954, textures->toolbarIcons[ICON_HAMBURGER].width,
                                                          textures->toolbarIcons[ICON_HAMBURGER].height})) {
            textures->stateToolbar.stateMenuSave.modeMenu = !textures->stateToolbar.stateMenuSave.modeMenu;
            textures->stateToolbar.stateMenuSave.modeSave = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
            textures->stateToolbar.stateMenuSave.modeSave = !textures->stateToolbar.stateMenuSave.modeSave;
            if (textures->stateToolbar.stateMenuSave.modeSave)
                textures->stateToolbar.stateMenuSave.resetNbSauvegardes = true;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
        }

        if (textures->stateToolbar.stateMenuSave.modeSave)
            return;

        if (CheckCollisionPointRec(mousePos, (Rectangle) {211, 954, textures->toolbarIcons[ICON_PEOPLE].width,
                                                          textures->toolbarIcons[ICON_PEOPLE].height})) {
            printf("People\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {446, 954, textures->toolbarIcons[ICON_ENERGY].width,
                                                          textures->toolbarIcons[ICON_ENERGY].height})) {
            printf("Energy\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {668, 954, textures->toolbarIcons[ICON_WATER].width,
                                                          textures->toolbarIcons[ICON_WATER].height})) {
            printf("Water\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {
                892, 954,
                .width = textures->toolbarIcons[ICON_PAUSE].width,
                .height = textures->toolbarIcons[ICON_PAUSE].height
        })) {
            sim->sim_running = !sim->sim_running;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {892, 954, textures->toolbarIcons[ICON_BUILD].width,
                                                          textures->toolbarIcons[ICON_BUILD].height})) {
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_DESTROY ? BUILD_MODE_NONE
                                                                                           : BUILD_MODE_DESTROY);
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {

            textures->timeScale *= 2.0f;
            if (textures->timeScale >= 256.0f)
                textures->timeScale = 1.0f;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height})) {
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_ROUTE ? BUILD_MODE_NONE
                                                                                         : BUILD_MODE_ROUTE);
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})) {
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_HABITATION ? BUILD_MODE_NONE
                                                                                              : BUILD_MODE_HABITATION);
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})) {
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CENTRALE ? BUILD_MODE_NONE
                                                                                            : BUILD_MODE_CENTRALE);
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CHATEAU ? BUILD_MODE_NONE
                                                                                           : BUILD_MODE_CHATEAU);
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1297, 954, textures->toolbarIcons[ICON_CASERNE].width,
                                                          textures->toolbarIcons[ICON_CASERNE].height})) {
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->stateToolbar.stateMenuSave.modeMenu = false;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CASERNE ? BUILD_MODE_NONE
                                                                                           : BUILD_MODE_CASERNE);
        }
        if (textures->stateToolbar.stateMenuSave.modeMenu) {
            if (CheckCollisionPointRec(mousePos, (Rectangle) {40, 851, textures->toolbarIcons[ICON_GRID].width,
                                                              textures->toolbarIcons[ICON_GRID].height})) {
                textures->affichageNiveau = AFFICHAGE_NIVEAU_NONE;
            }
            if (CheckCollisionPointRec(mousePos, (Rectangle) {150, 851, textures->toolbarIcons[ICON_ELECTRICITY_GRID].width,
                                                              textures->toolbarIcons[ICON_ELECTRICITY_GRID].height})) {
                textures->affichageNiveau = AFFICHAGE_NIVEAU_ELEC;
            }
            if (CheckCollisionPointRec(mousePos, (Rectangle) {265, 851, textures->toolbarIcons[ICON_WATER_GRID].width,
                                                              textures->toolbarIcons[ICON_WATER_GRID].height})) {
                textures->affichageNiveau = AFFICHAGE_NIVEAU_EAU;
            }

        }
    }
}

CaseKind_t ui_buildmode_to_casekind(BuildMode mode) {
    switch (mode) {
        case BUILD_MODE_ROUTE:
            return KIND_ROUTE;
        case BUILD_MODE_HABITATION:
            return KIND_HABITATION;
        case BUILD_MODE_CENTRALE:
            return KIND_CENTRALE;
        case BUILD_MODE_CHATEAU:
            return KIND_CHATEAU;
        case BUILD_MODE_CASERNE:
            return KIND_CASERNE;
        default:
            return KIND_VIDE;
    }
}