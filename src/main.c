#include <stdio.h>
#include "raylib.h"
#include "jeu.h"
#include "menu_principal.h"

int main() {
    Jeu_t jeu = {
            .should_exit = false,
            .screen = NULL
    };
    jeu_run(&jeu, menu_principal_alloc());
    return 0;
}
