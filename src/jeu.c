#include "jeu.h"


/// Lance la boucle principale du jeu.
void jeu_run(Jeu_t* jeu, ScreenInfo_t* ecran_depart)
{
    InitWindow(FENETRE_JEU_LARGEUR, FENETRE_JEU_HAUTEUR, "ECECity");

    jeu->should_exit = false;
    jeu->screen = ecran_depart;

    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    DBG_LOG("Lancement du jeu sur l'ecran: %s", ecran_depart->screen_name);

    if (ecran_depart->on_enter_callback != NULL)
        ecran_depart->on_enter_callback(jeu, ecran_depart);

    while (!WindowShouldClose() && !jeu->should_exit)
    {
        if (jeu->screen->update_callback != NULL)
            jeu->screen->update_callback(jeu, jeu->screen);

        BeginDrawing();
        ClearBackground(BLACK);

        if (jeu->screen->draw_callback != NULL)
            jeu->screen->draw_callback(jeu, jeu->screen);

        EndDrawing();
    }

    if (jeu->screen->on_exit_callback != NULL)
        jeu->screen->on_exit_callback(jeu, jeu->screen);
}

/// Change l'écran actuellement affiché avec celui passé en paramètre.
void jeu_switch_screen(Jeu_t* game, ScreenInfo_t* ecran) {
    if (game->screen)
    {
        if (game->screen->on_exit_callback)
            game->screen->on_exit_callback(game, game->screen);

        free(game->screen);
    }

    game->screen = ecran;
    if (game->screen)
    {
        if (game->screen->on_enter_callback)
            game->screen->on_enter_callback(game, game->screen);
    }
}

