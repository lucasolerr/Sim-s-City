#include "utils/grille.h"

Vector2I mouse_to_iso(Vector2I mouse, Image img) {
    Vector2I isoPos = cartesien_to_iso((Vector2I) {
            mouse.x / LARGUEUR_TUILE_ISO,
            mouse.y / HAUTEUR_TUILE_ISO
    });

    int offsetX = mouse.x % LARGUEUR_TUILE_ISO;
    int offsetY = mouse.y % HAUTEUR_TUILE_ISO;

    Color color = GetImageColor(img, offsetX, offsetY);

    if (color.r && !color.g && !color.b) {
        //... cellule en -1 des X
        isoPos.x -= 1;
    } else if (!color.r && color.g && !color.b) {
        //.. cellule en +y
        isoPos.y += 1;
    } else if (color.r && color.g && !color.b) {
        //cellule en +x
        isoPos.x += 1;
    } else if (!color.r && !color.g && color.b) {
        //cellule  en -y
        isoPos.y -= 1;
    }

    return isoPos;
}

Vector2I cartesien_to_iso(Vector2I cartesien) {
    return (Vector2I) {
        .x = (cartesien.y - ISO_ORIGINE_Y) + (cartesien.x - ISO_ORIGINE_X),
        .y = (cartesien.y - ISO_ORIGINE_Y) - (cartesien.x - ISO_ORIGINE_X)
    };
}