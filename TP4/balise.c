#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "balise.h"

//fonctions d'édition
void add(Abr **arbre, int key){
    Abr *tmp;
    Abr *tmpAbr = *arbre;

    Abr *new = malloc(sizeof(Abr));
    new->key = key;
    new->droite = NULL;
    new->gauche = NULL;
    new->deseq = 0;

    if(tmpAbr)
    do
    {
        tmp = tmpAbr;
        if(key > tmpAbr->key)
        {
            tmpAbr = tmpAbr->droite;
            if(!tmpAbr) tmp->droite = new;
        }
        else
        {   
            tmpAbr = tmpAbr->gauche;
            if(!tmpAbr) tmp->gauche = new;
        }
    } while (tmpAbr);
    else *arbre = new;
    abrDeseq(*arbre); //mets à jour les valeurs de déséquilibre de chaque noeud
    // abrRotate(arbre); //rééquilibre l'abre si besoin
    
}
  
Abr* supp(Abr *arbre, int key){
    if(arbre == NULL) return NULL;

    if(key < arbre->key){
        arbre->gauche = supp(arbre->gauche, key);
        return arbre;
    } 
    else if (key > arbre->key){
        arbre->droite = supp(arbre->droite, key);
        return arbre;
    }

    Abr *tmp = NULL;
    if(arbre->gauche == NULL){
        tmp = arbre->droite;
        arbre = NULL;
        return tmp;
    }

    else if(arbre->droite == NULL){
        tmp = arbre->gauche;
        arbre = NULL;
        return tmp;
    }

    else {
        Abr* dad = arbre;
        Abr* succ = arbre->droite;
        while(succ->gauche != NULL){
            dad = succ;
            succ = succ->gauche;
        }
        if(dad != arbre) dad->gauche = succ->droite;
        else dad->droite = succ->droite;
        arbre->key = succ->key;
        succ = NULL;
        return arbre;
    }
    // succ = successeur(arbre, arbre->key);
    // arbre->key = succ->key;
    // arbre->droite = supp(arbre->droite, succ->key);
    
}

//fonctions de rotations
Abr *rotDroit(Abr *arbre){
    Abr *enfant = arbre->gauche;
    Abr *petitEnfant = enfant->droite;

    enfant->droite = arbre;
    arbre->gauche = petitEnfant;

    return enfant;
}

Abr *rotGauche(Abr *arbre){
    Abr *enfant = arbre->droite;
    Abr *petitEnfant = enfant->gauche;

    enfant->gauche = arbre;
    arbre->droite = petitEnfant;

    return enfant;
}

Abr *rotDroitGauche(Abr *arbre){
    Abr *noeudDroit = arbre->droite;
    Abr *nvHead = noeudDroit->gauche;
    Abr *nvHeadD = nvHead->droite;
    Abr *nvHeadG = nvHead->gauche;
    
    nvHead->droite = noeudDroit;
    nvHead->gauche = arbre;
    arbre->droite = nvHeadG;
    noeudDroit->gauche = nvHeadD;
    
    return nvHead;
}

Abr *rotGaucheDroit(Abr *arbre){
    Abr *noeudGauche = arbre->gauche;
    Abr *nvHead = noeudGauche->droite;
    Abr *nvHeadD = nvHead->droite;
    Abr *nvHeadG = nvHead->gauche;
    
    nvHead->droite = arbre;
    nvHead->gauche = noeudGauche;
    arbre->gauche = nvHeadD;
    noeudGauche->droite = nvHeadG;
    
    return nvHead;
}

//fonctions de déséquilibre
int desequilibre(Abr *arbre){//fonction qui calcule le déséquilibre d'un arbre
    return hauteur(arbre->droite) - hauteur(arbre->gauche);
}

int hauteur(Abr *arbre){//fonction qui calcule la hauteur d'un arbre
    if(arbre == NULL) return -1;

    int droite = hauteur(arbre->droite);
    int gauche = hauteur(arbre->gauche);

    return ((gauche > droite ? gauche : droite)+1);
}

//fonctions AVL
void abrDeseq(Abr *arbre){ //mise à jour des valeurs de déséquilibre de chaque noeud de l'arbre
    if(!arbre) return;
    arbre->deseq = desequilibre(arbre);
    // printf("noeud %d a comme desequilibre %d\n", arbre->key, arbre->deseq);
    abrDeseq(arbre->droite);
    abrDeseq(arbre->gauche);
}

void abrRotate(Abr **arbre){//reequilibrage d'un arbre s'il est déséquilibre
    Abr *tmp;
    Abr *tmpAbr = *arbre;
    int key = findDeseqKey(tmpAbr);
    int find = 0;
    printf("we are searching key %d\n", key);
    if(key == -1) {
        find = -5;
        return;
    }
    if(find == 0)
    do{
        tmp = tmpAbr;
        if(tmpAbr->key == key) {
            if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == 1) tmpAbr = rotGauche(tmpAbr);
            if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == -1) tmpAbr = rotDroitGauche(tmpAbr);
            if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == 1) tmpAbr = rotGaucheDroit(tmpAbr);
            if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == -1) tmpAbr = rotDroit(tmpAbr);
            *arbre = tmpAbr;
            find = 5;
        }
        else if(key > tmpAbr->key)
        {
            tmpAbr = tmpAbr->droite;
            if(tmpAbr->key == key) { //trouvé la clé déséquilibrée
                if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == 1) tmpAbr = rotGauche(tmpAbr);
                if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == -1) tmpAbr = rotDroitGauche(tmpAbr);
                if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == 1) tmpAbr = rotGaucheDroit(tmpAbr);
                if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == -1) tmpAbr = rotDroit(tmpAbr);
                
                tmp->droite = tmpAbr;
                find = 1;
            }
        }
        else if(key < tmpAbr->key)
        {   
            tmpAbr = tmpAbr->gauche;
            if(tmpAbr->key == key) { //trouvé la clé déséquilibrée
                if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == 1) tmpAbr = rotGauche(tmpAbr);
                if(tmpAbr->deseq == 2 && tmpAbr->droite->deseq == -1) tmpAbr = rotDroitGauche(tmpAbr);
                if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == 1) tmpAbr = rotGaucheDroit(tmpAbr);
                if(tmpAbr->deseq == -2 && tmpAbr->gauche->deseq == -1) tmpAbr = rotDroit(tmpAbr);
                tmp->gauche = tmpAbr;
                find = -1;
            }
        }
    }while(find == 0);
}

int findDeseqKey(Abr *arbre){//trouve la clée déséquilibrée qu'il faut rééquilibrer
    if(!arbre) return -1;
    if(abs(arbre->deseq) == 2){
        if(!arbre->droite) return arbre->key;
        if(!arbre->gauche) return arbre->key;
        if(abs(arbre->droite->deseq)!=2 && abs(arbre->gauche->deseq)!=2) return arbre->key;
    }

    printf("treating key %d has desq %d\n", arbre->key, arbre->deseq);
    int keyD = findDeseqKey(arbre->droite);
    int keyG = findDeseqKey(arbre->gauche);

    return ((keyG > keyD ? keyG : keyD));
}

//fonction d'affichage
void printDot(Abr *arbre, char *name){

    FILE* fichier = NULL;
    fichier = fopen(name,"w");
    fputs("digraph G{", fichier);
    fclose(fichier);

    dotRecursive(arbre,name);
    
    fichier = fopen(name,"a");
    fputs("\n}", fichier);
}

void dotRecursive(Abr *arbre, char *name){

    if(!arbre) return;

    FILE* fichier = NULL;
    fichier = fopen(name,"a");
    Abr *tmp = arbre;

    if(arbre->gauche){
        tmp = arbre->gauche;
        fputs("\n    ",fichier);
        fprintf(fichier, "%d", arbre->key);
        fputs(" -> ",fichier);
        fprintf(fichier, "%d", tmp->key);
        dotRecursive(arbre->gauche, name);
    }

    if(arbre->droite){
        tmp = arbre->droite;
        fputs("\n    ",fichier);
        fprintf(fichier, "%d", arbre->key);
        fputs(" -> ",fichier);
        fprintf(fichier, "%d", tmp->key);
        dotRecursive(arbre->droite, name);
    }
}
 
//fonction de libération de mémoire
void clear(Abr **arbre){
    Abr *tmp = *arbre;

    if(!arbre) return;
    if(tmp->gauche)  clear(&tmp->gauche);
    if(tmp->droite) clear(&tmp->droite);

    free(tmp);
    *arbre = NULL;
}
