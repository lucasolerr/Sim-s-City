
#ifndef ECECITY_SPRITESHEET_H
#define ECECITY_SPRITESHEET_H

#include <raylib.h>

#define SPRITELARGEUR 40
#define SPRITEHAUTEUR 20

#define ORIGINEX 17
#define ORIGINEY 3

enum SPRITE_MAP {
    SPRITE_CHEAT,
    SPRITE_HOOVER,
    SPRITE_CONTOUR,
    SPRITE_TERRAIN_0,
    SPRITE_TERRAIN_1,
    SPRITE_TERRAIN_2,
    SPRITE_TERRAIN_3,
    SPRITE_TERRAIN_4,
    SPRITE_TERRAIN_5,
    SPRITE_TERRAIN_6,
    SPRITE_ROUTE_0,
    SPRITE_ROUTE_1,
    SPRITE_ROUTE_2,
    SPRITE_ROUTE_3,
    SPRITE_ROUTE_4,
    SPRITE_ROUTE_5,
    SPRITE_ROUTE_6,
    SPRITE_ROUTE_7,
    SPRITE_ROUTE_8,
    SPRITE_ROUTE_9,
    SPRITE_ROUTE_10,
    SPRITE_ROUTE_11,
    SPRITE_ROUTE_12,
    SPRITE_ROUTE_13,
    SPRITE_ROUTE_14,
    SPRITE_TERRAIN_VAGUE_3X3,
    SPRITE_RUINE_3X3,
    SPRITE_CABANE_3X3,
    SPRITE_MAISON_3X3,
    SPRITE_IMMEUBLE_3X3,
    SPRITE_GRATTE_CIEL_3X3,
    SPRITE_ENERGY_4X6,
    SPRITE_ENERGY_6X4,
    SPRITE_EAU_4X6,
    SPRITE_EAU_6X4,
    SPRITE_CASERNE_4x6,
    SPRITE_VIDE,
    NB_SPRITES
};

typedef struct Sprite_t {
    Rectangle rectangle;
    int decalageXDecor;
    int decalageYDecor;
} Sprite_t;

typedef struct SpriteSheet_t {
    Texture2D spriteSheetTexture;
    Image spriteDetectionTuile;
    Sprite_t sprites[NB_SPRITES];
    Texture2D spritesheetEtatsHabitations;
    Texture2D spriteFeu;
} SpriteSheet_t;

void sprite_sheet_load(SpriteSheet_t* spriteSheet);

void sprite_sheet_draw_sprite(SpriteSheet_t* spriteSheet, enum SPRITE_MAP map, Color teinte, int x, int y);

#endif //ECECITY_SPRITESHEET_H
