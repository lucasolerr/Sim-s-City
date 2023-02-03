#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>
#include <screens/gameplay.h>
#ifndef ECECITY_CAPACITE_H
#define ECECITY_CAPACITE_H

/// Affichage de la capacité des bâtiments en eau
void afficher_capacite(SimWorld_t* world, bool eau);

/// Affichage général du niveau d'eau
void afficher_level_eau(SpriteSheet_t* sheet, SimWorld_t* world);

/// Affichage général du niveau d'électricité
void afficher_level_elec(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay);

void afficher_level(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay);

/// Affichage de las suffisance des bâtiments en eau (si eau délivrée < nbHab) alors insuffisant
void afficher_etat_alim_eau(SpriteSheet_t* sheet, SimWorld_t* world);

/// Affichage de las suffisance des bâtiments en électricité (si électricité délivrée < nbHab) alors insuffisant
void afficher_etat_alim_elec(SpriteSheet_t* sheet, SimWorld_t* world);

#endif //ECECITY_CAPACITE_H
