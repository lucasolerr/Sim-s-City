
#ifndef ECECITY_JEU_H
#define ECECITY_JEU_H

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>


#define FENETRE_JEU_LARGEUR 1600
#define FENETRE_JEU_HAUTEUR 1024

#ifndef NDEBUG
#define DBG_LOG(text, ...) TraceLog(LOG_INFO, text, ##__VA_ARGS__)
#else
#define DBG_LOG(text, ...)
#endif

// prédéclaration pour les callbacks.
struct Jeu_t;
struct ScreenInfo_t;

/// Callbacks pour les écrans.

typedef void (*ScreenCb_Update)(struct Jeu_t*, struct ScreenInfo_t *);
typedef void (*ScreenCb_Draw)(struct Jeu_t*, struct ScreenInfo_t *);
typedef void (*ScreenCb_Exit)(struct Jeu_t*, struct ScreenInfo_t *);
typedef void (*ScreenCb_Enter)(struct Jeu_t*, struct ScreenInfo_t *);

/// Structure contenant les pointeurs vers les callbacks de dessin / maj d'un écran du jeu.
typedef struct ScreenInfo_t {
    /// Appelé chaque frame pour dessiner le contenu de l'écran.
    ScreenCb_Draw draw_callback;
    /// Appelé chaque frame pour effectuer des calculs / opérations avant le dessin de l'écran.
    ScreenCb_Update update_callback;
    /// Appelé lorsque lors de la transition d'un écran vers cet écran.
    ScreenCb_Enter on_enter_callback;
    /// Appelé lorsque lors de la transition de cet écran vers un autre écran.
    ScreenCb_Exit on_exit_callback;
    /// Nom de l'écran à des fins de débogage.
    const char* screen_name;
} ScreenInfo_t;

typedef struct Jeu_t {
    /// Ecran de jeu actuellement affiché.
    ScreenInfo_t* screen;
    /// Le jeu doit-il se fermer?
    bool should_exit;
} Jeu_t;

/// Lance la boucle principale du jeu.
void jeu_run(Jeu_t* jeu, ScreenInfo_t* ecran_depart);

/// Change l'écran actuellement affiché avec celui passé en paramètre.
void jeu_switch_screen(Jeu_t* jeu, ScreenInfo_t* ecran);

/// Quitte le jeu
inline void jeu_quitter(Jeu_t* jeu) { jeu->should_exit = true; }

#endif //ECECITY_JEU_H
