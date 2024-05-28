#ifndef ECECITY_MENU_PRINCIPAL_H
#define ECECITY_MENU_PRINCIPAL_H

#include "jeu.h"
#include <stdlib.h>

typedef struct MenuPrincipal_t {
    ScreenInfo_t screenInfo;
    // les textures, polices et autres ressources vont ici
    Font font_ttf;
    Texture2D texture_loading;
    Texture2D texture_EA;
    Texture2D texture_fond;
    Texture2D texture_logo;
    int nbClique;
    Rectangle boxNouvellePartie;
    Rectangle boxChargerPartie;
    Rectangle textBoxJouer;
    Rectangle textBoxRegles;
    Rectangle textBoxCredits;
    Rectangle textBoxRetour;
    Rectangle boxCommuniste ;
    Rectangle boxCapitaliste;
    bool peutChargerPartie;
} MenuPrincipal_t;

MenuPrincipal_t* menu_principal_alloc();

void menu_principal_draw(Jeu_t* jeu, MenuPrincipal_t* menu);

void menu_principal_update(Jeu_t* jeu, MenuPrincipal_t* menu);

void menu_principal_enter(Jeu_t* jeu, MenuPrincipal_t* menu);

void menu_principal_exit(Jeu_t* jeu, MenuPrincipal_t* menu);

#endif //ECECITY_MENU_PRINCIPAL_H
