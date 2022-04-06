#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_data.h"

int main() {

    Graphe *graphe = creer_graph("./Instances/graph-1", true);
    
    // print_graphe(graphe);
    
    

    // DFS(graphe,5);
    // print_visited(graphe);

    // printf("%d\n",connexity(graphe));

    invert(graphe);
    // print_graphe(invert(graphe));
    
    free_graph(graphe);
    
    // creer_dot("./Instances/graph-3", false);
    
   return 0;
}