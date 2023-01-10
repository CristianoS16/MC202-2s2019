#include <stdio.h>
#include <stdlib.h>
#include "lab13.h"

//Funções para filas:

//Função para criar uma fila
queue* create_queue(){
    queue *q = malloc(sizeof(queue));
    //Caso a alocação falhe
    if(!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

//Função para adicionar um novo nó na fila
queue* insert_queue(queue* q, int value, int d){
    nodequeue *new = malloc(sizeof(nodequeue));
    //Caso a alocação falhe
    if(!new)
        printf("deu ruim");
    new->element = value;
    new->distance = d;
    //Caso em que a fila esta vazia
    if(q->head == NULL){
        new->prox = NULL;
        new->prev = NULL;
        q->head = new;
        q->tail = new;
        return q;
    }
    //Caso geral
    new->prox = q->head; 
    new->prev = NULL;
    q->head->prev = new;
    q->head = new;
    return q;
}

//Função para desenfilerar(retirar o ultimo)
int dequeue(queue *q, int* d){
    if(q->head != NULL){
        int aux = q->tail->element;
        printf("%d %d\n", q->tail->element, q->tail->distance);
        *d = q->tail->distance;
        nodequeue* auxaux = q->tail;
        //Verifica se há mais de um elemento na fila
        if(auxaux->prev != NULL){
            auxaux->prev->prox = NULL;
        }
        q->tail = q->tail->prev;
        //Verifica se apos a modificação a fila ficou vazia
        if (q->tail == NULL){
            q->head = NULL;
        }
        
        free(auxaux);
        return aux;
    }
    return 0; //Se tirar isso aqui nao compila sem warning
}

//Função para liberar a memoria de uma fila
void delet_queue(queue *q){
    nodequeue *auxaux, *aux = q->tail;
    //Percorre a fila liberando a memoria
    while(aux != NULL){
        auxaux = aux;
        aux = aux->prev;
        free(auxaux);
    }
}

//Função para deslocar posições do vetor de vizinhos
void jump(int *E, int n, int i){
    int x, y = n*(n-1);
    while(y>=i){
        if(y==0)
            break;
        x=y-1;
        E[y] = E[x];
        y--;
    }
}

//Função para inclementar o vetor de vertices 
void inclement(int* V, int n, int i){
    int x;
    for(x=i; x<(n+1); x++)
        V[x] = V[x]+1;
}

//Função para cria um grado em um vetor de adjacencia
void create_graph(int *V, int *E, int n){
    int i, j;
    //Para cada vertice lido o vetor de vizinhos e deslocado para abrir espaço, e o vetor de vertice e inclementado devido ao deslocamento no vetor de vizingos
    while(scanf("%d,%d", &i, &j) && (i!=0 || j!=0)){
        jump(E, n, V[i-1]);
        E[V[i-1]] = j;
        inclement(V, n, i);
        jump(E, n, V[j-1]);
        E[V[j-1]] = i;
        inclement(V, n, j);
        
    }
}

//Função para realizar o percurso em largura 
void BFS(int* V, int* E, int n){
    int s, d=0, x, y;
    int vet[n];
    //Vetor para marcar quais arestas ja foram visitadas, vertice e imprimido na função
    for(s=0; s<n; s++)
        vet[s] = 0;
    scanf(" %d", &s);
    printf("Origem da busca: %d\n", s);
    printf("Vertices alcancados e distancias:\n");
    queue *fl = create_queue();
    insert_queue(fl, s, d);
    vet[s-1] = 1;
    d++;
    while(fl->head != NULL){
        x = dequeue(fl, &d);;            
        for(y=V[x-1]; y<V[x]; y++){
            if(vet[E[y]-1] == 0){
                insert_queue(fl, E[y], d+1);
                vet[(E[y]-1)] = 1;
            }
        } 
    }
    delet_queue(fl);
    free(fl);
}
