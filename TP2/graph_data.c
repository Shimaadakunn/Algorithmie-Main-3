#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_data.h"


Liste *ajouter(Liste *liste, int nvNombre)
{
    printf("Oblige de printf quelque chose pour faire fonctinner ma fonction ajouter\n");
    Liste *new_node = (Liste*)malloc(sizeof(Liste));

    new_node->sommet = nvNombre;
    new_node->next = NULL;
    
    if(liste == NULL) return new_node;
    
    else {
        Liste* temp = liste;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new_node;
        return liste;
    }
}

void afficherListe(Liste *liste)
{
    Liste* tmp = liste;
    /* Tant que l'on n'est pas au bout de la liste */
    while(tmp != NULL)
    {
        /* On affiche */
        printf("%d ", tmp->sommet);
        /* On avance d'une case */
        tmp = tmp->next;
    }
}

void print_graphe(Graphe *graphe){
    for(int i=0; i < graphe->nbr_sommets; i++) {
        printf("%d", i+1);
        printf(" -> ");
        afficherListe(graphe->adj[i]);
        printf("\n");
    }
}

void free_graph(Graphe *graphe){
    for(size_t i=0; i < graphe->nbr_sommets; i++)
    {
        free_list(graphe->adj[i]); //supprime une liste chainnée
    }
    graphe = NULL;
}

void free_list(Liste *liste){
    Liste *tmp, *tmp2;
    tmp = liste;
    while(tmp != NULL)
    {
        tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
}

Graphe *creer_graph(char *fichier, bool oriented){

    FILE *f_txt;
    char *fichier_txt;
    fichier_txt = (char *) malloc( strlen( fichier ) + 1 );
    strcat(strcpy(fichier_txt,fichier),".txt");

    f_txt = fopen(fichier_txt,"r");
    
    if(f_txt == NULL)
    {
        printf("Error!");   
        exit(1);
    }
    
    int nbr_sommets, nbr_aretes, sommet_1, sommet_2;
    Graphe *graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe->adj = (Liste **)malloc(sizeof(Liste*));
    graphe->visited = (int *)malloc(sizeof(int));
    
    char line[800];
    if(fgets(line, sizeof(line), f_txt)) sscanf(line, "%d", &nbr_sommets); 
    if(fgets(line, sizeof(line), f_txt)) sscanf(line, "%d", &nbr_aretes);
    
    graphe->nbr_sommets = nbr_sommets;
    graphe->nbr_aretes = nbr_aretes;
    graphe->oriented = oriented;
    
    for(int i = 0; i < graphe->nbr_sommets; i++) {
        graphe->adj[i] = NULL;
        graphe->visited[i] = 0;
    }    
    
    while(fgets(line, 800, f_txt)){
        sscanf(line, "%d %d", &sommet_1, &sommet_2);
        graphe->adj[sommet_1-1] = ajouter(graphe->adj[sommet_1-1],sommet_2);
        if (graphe->oriented == false) graphe->adj[sommet_2-1] = ajouter(graphe->adj[sommet_2-1],sommet_1);
    }
    fclose(f_txt);
    return graphe;
}

void creer_dot(char *fichier, bool oriented)
{
    FILE *f_txt;    
    char *fichier_txt;
    int sommet_1, sommet_2;
    fichier_txt = (char *) malloc( strlen( fichier ) + 1 );
    strcat(strcpy(fichier_txt,fichier),".txt");

    FILE *f_dot;
    char *fichier_dot;
    fichier_dot = (char *) malloc( strlen( fichier ) + 1 );
    strcat(strcpy(fichier_dot,fichier),".dot");

    
    f_txt = fopen(fichier_txt,"r");
    f_dot = fopen(fichier_dot,"w");

    char line[256];
    int nbr_sommets;
    if(fgets(line, sizeof(line), f_txt)) sscanf(line, "%d", &nbr_sommets);
    fgets(line, sizeof(line), f_txt);

    int *visited;
    
    visited = (int *)malloc(sizeof(int));
    
    for(int i = 0; i < nbr_sommets; i++) visited[i] = 0;
    
    if (oriented == 0){
        fputs("graph G{", f_dot);
        while (fgets(line, sizeof(line), f_txt)) {
            sscanf(line, "%d %d", &sommet_1, &sommet_2);
            fputs("\n    ",f_dot);
            fprintf(f_dot, "%d", sommet_1);
            fputs(" -- ",f_dot);
            fprintf(f_dot, "%d", sommet_2);

            if(visited[sommet_1-1] == 0) visited[sommet_1-1] = 1;
            if(visited[sommet_2-1] == 0) visited[sommet_2-1] = 1;
        }
    }
    else if (oriented == 1){
        fputs("digraph G{", f_dot);
        while (fgets(line, sizeof(line), f_txt)) {
            sscanf(line, "%d %d", &sommet_1, &sommet_2);
            fputs("\n    ",f_dot);
            fprintf(f_dot, "%d", sommet_1);
            fputs(" -> ",f_dot);
            fprintf(f_dot, "%d", sommet_2);

            if(visited[sommet_1-1] == 0) visited[sommet_1-1] = 1;
            if(visited[sommet_2-1] == 0) visited[sommet_2-1] = 1;
        }

    }

    for(int i = 0; i < nbr_sommets; i++){
        if(visited[i] == 0) fprintf(f_dot, "\n    %d", i+1);
    }
    fputs("\n}", f_dot);
    
    fclose(f_txt);

}

void DFS( Graphe* graphe, int sommet) {

    Liste* temp = graphe->adj[sommet-1];
    graphe->visited[sommet-1] = 1;

    while (temp != NULL) {
        int sommet_connecte = temp->sommet;

        if (graphe->visited[sommet_connecte-1] == 0) {
         DFS(graphe, sommet_connecte);
        }
        temp = temp->next;
    }
}

void print_visited(Graphe* graphe){
    for(int i=0; i < graphe->nbr_sommets; i++) printf("Sommet %d visited? %d \n", i+1, graphe->visited[i]);
}

bool connexity(Graphe *graphe){

    for(int i = 0; i < graphe->nbr_sommets; i++) graphe->visited[i] = 0;

    DFS(graphe,1);

    for(int i = 0; i < graphe->nbr_sommets; i++) if(graphe->visited[i] != 1) return false;
    return true;
}

Graphe *invert(Graphe *graphe){

    printf("Oblige de printf quelque chose pour faire fonctinner ma fonction invert\n");
    if (graphe->oriented == false){
        printf("The graphe is not oriented\n");
        exit(1);
    }

    Graphe *inverted = (Graphe*)malloc(sizeof(Graphe));
    inverted->visited = (int *)malloc(sizeof(int));
    inverted->adj = (Liste **)malloc(sizeof(Liste*));

    inverted->nbr_sommets = graphe->nbr_sommets;
    inverted->nbr_aretes = graphe->nbr_aretes;
    inverted->oriented = graphe->oriented;
    
    for(int i = 0; i < inverted->nbr_sommets; i++) {
        inverted->adj[i] = NULL;
        inverted->visited[i] = 0;
    }

    Liste *tmp;

    for(int i = 0; i < graphe->nbr_sommets; i++){
        if (graphe->adj[i] != NULL){
            printf("Je traite la liste des adj du sommet %d\n", i+1);
            tmp = graphe->adj[i];
            while(tmp != NULL){
                printf("Je rajoute a la liste des adj au sommet %d, le sommet %d\n", tmp->sommet, i+1);
                inverted->adj[tmp->sommet-1] = ajouter(inverted->adj[tmp->sommet-1], i+1);
                // inverted->adj[2] = ajouter(inverted->adj[2], 1);
                tmp = tmp->next;
            }  
        }
    }
    print_graphe(inverted);
    return inverted;

}