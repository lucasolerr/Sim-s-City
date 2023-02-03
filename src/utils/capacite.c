#include "sim/chateau.h"
#include "sim/sim.h"
#include "affichage.h"
#include "screens/gameplay.h"
#include <math.h>


///afficher les capacités des centrales et chateaux

void afficher_capacite(SimWorld_t* world, bool eau) {
    if (!eau) {
        struct Maillon_t *centrales = world->centrales->premier;
        while (centrales) {
            CentraleElectrique_t *centraleElectrique = (CentraleElectrique_t *) centrales->data;
            DrawText(TextFormat("%d/5000", centraleElectrique->capacite),
                     (ORIGINEX * SPRITELARGEUR) + centraleElectrique->position.x * (SPRITELARGEUR / 2) -
                     centraleElectrique->position.y * (SPRITELARGEUR / 2),
                     (ORIGINEY * SPRITEHAUTEUR) + centraleElectrique->position.y * (SPRITEHAUTEUR / 2) +
                     centraleElectrique->position.x * (SPRITEHAUTEUR / 2), 20, WHITE);
            centrales = centrales->next;

            struct Maillon_t* maisons = world->habitations->premier;
            while (maisons) {
                Habitation_t* habitation = (Habitation_t*) maisons->data;
                bool should_display = habitation_get_required_energy(habitation, world->rules) > 0;
                if (should_display) {
                    DrawText(TextFormat("%d / %d", habitation->electricite,
                                        habitation_get_required_energy(habitation, world->rules)),
                             (ORIGINEX * SPRITELARGEUR) + habitation->position.x * (SPRITELARGEUR / 2) -
                             habitation->position.y * (SPRITELARGEUR / 2),
                             (ORIGINEY * SPRITEHAUTEUR) + habitation->position.y * (SPRITEHAUTEUR / 2) +
                             habitation->position.x * (SPRITEHAUTEUR / 2), 20, WHITE);
                }
                maisons = maisons->next;
            }
        }
    }else {
        struct Maillon_t *chateaux = world->chateaux->premier;
        while (chateaux) {
            ChateauEau_t *chateauEau = (ChateauEau_t *) chateaux->data;
            DrawText(TextFormat("%d/5000", chateauEau->capacite),
                     (ORIGINEX * SPRITELARGEUR) + chateauEau->position.x * (SPRITELARGEUR / 2) -
                     chateauEau->position.y * (SPRITELARGEUR / 2),
                     (ORIGINEY * SPRITEHAUTEUR) + chateauEau->position.y * (SPRITEHAUTEUR / 2) +
                     chateauEau->position.x * (SPRITEHAUTEUR / 2), 20, WHITE);
            chateaux = chateaux->next;
        }

        struct Maillon_t* maisons = world->habitations->premier;
        while (maisons) {
            Habitation_t* habitation = (Habitation_t*) maisons->data;
            bool should_display = habitation_get_required_water(habitation, world->rules) > 0;
            if (should_display) {
                DrawText(
                        TextFormat("%d / %d", habitation->eau, habitation_get_required_water(habitation, world->rules)),
                        (ORIGINEX * SPRITELARGEUR) + habitation->position.x * (SPRITELARGEUR / 2) -
                        habitation->position.y * (SPRITELARGEUR / 2),
                        (ORIGINEY * SPRITEHAUTEUR) + habitation->position.y * (SPRITEHAUTEUR / 2) +
                        habitation->position.x * (SPRITEHAUTEUR / 2), 20, WHITE);
            }
            maisons = maisons->next;
        }
    }
}

///afficher le niveay -1 des canalisations

void afficher_level_eau(SpriteSheet_t* sheet, SimWorld_t* world){
    struct Maillon_t* chateaux = world->chateaux->premier;
    while(chateaux){
        ChateauEau_t* chateauEau = (ChateauEau_t*)chateaux->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, BLUE, chateauEau->position.x, chateauEau->position.y);
        chateaux = chateaux->next;
    }
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        affichage_draw_habitation(sheet, hab, BLUE);
        maison = maison->next;
    }
}

///afficher le niveau -2 de l'electricité

void afficher_level_elec(SpriteSheet_t* sheet, SimWorld_t* world){
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centraleElectrique = (CentraleElectrique_t*)centrales->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, YELLOW, centraleElectrique->position.x, centraleElectrique->position.y);
        centrales = centrales->next;
    }
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        affichage_draw_habitation(sheet, hab, YELLOW);
        maison = maison->next;
    }
}

void afficher_level(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay){
    Rectangle textBoxElec = {440, 950, 50, 50};
    Rectangle textBoxEau = {660, 950, 50, 50};
    if (CheckCollisionPointRec(GetMousePosition(), textBoxEau)) {
        afficher_level_eau(&gameplay->spriteSheet, gameplay->world);
    }
    if (CheckCollisionPointRec(GetMousePosition(), textBoxElec)) {
        afficher_level_elec(&gameplay->spriteSheet, gameplay->world);
    }
}

void afficher_etat_alim_eau(SpriteSheet_t* sheet, SimWorld_t* world) {
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        if(!hab->alimentee_en_eau)
        {
            int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR/2) - hab->position.y * (SPRITELARGEUR/2);
            int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR/2) + hab->position.x * (SPRITEHAUTEUR/2) + 16;

            DrawTextureRec(sheet->spritesheetEtatsHabitations, (Rectangle) {
                .x = 32,
                .y = 0,
                .width = 32,
                .height = 32
            }, (Vector2) {
                .x = oX,
                .y = oY
            }, WHITE);
        }
        maison = maison->next;
    }
}

void afficher_etat_alim_elec(SpriteSheet_t* sheet, SimWorld_t* world) {
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;

        if (!hab->alimentee_en_electricite) {

            int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                     hab->position.y * (SPRITELARGEUR / 2);
            int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                     hab->position.x * (SPRITEHAUTEUR / 2) + 16;

            DrawTextureRec(sheet->spritesheetEtatsHabitations, (Rectangle) {
                    .x = 0,
                    .y = 0,
                    .width = 32,
                    .height = 32
            }, (Vector2) {
                    .x = oX,
                    .y = oY
            }, WHITE);
        }

        maison = maison->next;
    }
}
