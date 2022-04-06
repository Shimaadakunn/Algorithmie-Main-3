#ifndef ___ARBRE___
#define ___ARBRE___

typedef struct arbre {
    int key;
    struct arbre* droite;
    struct arbre* gauche;
} Abr;

//fonctions d'édition
void add(Abr **arbre, int key);
Abr* supp(Abr *arbre, int key);

//fonctions de recherche
int searchKey(Abr *arbre, int key);
Abr *successeur(Abr *arbre, int key);
Abr *predecesseur(Abr *arbre, int key);
int desequilibre(Abr *arbre);
int hauteur(Abr *arbre);

//fonctions d'affichage
void printAbr(Abr *arbre);
void printDot(Abr *arbre, char *fichier);
void dotRecursive(Abr *arbre, char *name);

//fonction de libération de mémoire
void clear(Abr **arbre);

//Partie B
//Génération de 50 tableaux aléatoires de taille n
int *data(int n, int valMin, int valMax);
void histH(int n, int valMin, int valMax);
void histD(int n, int valMin, int valMax);

#endif