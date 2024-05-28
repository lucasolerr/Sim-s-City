
#ifndef ECECITY_AFFICHAGE_H
#define ECECITY_AFFICHAGE_H

#include <raylib.h>
#include "sim/sim.h"
#include "spritesheet.h"
#include "sim/casernes.h"

/// Enumère les composants du jeu à dessiner.
enum RenderLayer {
    LAYER_HABITATIONS = 1 << 0,
    LAYER_CENTRALES = 1 << 1,
    LAYER_CHATEAUX = 1 << 2,
    LAYER_ROUTES = 1 << 3,
    LAYER_CASERNE = 1 << 4,
    LAYER_ALL = LAYER_HABITATIONS | LAYER_CENTRALES | LAYER_CHATEAUX | LAYER_CASERNE
};

/// Dessine le fond de la carte.
void affichage_draw_terrain_background(SpriteSheet_t* sheet, SimWorld_t* world, bool eau, bool elec);

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world, enum RenderLayer layers);

/// Dessine une habitation sur la carte.
void affichage_draw_habitation(SpriteSheet_t* sheet, Habitation_t* habitation, Color teinte);

/// Dessine l'apercu de construction d'un bâtiment sur la carte.
void affichage_draw_build_preview(SpriteSheet_t* sheet, SimWorld_t* world, Vector2I pos, CaseKind_t type);

void affichage_debug_draw_voisins_chateau(SpriteSheet_t* sheet, ChateauEau_t* chateau, Color teinte);

void affichage_debug_draw_voisins_centrale(SpriteSheet_t* sheet, CentraleElectrique_t* centrale, Color teinte);

void affichage_debug_draw_voisins_caserne(SpriteSheet_t* sheet, CasernePompier_t* caserne, Color teinte);

#endif //ECECITY_AFFICHAGE_H
