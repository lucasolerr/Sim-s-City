#include "menu_principal.h"
#include <stdio.h>
#include "screens/gameplay.h"
#include "sauvegarde.h"

MenuPrincipal_t* menu_principal_alloc() {
    MenuPrincipal_t* test = malloc(sizeof(MenuPrincipal_t));
    test->screenInfo.draw_callback = menu_principal_draw;
    test->screenInfo.update_callback = menu_principal_update;
    test->screenInfo.on_enter_callback = menu_principal_enter;
    test->screenInfo.on_exit_callback = menu_principal_exit;
    test->screenInfo.screen_name = "MENU PRINCIPAL";
    return test;
}

void menu_principal_draw(Jeu_t* jeu, MenuPrincipal_t* menu) {
    bool SourisSurTexte;
    DrawTexture(menu->texture_fond, 0, 0, WHITE);
    switch (menu->nbClique) {
            case 0:
                if(CheckCollisionPointRec(GetMousePosition(), menu->textBoxJouer) ||
                   CheckCollisionPointRec(GetMousePosition(), menu->textBoxCredits) ||
                   CheckCollisionPointRec(GetMousePosition(), menu->textBoxRegles)) {
                    SourisSurTexte = true;
                }
                else{
                    SourisSurTexte = false;
                    DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 256}, 150, 8, ORANGE);
                    DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 255}, 146, 10, WHITE);
                    DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {50, 486}, 150, 8, ORANGE);
                    DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {57, 485}, 146, 10, WHITE);
                    DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {51, 766}, 150,8, ORANGE);
                    DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {57, 765}, 146, 10, WHITE);

                }

                if(SourisSurTexte) {

                    if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxJouer)) {
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {45, 260}, 190, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 255}, 190, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {50, 486}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 485}, 146, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {51, 766}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 765}, 146, 10, WHITE);
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRegles)) {
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {47, 490}, 190, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 485}, 190, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 256}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 255}, 146, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {51, 766}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 765}, 146, 10, WHITE);;

                    }
                    if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxCredits)) {
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {47, 770}, 190, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 765}, 190, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 256}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 255}, 146, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {50, 486}, 150, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 485}, 146, 10, WHITE);
                    }
                }
                break;

            case 1:
                DrawTextEx(menu->font_ttf, "NOUVELLE PARTIE", (Vector2){650, 260}, 80, 8, ORANGE);
                DrawTextEx(menu->font_ttf, "NOUVELLE PARTIE", (Vector2){655, 255}, 80, 8, WHITE);
                if (menu->peutChargerPartie) {
                    DrawTextEx(menu->font_ttf, "CHARGER PARTIE", (Vector2) {650, 350}, 80, 8, ORANGE);
                    DrawTextEx(menu->font_ttf, "CHARGER PARTIE", (Vector2) {655, 345}, 80, 8, WHITE);
                    DrawCircle(630, 381, 5, WHITE);
                    DrawCircle(628, 382, 5, ORANGE);
                }
                DrawCircle(628, 285, 5, ORANGE);
//                DrawCircle(628, 382, 5, ORANGE);
                DrawCircle(630, 284, 5, WHITE);
//                DrawCircle(630, 381, 5, WHITE);
                DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 256}, 150, 8, ORANGE);
                DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 255}, 146, 10, WHITE);
                DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {50, 486}, 150, 8, ORANGE);
                DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 485}, 146, 10, WHITE);
                DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {51, 766}, 150, 8, ORANGE);
                DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 765}, 146, 10, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRetour)){
                    DrawRectangle(10, 915, 220, 90, DARKGRAY);
                    DrawRectangle(15, 920,210, 80, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 935}, 65, 5, GRAY);
            }
            if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRegles) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {47, 490}, 190, 10, ORANGE);
                DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 485}, 190, 10, WHITE);
            }
            if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxCredits) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                menu->nbClique = 3;
            }
            break;

            case 2:
                DrawRectangle(30, 10, 1540, 900, SKYBLUE);
                DrawTextEx(menu->font_ttf, "LES REGLES DU JEU :", (Vector2){430, 20}, 90, 5, WHITE);
                DrawTextEx(menu->font_ttf, "\tDans ce jeu vous etes le maire de la ville ECE-city en charge\ndu bien-etre de ses citoyens."
                                       " Vous avez le pouvoir de construire \ndes infrastructures (routes lignes electriques"
                                       " canalisation) et \ndes batiments (centrales electriques,\n"
                                       "caserne de pompiers...).\n"
                                       "\tToutes ces taches seront a realiser en gerant un budget serre \nqui doit equilibrer les"
                                       " depenses liees a ces constructions et\nles recettes liees aux impots et taxes.\n"
                                        "\tPour une partie deux modes sont disponibles : communiste\net capitaliste.", (Vector2){50, 110}, 50, 5, WHITE);
                DrawRectangle(15, 930, 205, 70, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 940}, 65, 5, GRAY);
                if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRetour)){
                    DrawRectangle(10, 915, 220, 90, DARKGRAY);
                    DrawRectangle(15, 920,210, 80, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 935}, 65, 5, GRAY);
                }
            break;

            case 3:
                DrawRectangle(30, 10, 1540, 900, SKYBLUE);
                DrawTextEx(menu->font_ttf, "CREDITS :", (Vector2){630, 20}, 90, 5, WHITE);
                DrawTextEx(menu->font_ttf, "\n\tCe jeu a ete realise dans le cadre du projet informatique du \npremier semestre de deuxieme annee"
                                           " d'ecole d'ingenieur a l'ECE.\nL'entierete de ce jeu a ete concu et implemente par l'equipe \n"
                                           "3G qui est composee de :\n", (Vector2){45, 110}, 50, 5, WHITE);
                DrawTextEx(menu->font_ttf, "- LUCAS ARRIESSE\n- LUCA SOLER\n- EMMA BATHEROSSE\n- JULES FEDIT", (Vector2){650, 500}, 50, 5, WHITE);
                DrawRectangle(15, 930, 205, 70, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 940}, 65, 5, GRAY);
                if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRetour)){
                    DrawRectangle(10, 915, 220, 90, DARKGRAY);
                    DrawRectangle(15, 920,210, 80, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 935}, 65, 5, GRAY);
                }
            break;

            case 4:
                DrawRectangle(0, 0, 1600, 1024, BLACK);
            break;
            case 5:
                DrawRectangle(0, 0, 1600, 1024, BLACK);
            break;
            case 6:
                DrawRectangle(15, 930, 205, 70, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "CHOISIR LE MODE", (Vector2) {457, 700}, 92, 10, ORANGE);
                DrawTextEx(menu->font_ttf, "CHOISIR LE MODE", (Vector2) {460, 690}, 92, 10, WHITE);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 940}, 65, 5, GRAY);
                DrawRectangle(200, 400, 450, 200, SKYBLUE);
                DrawRectangle(950, 400, 450, 200, SKYBLUE);
                DrawTextEx(menu->font_ttf, "CAPITALISTE", (Vector2){220, 465}, 85, 5, WHITE);
                DrawTextEx(menu->font_ttf, "COMMUNISTE", (Vector2){970, 465}, 85, 5, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), menu->textBoxRetour)){
                    DrawRectangle(10, 915, 220, 90, DARKGRAY);
                    DrawRectangle(15, 920,210, 80, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){25, 935}, 65, 5, GRAY);
                }
                if (CheckCollisionPointRec(GetMousePosition(), menu->boxCapitaliste)){
                    DrawRectangle(200, 400, 450, 200, DARKBLUE);
                    DrawTextEx(menu->font_ttf, "CAPITALISTE", (Vector2){220, 465}, 85, 5, WHITE);
                }
                if (CheckCollisionPointRec(GetMousePosition(), menu->boxCommuniste)){
                    DrawRectangle(950, 400, 450, 200, DARKBLUE);
                    DrawTextEx(menu->font_ttf, "COMMUNISTE", (Vector2){970, 465}, 85, 5, WHITE);
                }
            break;
            case 7:
                DrawRectangle(0, 0, 1600, 1024, BLACK);
            break;
            default:
                break;

        }
    }

void menu_principal_update(Jeu_t* jeu, MenuPrincipal_t* menu) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->textBoxJouer)){
        menu->nbClique = 1;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->textBoxRegles)){
        menu->nbClique = 2;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->textBoxCredits)){
        menu->nbClique = 3;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->boxCapitaliste)){
        menu->nbClique = 4;
        jeu_switch_screen(jeu, gameplay_create_screen(sim_world_create(Capitaliste_t, 500000)));
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->boxCommuniste)){
        menu->nbClique = 5;
        jeu_switch_screen(jeu, gameplay_create_screen(sim_world_create(Communiste_t, 500000)));
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->textBoxRetour)){
        menu->nbClique = 0;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->boxNouvellePartie)){
        menu->nbClique = 6;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menu->boxChargerPartie) && menu->peutChargerPartie){
        menu->nbClique = 7;
        SimWorld_t* world = sim_world_create(Capitaliste_t, 500000);
        sim_charger(world, SAVE_AUTO_SAVE_FILENAME);
        jeu_switch_screen(jeu, gameplay_create_screen(world));
    }
}

// les trucs a charger au lancement du jeu vont la
void menu_principal_enter(Jeu_t* jeu, MenuPrincipal_t* menu) {
    menu->nbClique = 0;
    menu->boxNouvellePartie = (Rectangle){655, 255, 570, 65};
    menu->boxChargerPartie = (Rectangle){650, 350, 545, 65};
    menu->textBoxJouer = (Rectangle){52, 256, 330, 100};
    menu->textBoxRegles = (Rectangle){50, 486, 390, 100};
    menu->textBoxCredits = (Rectangle){50, 766, 440, 100};
    menu->textBoxRetour = (Rectangle){15, 930, 205, 70};
    menu->boxCommuniste = (Rectangle){950, 400, 450, 200};
    menu->boxCapitaliste = (Rectangle){200, 400, 450, 200};
    menu->font_ttf = LoadFontEx("../assets/font/daddy-day.ttf", 36, NULL, 0);
    menu->texture_fond = LoadTexture("../assets/textures/menu/fond_menu.png");
    menu->peutChargerPartie = FileExists(SAVE_AUTO_SAVE_FILENAME);
}

// les trucs a supprimer a la fermeture du jeu vont la
void menu_principal_exit(Jeu_t* jeu, MenuPrincipal_t* menu) {
    UnloadTexture(menu->texture_fond);
    UnloadTexture(menu->texture_loading);
    UnloadTexture(menu->texture_logo);
    UnloadTexture(menu->texture_EA);
    UnloadFont(menu->font_ttf);
}
