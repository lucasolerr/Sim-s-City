#include "bfs.h"

/// Un noeud pour le parcours en largeur.
typedef struct BFSNode_t {
    /// La position du noeud.
    Vector2I pos;
    /// La distance du noeud à la source.
    int distance;
} BFSNode_t;

/// Alloue un noeud pour le bfs
/// @param habitation - adresse de structure habitation allouée dynamiquement.
/// @param distance - int - distance depuis le sommet initial.
/// @return HabitationNode_t* - adresse de structure node allouée dynamiquement.
HabitationNode_t* node_alloc(Habitation_t* habitation, int distance) {
    HabitationNode_t* node = malloc(sizeof(HabitationNode_t));
    node->habitation = habitation;
    node->distance = distance;
    return node;
}
/// Alloue un noeud pour le bfs
/// @param pos - vecteur de deux dimension - position sur la carte.
/// @param d - int - distance depuis le sommet initial.
/// @return BFSNode_t* - adresse de structure node allouée dynamiquement.
BFSNode_t *bfs_node_alloc(Vector2I pos, int d) {
    BFSNode_t *bfs = malloc(sizeof(BFSNode_t));
    bfs->pos = pos;
    bfs->distance = d;
    return bfs;
}

/// Tente de mettre a jour un chemin si la distance est plus courte.
/// @param vecteur - tableau dynamique pour stocker les habitations découvertes.
/// @param d - int - distance depuis le sommet initial.
/// @param data - adresse de structure habitation allouée dynamiquement.
/// @return void.
void bfs_try_add_chemin(Vector_t* vecteur, int d, void* data) {
    for (int i = 0; i < vecteur->taille; ++i) {
        HabitationNode_t* node = vecteur->data[i];
        if (node->habitation == data) {
            node->distance = d < node->distance ? d : node->distance;
            return;
        }
    }
    vector_push(vecteur, node_alloc(data, d));
}

bool bfs_visiteur_habitation(Case_t* caseActuelle, int distance, Vector_t* resultats, void* batId) {
    if (caseActuelle->type == KIND_HABITATION) {
        Habitation_t* habitation = caseActuelle->donnees;
        bfs_try_add_chemin(resultats, distance, habitation);
        return true;
    }
    return false;
}

/// BFS
/// @param chemins - tableau dynamique pour stocker les habitations découvertes.
/// @param data - adresse de structure bâtiment allouée dynamiquement depuis lequel on effectue le bfs.
/// @param start - vecteur de deux dimension - position initiale sur la carte pour effectuer le bfs.
/// @param world - Structure du monde de simulation alloué dynamiquement.
/// @return void.
void bfs(SimWorld_t* world, Vector2I start, void* batId, Vector_t* chemins, VisiteurBFS_t visiteur) {

    BFSNode_t *start_node = bfs_node_alloc(start, 0);
    bool visited[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {false};

    Liste_t* file = liste_alloc();
    liste_ajouter_fin(file, start_node);

    while (!liste_estVide(file)) {
        BFSNode_t* node = liste_supprimer_debut(file);

        // ne pas traiter si hors limites
        if (node->pos.x < 0 || node->pos.x > SIM_MAP_LARGEUR || node->pos.y < 0 || node->pos.y > SIM_MAP_HAUTEUR) {
            free(node);
            continue;
        }

        // ne pas traiter si déja visitée.
        if (visited[node->pos.x][node->pos.y]) {
            free(node);
            continue;
        }

        // si c'est vide ne pas visiter
        if (world->map[node->pos.x][node->pos.y].type == KIND_VIDE) {
            free(node);
            continue;
        }

        // si la fonction de visite de noeud retourne true, ne pas visiter les voisins.
        if (visiteur != NULL && visiteur(&world->map[node->pos.x][node->pos.y], node->distance, chemins, batId)) {
            free(node);
            continue;
        }

        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (abs(i) == abs(j)) continue; // On ne veut que les voisins directs "de von neumann"

                Vector2I nextPos = {node->pos.x + i, node->pos.y + j};

                if (node->pos.x + i < 0 || node->pos.x + i > SIM_MAP_LARGEUR || node->pos.y + j < 0 || node->pos.y + j > SIM_MAP_HAUTEUR)
                    continue;

                if (!visited[nextPos.x][nextPos.y]) {
                    switch (world->map[nextPos.x][nextPos.y].type) {
                        case KIND_VIDE:
                            break;

                        case KIND_ROUTE:
                            liste_ajouter_fin(file, bfs_node_alloc(nextPos, node->distance + 1));
                            break;

                        case KIND_HABITATION:
                            liste_ajouter_fin(file, bfs_node_alloc(nextPos, node->distance));
                            break;

                        case KIND_CENTRALE:
                        case KIND_CASERNE:
                        case KIND_CHATEAU:
                            if (world->map[nextPos.x][nextPos.y].donnees == batId)
                                liste_ajouter_fin(file, bfs_node_alloc(nextPos, node->distance));
                        default:
                            break;
                        }
                    }
                }
            }

        visited[node->pos.x][node->pos.y] = true;
        free(node);
    }

    // on trie les résultats par distance
    vector_sort(chemins, trier_noeux_habitations_par_distance);

}

int trier_noeux_habitations_par_distance(HabitationNode_t* node, HabitationNode_t* node2) {
    return node->distance - node2->distance;
}

int trier_noeux_habitations_par_niveau(HabitationNode_t* node, HabitationNode_t* node2) {
    int d = node2->habitation->niveau - node->habitation->niveau;
    return d;
}

int trier_noeux_habitations_par_eau(HabitationNode_t* node, HabitationNode_t* node2) {
    int d = node2->habitation->eau - node->habitation->eau;
    return d;
}