#include "affichage.h"
#include "sim/chateau.h"
#include "raylib.h"
#include "bfs.h"
#include "sim/casernes.h"

/// Fonction qui permet de trier les routes selon le nombre de voisins adjacents.
/// @param eceCity - Structure du monde de simulation alloué dynamiquement.
/// @param x, y - coordonnées isométriques de la route en question.
/// @return SPRITE_MAP - sprite correspondante pour une route donnée.
enum SPRITE_MAP get_route_sprite_variant(SimWorld_t *eceCity, int x, int y) {
    if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
        eceCity->map[x][y - 1].type == KIND_ROUTE &&
        eceCity->map[x + 1][y].type == KIND_ROUTE &&
        eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_14;
    } else if (eceCity->map[x - 1][y].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_13;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_12;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_11;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_10;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_9;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_8;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_7;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_6;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_5;
    } else if (eceCity->map[x + 1][y].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_4;
    } else if (eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_3;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_2;
    } else if (eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_1;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_0;
    }

    return SPRITE_ROUTE_0;
}

/// Dessine le fond de la map (arbres, herbe, ...).
/// @param sheet - Structure de SpriteSheet - contenant tous les assets pour l'affichage.
/// @param world - Structure du monde de simulation alloué dynamiquement.
/// @param eau, elec - factorise cette fonction pour l'affichage des différents niveaux (0, -1, -2).
/// @return void.
void affichage_draw_terrain_background(SpriteSheet_t *sheet, SimWorld_t *world, bool eau, bool elec) {
    for (int i = -25; i < 120; ++i) {
        for (int j = -25; j < 130; ++j) {
            if (i > 0 && i < 45 && j > 0 && j < 35) {
                switch (world->map[i][j].type) {
                    case KIND_ROUTE: {
                        sprite_sheet_draw_sprite(sheet, get_route_sprite_variant(world, i, j),
                                                 eau && world->map[i][j].connexe_eau ? BLUE : (elec &&
                                                                                               world->map[i][j].connexe_elec
                                                                                               ? YELLOW : WHITE), i,
                                                 j);
                        break;
                    }

                    default: {
                        sprite_sheet_draw_sprite(sheet, world->map[i][j].sprite_terrain, WHITE, i, j);
                        break;
                    }
                }
            } else {
                sprite_sheet_draw_sprite(sheet, SPRITE_TERRAIN_3, WHITE, i, j);
            }
        }
    }
}

/// Dessine les tuiles de la carte.
/// @param sheet - Structure de SpriteSheet - contenant tous les assets pour l'affichage.
/// @param world - Structure du monde de simulation alloué dynamiquement.
/// @param layers - enum RenderLayer - permet d'afficher un niveau de transparence pour les bâtiments lors du placement de la route.
/// @return void.
void affichage_draw_entities(SpriteSheet_t *sheet, SimWorld_t *world, enum RenderLayer layers) {

    Color centralesColor = (layers & LAYER_CENTRALES) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t *centrale = (CentraleElectrique_t *) centrales->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, centralesColor, centrale->position.x, centrale->position.y);
        centrales = centrales->next;
    }

    Color chateauxColor = (layers & LAYER_CHATEAUX) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t *chateau = (ChateauEau_t *) chateaux->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, chateauxColor, chateau->position.x, chateau->position.y);
        chateaux = chateaux->next;
    }

    Color casernesColor = (layers & LAYER_CASERNE) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *casernes = world->casernes->premier;
    while (casernes) {
        CasernePompier_t *caserne = (CasernePompier_t *) casernes->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_CASERNE_4x6, casernesColor, caserne->position.x, caserne->position.y);
        casernes = casernes->next;
    }

    Color routesColor = (layers & LAYER_HABITATIONS) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *maison = world->habitations->premier;
    while (maison) {
        Habitation_t *hab = (Habitation_t *) maison->data;
        affichage_draw_habitation(sheet, hab, routesColor);
        maison = maison->next;
    }
    ///////////////////////////
    ///////////////////////////
}

/// Dessine les bâtiments quand on les a en mains.
/// @param sheet - Structure de SpriteSheet - contenant tous les assets pour l'affichage.
/// @param world - Structure du monde de simulation alloué dynamiquement.
/// @return void.
void affichage_draw_build_preview(SpriteSheet_t *sheet, SimWorld_t *world, Vector2I v, CaseKind_t type) {
    int w = 0;
    int h = 0;
    enum SPRITE_MAP bat = SPRITE_HOOVER;
    switch (type) {
        case KIND_ROUTE:
            w = 1;
            h = 1;
            bat = SPRITE_ROUTE_0;
            break;

        case KIND_HABITATION:
            w = 3;
            h = 3;
            bat = SPRITE_TERRAIN_VAGUE_3X3;
            break;

        case KIND_CENTRALE:
            w = 6;
            h = 4;
            bat = SPRITE_ENERGY_6X4;
            break;

        case KIND_CHATEAU:
            w = 4;
            h = 6;
            bat = SPRITE_EAU_4X6;
            break;

        case KIND_CASERNE:
            w = 6;
            h = 4;
            bat = SPRITE_CASERNE_4x6;
            break;

        default:
            break;
    }

    bool is_valid = sim_check_can_place(world, w > 1, v.x, v.y, w, h);
    sprite_sheet_draw_sprite(sheet, bat, is_valid ? GREEN : RED, v.x, v.y);
}

/// Dessine les habitations en fonciton de leur niveau (Ruine, Maison, ...).
/// @param sheet - Structure de SpriteSheet - contenant tous les assets pour l'affichage.
/// @param habitation - adresse de structure habitation allouée dynamiquement.
/// @param teinte - Structure Color - permet d'afficher l'habitation selon plusieurs teintes
/// @return void.
void affichage_draw_habitation(SpriteSheet_t *sheet, Habitation_t *habitation, Color teinte) {
    enum SPRITE_MAP habitation_sprite = SPRITE_TERRAIN_VAGUE_3X3;

    switch (habitation->niveau) {
        case NIVEAU_CABANE:
        case NIVEAU_CABANE_CAP:
            habitation_sprite = SPRITE_CABANE_3X3;
            break;

        case NIVEAU_MAISON:
        case NIVEAU_MAISON_CAP:
            habitation_sprite = SPRITE_MAISON_3X3;
            break;

        case NIVEAU_GRATTE_CIEL:
            habitation_sprite = SPRITE_GRATTE_CIEL_3X3;
            break;

        case NIVEAU_RUINE:
            habitation_sprite = SPRITE_RUINE_3X3;
            break;

        case NIVEAU_TERRAIN_VAGUE:
        case NIVEAU_TERRAIN_VAGUE_CAP:
            habitation_sprite = SPRITE_TERRAIN_VAGUE_3X3;
            break;

        case NIVEAU_IMMEUBLE:
        case NIVEAU_IMMEUBLE_CAP:
            habitation_sprite = SPRITE_IMMEUBLE_3X3;
            break;

        default:
            break;
    }

    sprite_sheet_draw_sprite(sheet, habitation_sprite, teinte, habitation->position.x, habitation->position.y);
}

/// @return void.
void affichage_debug_draw_voisins_chateau(SpriteSheet_t *sheet, ChateauEau_t *chateau, Color teinte) {
    sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, teinte, chateau->position.x, chateau->position.y);

    for (int i = 0; i < chateau->habitations->taille; ++i) {
        Habitation_t *hab = ((HabitationNode_t *) chateau->habitations->data[i])->habitation;
        affichage_draw_habitation(sheet, hab, teinte);
        int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                 hab->position.y * (SPRITELARGEUR / 2);
        int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                 hab->position.x * (SPRITEHAUTEUR / 2);
        DrawText(TextFormat("#%d (d: %d)", i, ((HabitationNode_t *) chateau->habitations->data[i])->distance), oX, oY,
                 20, WHITE);
    }
}

/// @return void.
void affichage_debug_draw_voisins_centrale(SpriteSheet_t *sheet, CentraleElectrique_t *centrale, Color teinte) {
    sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, teinte, centrale->position.x, centrale->position.y);
    for (int i = 0; i < centrale->habitations->taille; ++i) {
        Habitation_t *hab = ((HabitationNode_t *) centrale->habitations->data[i])->habitation;
        affichage_draw_habitation(sheet, hab, teinte);
        int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                 hab->position.y * (SPRITELARGEUR / 2);
        int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                 hab->position.x * (SPRITEHAUTEUR / 2);
        DrawText(TextFormat("#%d", i, ((HabitationNode_t *) centrale->habitations->data[i])->distance), oX, oY, 20,
                 WHITE);
    }
}

/// @return void.
void affichage_debug_draw_voisins_caserne(SpriteSheet_t *sheet, CasernePompier_t *caserne, Color teinte) {
    sprite_sheet_draw_sprite(sheet, SPRITE_CASERNE_4x6, teinte, caserne->position.x, caserne->position.y);
    for (int i = 0; i < caserne->habitations->taille; ++i) {
        Habitation_t *hab = ((HabitationNode_t *) caserne->habitations->data[i])->habitation;
        affichage_draw_habitation(sheet, hab, teinte);
        int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                 hab->position.y * (SPRITELARGEUR / 2);
        int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                 hab->position.x * (SPRITEHAUTEUR / 2);
        DrawText(TextFormat("#%d (%d: d)", i, ((HabitationNode_t *) caserne->habitations->data[i])->distance), oX, oY,
                 20, WHITE);
    }
}