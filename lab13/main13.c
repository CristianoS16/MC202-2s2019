#include <stdio.h>
#include <stdlib.h>
#include "lab13.h"

int main(){
    int n, i;
    scanf("%d", &n);    //Ler os vertices possiveis
    int E[n*(n-1)], V[(n+1)];   //E para guardar os vizinhos e V para guardar os vertices    
    for(i=0; i<(n+1); i++)
        V[i] = 0;
    for(i=0; i<(n*(n-1)); i++)
        E[i] = 0;
    create_graph(V, E, n);    
    BFS(V, E, n);
    return 0;
}