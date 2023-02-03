#include "sim/casernes.h"

/// Allocation d'une caserne de pompier.
/// @return CasernePompier_t - adresse de structure CasernePompier_t allouée dynamiquement
CasernePompier_t* alloc_caserne(){
    CasernePompier_t* caserne = malloc(sizeof(CasernePompier_t));
    caserne->habitations = vector_alloc(10);
    return caserne;
}

/// Dessine le statut "en feu" d'une habitation.
void draw_enfeu(SimWorld_t *world, SpriteSheet_t* sheet){
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        if(hab->enfeu == true){
            DrawTexture(sheet->spriteFeu, (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                                                                 hab->position.y * (SPRITELARGEUR / 2), (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                                                                                                        hab->position.x * (SPRITEHAUTEUR / 2) - 10, WHITE);
        }
        maison = maison->next;
    }
}

/// Détruit d'une caserne.
/// @param caserne - adresse de structure CasernePompier_t allouée dynamiquement
void caserne_free(CasernePompier_t* caserne) {
    free(caserne);
}

