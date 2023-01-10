//Arquivo .c contendo as implementações das funções para arvore e fila
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lab09.h"

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
queue* insert_queue(queue* q, node* value){
    nodequeue *new = malloc(sizeof(nodequeue));
    //Caso a alocação falhe
    if(!new)
        printf("deu ruim");
    new->element = value;
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
node* dequeue(queue *q){
    if(q->head != NULL){
        node *aux = q->tail->element;
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
    return NULL;
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

//Funções para arvores:

//Função para criar uma arvore
node* create_tree(){
    return NULL;
}

//Função para realizar busca em uma arvore
node* search(node *arv, int n){
    //Se o nó não existir chega a uma folha e devolve NULL
    while (arv != NULL && arv->element != n){
        //Verifica por qual nó deve seguir a busca
        if (n < arv->element)
            arv = arv->left;
        else
            arv = arv->right;
        }
    return arv;
}

//Função para inserir um novo no em uma arvore
node* insert_tree(node *arv, int n){
    //Novos nós são inseridos apenas nas folhas
    if (arv == NULL){
        node *new = malloc(sizeof(node));
        if (!new){
            printf("Erro ao alocar memoria");
            return NULL;
        }
        new->element = n;
        new->left = new->right = NULL;
        return new;
    }
    //Chama a propria função passando uma nova raiz que corresponde ao "caminho" ate a folha onde o novo nó deve ser inserido
    if (n < arv->element)
        arv->left = insert_tree(arv->left, n);
    else
        arv->right = insert_tree(arv->right, n);
    return arv;
}

//Função para imprimir o conteudo da arvore em pós-ordem
void pos_ordem(node *arv){
     if (arv != NULL){
        pos_ordem(arv->left);
        pos_ordem(arv->right);
        printf("%d ", arv->element);
    }
}

//Função para imprimir o conteudo da arvore em em-ordem
void em_ordem(node *arv){
     if (arv != NULL){
        em_ordem(arv->left);
        printf("%d ", arv->element);
        em_ordem(arv->right);
    }
}

//Função para imprimir o conteudo da arvore em pré-ordem
void pre_ordem(node *arv){
     if (arv != NULL){
        printf("%d ", arv->element);
        pre_ordem(arv->left);
        pre_ordem(arv->right);
    }
}

//Função para imprimir o conteudo da arvore em largura
void largura(node *arv){
    node *i;
    //Cria uma fila e insere elementos
    queue *q = create_queue(); 
    q = insert_queue(q, arv);
    //Conforme percorre a arvore desemfileira(imprime) e enfilera novos elementos
    while ((i = dequeue(q)) != NULL){
        printf("%d ", i->element);
        if(i->left != NULL)
            insert_queue(q, i->left);
        if(i->right != NULL)
            insert_queue(q, i->right);
    }
    //Libera memoria da fila criada
    delet_queue(q);
    free(q);
}

//Função para liberar a memoria alocada pela arvore
void free_tree(node *arv){
    if (arv != NULL){
        free_tree(arv->left);
        free_tree(arv->right);
        free(arv);
    }
}
