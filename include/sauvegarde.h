#ifndef ECECITY_SAUVEGARDE_H
#define ECECITY_SAUVEGARDE_H

#include "screens/gameplay.h"

#define SAVE_DIRECTORY_PATH "saves/"
#define SAVE_AUTO_SAVE_FILENAME "saves/Autosave.txt"

void affichage_menu_sauvegarde(GameplayScreen_t* gameplay);

void update_menu_sauvegarde(GameplayScreen_t* gameplay);

void ensure_save_directory_exists();

/// Sauvegarde la partie dans un fichier
void sim_sauvegarder(SimWorld_t *world, const char *nomFichier);

/// Charge une partie depuis un fichier
void sim_charger(SimWorld_t *world, const char *nomFichier);

#endif
