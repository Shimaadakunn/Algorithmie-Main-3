#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arbre.h"

int main(){

    Abr *arbre = NULL;

    add(&arbre, 30);
    add(&arbre,10);
    add(&arbre,50);
    add(&arbre,5);
    add(&arbre,15);
    add(&arbre,1);
    add(&arbre,22);
    add(&arbre,18);
    add(&arbre,13);
    printDot(arbre,"./Fichiers .dot/arbre.dot");

    printDot(supp(arbre, 15),"./Fichiers .dot/supp.dot");

    histD(10,0,25);
    histH(10,0,25);
    
}