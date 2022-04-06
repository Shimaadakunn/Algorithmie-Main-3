#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "arbre.h"

//fonctions d'édition
void add(Abr **arbre, int key){
    Abr *tmp;
    Abr *tmpAbr = *arbre;

    Abr *new = malloc(sizeof(Abr));
    new->key = key;
    new->droite = NULL;
    new->gauche = NULL;

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

//fonctions de recherche
int searchKey(Abr *arbre, int key){

    while(arbre){
        if(key == arbre->key) return 1;

        if(key > arbre->key) arbre = arbre->droite;
        else arbre = arbre->gauche;
    }
    return 0;
}

Abr *successeur(Abr *arbre, int key){
    int find = 1;

    while(find){
        if(key == arbre->key) find = 0;

        else if(key > arbre->key) arbre = arbre->droite;
        else arbre = arbre->gauche;
    }
    return arbre->droite;
}

int desequilibre(Abr *arbre){
    return abs(hauteur(arbre->droite) - hauteur(arbre->gauche));
}

int hauteur(Abr *arbre){
    if(arbre == NULL) return -1;

    int droite = hauteur(arbre->droite);
    int gauche = hauteur(arbre->gauche);

    return ((gauche > droite ? gauche : droite)+1);
}

//fonctions d'affichage
void printAbr(Abr *arbre){

    if(!arbre) return;

    if(arbre->gauche) printAbr(arbre->gauche);

    printf("%d -> ", arbre->key);

    if(arbre->droite) printAbr(arbre->droite);
}

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

//Tableau d'entiers de la moyenne des hauteurs et déséquilibres
int *data(int n, int valMin, int valMax){
    srand(time(NULL));
    Abr **tab = (Abr **)malloc(50*sizeof(Abr *));
    int *data = (int *)malloc(2*sizeof(int));
    data[0] = data[1] = 0;

    for(int i=0; i<50; i++){
        Abr *arbre = NULL;
        tab[i] = arbre;
        for(int j=0; j<n; j++){
            add(&arbre, valMin + rand() % (valMax + 1 - valMin));
        }
        data[0] = data[0] + hauteur(arbre);
        data[1] = data[1] + desequilibre(arbre);
    }
    data[0] = data[0]/50;
    data[1] = data[1]/50;
    return data;
}

//Fonction d'affichage d'un histogram en fonction du nombre n
void histH(int n, int valMin, int valMax){
    printf("\n\n Histogramme des moyennes de la hauteur \n");
    for(int i=1; i<=n; i++){
        if(i<10) printf("%d  |", i);
        if(i>9) printf("%d |", i);
        
        for(int j=0; j<data(i,valMin,valMax)[0]; j++) printf("%c", (char)254u);
        printf("\n");
    }
}

void histD(int n, int valMin, int valMax){
    printf("\n\n Histogramme des moyennes des desequilibres \n");
    for(int i=1; i<=n; i++){
        if(i<10) printf("%d  |", i);
        if(i>9) printf("%d |", i);
        
        for(int j=0; j<data(i,valMin,valMax)[1]; j++) printf("%c", (char)254u);
        printf("\n");
    }
}