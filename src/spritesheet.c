#include "spritesheet.h"

void sprite_sheet_load(SpriteSheet_t* spriteSheet) {

    spriteSheet->spriteSheetTexture = LoadTexture("../assets/textures/carte/spriteSheet.png");
    spriteSheet->spriteDetectionTuile = LoadImage("../assets/textures/carte/tileCheat.png");

    spriteSheet->sprites[SPRITE_CHEAT].rectangle.height = SPRITEHAUTEUR;
    spriteSheet->sprites[SPRITE_CHEAT].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_CHEAT].rectangle.x = 0;
    spriteSheet->sprites[SPRITE_CHEAT].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_CHEAT].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_CHEAT].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_HOOVER].rectangle.height = SPRITEHAUTEUR;
    spriteSheet->sprites[SPRITE_HOOVER].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_HOOVER].rectangle.x = SPRITELARGEUR * SPRITE_HOOVER;
    spriteSheet->sprites[SPRITE_HOOVER].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_HOOVER].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_HOOVER].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_CONTOUR].rectangle.height = 20;
    spriteSheet->sprites[SPRITE_CONTOUR].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_CONTOUR].rectangle.x = SPRITELARGEUR * SPRITE_CONTOUR;
    spriteSheet->sprites[SPRITE_CONTOUR].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_CONTOUR].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_CONTOUR].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_0].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_0].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_0].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_0;
    spriteSheet->sprites[SPRITE_TERRAIN_0].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_0].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_0].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_1].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_1].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_1].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_1;
    spriteSheet->sprites[SPRITE_TERRAIN_1].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_1].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_1].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_2].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_2].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_2].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_2;
    spriteSheet->sprites[SPRITE_TERRAIN_2].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_2].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_2].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_3].rectangle.height = 36;
    spriteSheet->sprites[SPRITE_TERRAIN_3].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_3].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_3;
    spriteSheet->sprites[SPRITE_TERRAIN_3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_3].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_3].decalageYDecor = -10;

    spriteSheet->sprites[SPRITE_TERRAIN_4].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_4].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_4].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_4;
    spriteSheet->sprites[SPRITE_TERRAIN_4].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_4].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_4].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_5].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_5].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_5].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_5;
    spriteSheet->sprites[SPRITE_TERRAIN_5].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_5].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_5].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_6].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_TERRAIN_6].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_TERRAIN_6].rectangle.x = SPRITELARGEUR * SPRITE_TERRAIN_6;
    spriteSheet->sprites[SPRITE_TERRAIN_6].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_6].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_6].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_0].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_0].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_0].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_0;
    spriteSheet->sprites[SPRITE_ROUTE_0].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_0].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_0].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_1].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_1].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_1].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_1;
    spriteSheet->sprites[SPRITE_ROUTE_1].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_1].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_1].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_2].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_2].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_2].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_2;
    spriteSheet->sprites[SPRITE_ROUTE_2].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_2].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_2].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_3].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_3].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_3].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_3;
    spriteSheet->sprites[SPRITE_ROUTE_3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_3].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_3].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_4].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_4].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_4].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_4;
    spriteSheet->sprites[SPRITE_ROUTE_4].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_4].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_4].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_5].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_5].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_5].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_5;
    spriteSheet->sprites[SPRITE_ROUTE_5].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_5].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_5].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_6].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_6].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_6].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_6;
    spriteSheet->sprites[SPRITE_ROUTE_6].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_6].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_6].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_7].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_7].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_7].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_7;
    spriteSheet->sprites[SPRITE_ROUTE_7].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_7].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_7].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_8].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_8].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_8].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_8;
    spriteSheet->sprites[SPRITE_ROUTE_8].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_8].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_8].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_9].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_9].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_9].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_9;
    spriteSheet->sprites[SPRITE_ROUTE_9].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_9].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_9].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_10].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_10].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_10].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_10;
    spriteSheet->sprites[SPRITE_ROUTE_10].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_10].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_10].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_11].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_11].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_11].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_11;
    spriteSheet->sprites[SPRITE_ROUTE_11].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_11].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_11].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_12].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_12].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_12].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_12;
    spriteSheet->sprites[SPRITE_ROUTE_12].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_12].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_12].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_13].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_13].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_13].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_13;
    spriteSheet->sprites[SPRITE_ROUTE_13].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_13].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_13].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_ROUTE_14].rectangle.height = 26;
    spriteSheet->sprites[SPRITE_ROUTE_14].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[SPRITE_ROUTE_14].rectangle.x = SPRITELARGEUR * SPRITE_ROUTE_14;
    spriteSheet->sprites[SPRITE_ROUTE_14].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ROUTE_14].decalageXDecor = 0;
    spriteSheet->sprites[SPRITE_ROUTE_14].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].rectangle.height = 70;
    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].rectangle.x = 1000;
    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[SPRITE_TERRAIN_VAGUE_3X3].decalageYDecor = -1;

    spriteSheet->sprites[SPRITE_RUINE_3X3].rectangle.height = 70;
    spriteSheet->sprites[SPRITE_RUINE_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_RUINE_3X3].rectangle.x = 1120;
    spriteSheet->sprites[SPRITE_RUINE_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_RUINE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[SPRITE_RUINE_3X3].decalageYDecor = 0;

    spriteSheet->sprites[SPRITE_CABANE_3X3].rectangle.height = 75;
    spriteSheet->sprites[SPRITE_CABANE_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_CABANE_3X3].rectangle.x = 1240;
    spriteSheet->sprites[SPRITE_CABANE_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_CABANE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[SPRITE_CABANE_3X3].decalageYDecor = -(5);

    spriteSheet->sprites[SPRITE_MAISON_3X3].rectangle.height = 70;
    spriteSheet->sprites[SPRITE_MAISON_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_MAISON_3X3].rectangle.x = 1360;
    spriteSheet->sprites[SPRITE_MAISON_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_MAISON_3X3].decalageXDecor = -40;
    spriteSheet->sprites[SPRITE_MAISON_3X3].decalageYDecor = -1;

    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].rectangle.height = 90;
    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].rectangle.x = 1480;
    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].decalageXDecor = -41;
    spriteSheet->sprites[SPRITE_IMMEUBLE_3X3].decalageYDecor = -22;

    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].rectangle.height = 120;
    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].rectangle.width = 120;
    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].rectangle.x = 1600;
    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].decalageXDecor = -40;
    spriteSheet->sprites[SPRITE_GRATTE_CIEL_3X3].decalageYDecor = -54;

    spriteSheet->sprites[SPRITE_ENERGY_4X6].rectangle.height = 128;
    spriteSheet->sprites[SPRITE_ENERGY_4X6].rectangle.width = 200;
    spriteSheet->sprites[SPRITE_ENERGY_4X6].rectangle.x = 1720;
    spriteSheet->sprites[SPRITE_ENERGY_4X6].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ENERGY_4X6].decalageXDecor = -100;
    spriteSheet->sprites[SPRITE_ENERGY_4X6].decalageYDecor = -22;

    spriteSheet->sprites[SPRITE_ENERGY_6X4].rectangle.height = 128;
    spriteSheet->sprites[SPRITE_ENERGY_6X4].rectangle.width = 200;
    spriteSheet->sprites[SPRITE_ENERGY_6X4].rectangle.x = 1920;
    spriteSheet->sprites[SPRITE_ENERGY_6X4].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_ENERGY_6X4].decalageXDecor = -60;
    spriteSheet->sprites[SPRITE_ENERGY_6X4].decalageYDecor = -22;

    spriteSheet->sprites[SPRITE_EAU_4X6].rectangle.height = 136;
    spriteSheet->sprites[SPRITE_EAU_4X6].rectangle.width = 200;
    spriteSheet->sprites[SPRITE_EAU_4X6].rectangle.x = 2120;
    spriteSheet->sprites[SPRITE_EAU_4X6].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_EAU_4X6].decalageXDecor = -100;
    spriteSheet->sprites[SPRITE_EAU_4X6].decalageYDecor = -29;

    spriteSheet->sprites[SPRITE_EAU_6X4].rectangle.height = 130;
    spriteSheet->sprites[SPRITE_EAU_6X4].rectangle.width = 200;
    spriteSheet->sprites[SPRITE_EAU_6X4].rectangle.x = 2320;
    spriteSheet->sprites[SPRITE_EAU_6X4].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_EAU_6X4].decalageXDecor = -60;
    spriteSheet->sprites[SPRITE_EAU_6X4].decalageYDecor = -22;

    spriteSheet->sprites[SPRITE_CASERNE_4x6].rectangle.height = 120;
    spriteSheet->sprites[SPRITE_CASERNE_4x6].rectangle.width = 200;
    spriteSheet->sprites[SPRITE_CASERNE_4x6].rectangle.x = 2520;
    spriteSheet->sprites[SPRITE_CASERNE_4x6].rectangle.y = 0;
    spriteSheet->sprites[SPRITE_CASERNE_4x6].decalageXDecor = -60;
    spriteSheet->sprites[SPRITE_CASERNE_4x6].decalageYDecor = -20;


    spriteSheet->spritesheetEtatsHabitations = LoadTexture("../assets/textures/icones/icones.png");
    spriteSheet->spriteFeu = LoadTexture("../assets/textures/icones/fire.png");
}

void sprite_sheet_draw_sprite(SpriteSheet_t* spriteSheet, enum SPRITE_MAP sprite, Color teinte, int x, int y) {
    int oX = (ORIGINEX * SPRITELARGEUR) + x * (SPRITELARGEUR/2) - y * (SPRITELARGEUR/2);
    int oY = (ORIGINEY * SPRITEHAUTEUR) + y * (SPRITEHAUTEUR/2) + x * (SPRITEHAUTEUR/2);
    DrawTextureRec(spriteSheet->spriteSheetTexture,
                   spriteSheet->sprites[sprite].rectangle,
                   (Vector2){oX + spriteSheet->sprites[sprite].decalageXDecor, oY + + spriteSheet->sprites[sprite].decalageYDecor}, teinte);
}
