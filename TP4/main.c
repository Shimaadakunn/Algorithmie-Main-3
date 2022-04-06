#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "balise.h"

int main(){

    Abr *arbre = NULL;

    add(&arbre, 50);
    add(&arbre, 90);
    add(&arbre, 25);
    add(&arbre, 20);
    // add(&arbre, 75);
    add(&arbre, 30);
    add(&arbre, 15);
    add(&arbre, 10);
    // add(&arbre, 28);
    // add(&arbre, 26);
    // add(&arbre, 87);
    // add(&arbre, 69);
    // add(&arbre, 60);
    
    printDot(arbre,"./Fichiers .dot/arbre.dot");
}