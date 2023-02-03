#ifndef ECECITY_GRILLE_H
#define ECECITY_GRILLE_H

#define LARGUEUR_TUILE_ISO 40
#define HAUTEUR_TUILE_ISO 20

#define ISO_ORIGINE_X 17
#define ISO_ORIGINE_Y 3

#include <raylib.h>

typedef enum SimRules_t {
    Capitaliste_t,
    Communiste_t,
} SimRules_t;

typedef struct Vector2I {
    int x;
    int y;
} Vector2I;


/// Convertit les coordonnées de la souris en coordonnées isométriques à l'aide d'une image de référence.
Vector2I mouse_to_iso(Vector2I mouse, Image refImg);

/// Convertit les coordonnées cartésiennes en coordonnées isométriques.
Vector2I cartesien_to_iso(Vector2I cartesien);

#endif //ECECITY_GRILLE_H
