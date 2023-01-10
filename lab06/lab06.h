//Aquivo .h contendo a declarações de tipos e funções que manipulam a lista
#ifndef LISTAH
#define LISTAH
typedef struct node{ 
    int element;
    int cont;
    struct node *next;
}node;

void insert(node **p, int n);
int remov(node **p, int n);
node* reset(node **p, int n);

#endif
