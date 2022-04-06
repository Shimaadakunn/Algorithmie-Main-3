#ifndef GRAPH_DATA
#define GRAPH_DATA

typedef struct liste {
    int sommet;
    struct liste* next;
} Liste;

typedef struct graph{
    int nbr_sommets;
    int nbr_aretes;
    bool oriented;
    int* visited;
    Liste** adj;
}Graphe;


Graphe *creer_graph(char *fichier, bool oriented);
Liste *ajouter(Liste *liste, int nvNombre);
void afficherListe(Liste *liste);
void print_graphe(Graphe *graphe);
void creer_dot(char *fichier, bool oriented);
void free_graph(Graphe *graphe);
void free_list(Liste *liste);
void DFS(Graphe *graphe, int vertex);
void print_visited(Graphe* graphe);
bool connexity(Graphe *graphe);
Graphe *invert(Graphe *graphe);


#endif