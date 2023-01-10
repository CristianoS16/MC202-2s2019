//Aquivo .h contendo a declarações de tipos e funções que manipulam arvores
#ifndef TREEH
#define TREEH

//Registro para guardar os nos da arvore
struct node {
    int element;
    struct node *right, *left;
};
typedef struct node node;

//Registro para guardar os nos da fila
struct nodequeue{ 
    node *element;
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

//Funções relacionadas a arvore:
node* create_tree();
node* search(node *arv, int n);
node* insert_tree(node *arv, int n);
void pos_ordem(node *arv);
void em_ordem(node *arv);
void pre_ordem(node *arv);
void largura(node *arv);
void free_tree(node *arv);

//Funções relacionadas a fila:
queue* create_queue();
queue* insert_queue(queue* q, node* value);
node* dequeue(queue *q);
void delet_queue(queue *q);

#endif
