#ifndef ___BALISE___
#define ___BALISE___

typedef struct arbre {
    int key;
    int deseq;
    struct arbre* droite;
    struct arbre* gauche;
} Abr;

//fonctions d'édition
void add(Abr **arbre, int key);
Abr* supp(Abr *arbre, int key);

Abr *rotGauche(Abr *arbre);
Abr *rotDroit(Abr *arbre);
Abr *rotGaucheDroit(Abr *arbre);
Abr *rotDroitGauche(Abr *arbre);

//fonctions de déséquilibre
int desequilibre(Abr *arbre);
int hauteur(Abr *arbre);

//fonction AVL
void abrDeseq(Abr *arbre);
int findDeseqKey(Abr *arbre);
void abrRotate(Abr **arbre);

//fonctions d'affichage
void printDot(Abr *arbre, char *fichier);
void dotRecursive(Abr *arbre, char *name);

//fonction de libération de mémoire
void clear(Abr **arbre);

#endif