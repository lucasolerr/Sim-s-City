
#ifndef ECECITY_UI_H
#define ECECITY_UI_H

#include <raylib.h>
#include "sim/sim.h"

typedef enum BuildMode {
    BUILD_MODE_NONE,
    BUILD_MODE_ROUTE,
    BUILD_MODE_CENTRALE,
    BUILD_MODE_CHATEAU,
    BUILD_MODE_HABITATION,
    BUILD_MODE_CASERNE,
    BUILD_MODE_DESTROY,
} BuildMode;

typedef enum AffichageNiveau {
    AFFICHAGE_NIVEAU_NONE,
    AFFICHAGE_NIVEAU_ELEC,
    AFFICHAGE_NIVEAU_EAU
} AffichageNiveau_t;

/// Le mode de construction actuel.

enum TOOLBAR_ICON {
    ICON_HAMBURGER,
    ICON_SAVE,
    ICON_PEOPLE,
    ICON_ENERGY,
    ICON_WATER,
    ICON_BUILD,
    ICON_DESTROY,
    ICON_TIME,
    ICON_ROAD,
    ICON_HABITATION,
    ICON_CENTRALE,
    ICON_CHATEAU,
    ICON_GRID,
    ICON_WATER_GRID,
    ICON_ELECTRICITY_GRID,
    ICON_CHECK,
    ICON_CANCEL,
    ICON_ADD,
    ICON_CASERNE,
    ICON_DOLLAR,
    ICON_PAUSE,
    ICON_NB_LOGOS_TOOLBAR
};

typedef struct {
    bool hoverAdd;
    bool hoverSel;
    bool hoverCancel;
    bool hoverComponent;
    bool select_component;
    int num_component_hover;
    int num_component_select;
    bool clickAdd;
    bool modeAjout;
    bool clickSel;
    bool clickCancel;
    char nomFichier[10];
    char nomFichierOuverture[10];
    int indice;
    bool resetNbSauvegardes;
    bool modeMenu;
    bool modeSave;
} StateMenuSave_t;

typedef struct {
    int nb_sauvegardes;
    char nom_sauvegardes[10][260];
    char* sauvegardes_time[10];
} SaveHistory_t;

typedef struct StateToolbar_t {
    StateMenuSave_t stateMenuSave;
    SaveHistory_t saveHistory;
    bool hoverNiveauNormal;
    bool hoverNiveauEau;
    bool hoverNiveauElectricite;
} ToolbarHoverState_t;


/// Contient l'état de l'interface utilisateur.
typedef struct UIState {
    Texture2D toolbarIcons[ICON_NB_LOGOS_TOOLBAR];
    /// Mode de construction actuel
    enum BuildMode currentBuildMode;
    /// Mode d'affichage actuel
    enum AffichageNiveau affichageNiveau;
    /// Multiplicateur de vitesse de jeu
    float timeScale;
    /// Informations sur l'état de hover des trucs de la toolbar.
    ToolbarHoverState_t stateToolbar;
} UIState;

/// Charger les textures pour l'interface utilisateur.
void ui_charger_textures(UIState* textures);

/// Dessine l'interface utilisateur.
void ui_draw_toolbar(UIState* states, SimWorld_t* sim);

/// Met a jour l'état des boutons de l'UI.
void ui_update_toolbar(UIState* textures, SimWorld_t* sim);

CaseKind_t ui_buildmode_to_casekind(BuildMode mode);

#endif //ECECITY_UI_H
