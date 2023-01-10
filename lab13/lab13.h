#ifndef grafo
#define grafo

//Registro para guardar os nos da fila
struct nodequeue{ 
    int element;
    int distance;
    struct nodequeue *prox;
    struct nodequeue *prev;
};
typedef struct nodequeue nodequeue;

//Registo para guardar uma fila
struct queue{
    nodequeue *head;
    nodequeue *tail;
};
typedef struct queue queue;

//Funções relacionadas a fila:
queue* create_queue();
queue* insert_queue(queue* q, int value, int d);
int dequeue(queue *q, int* d);
void delet_queue(queue *q);

//Funções para grafo e BFS
void create_graph(int* V, int* E, int n);
void BFS(int* V, int *E, int n);
void jump(int* E, int n, int i);
void inclement(int* V, int n, int i);

#endif 