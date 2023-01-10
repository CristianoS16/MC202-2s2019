//Arquivo .c contendo as implementações das funções para arvore e fila
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lab10.h"

//Funções para pilha de nos de arvore:

//Função para adicionar um novo elemento a pilha
nodestack* push(nodestack* pl, node* nodearv){
    nodestack *new = malloc(sizeof(nodestack));
    //Caso a alocação falhe
    if(!new)
        return NULL;
    new->root = nodearv;
    //Caso seja o primeiro elemento da pilha
    if(pl==NULL){
        new->next = NULL;
        return new;
    }
    new->next = pl;
    return new;
}

//Função para desempilhar
node* pop(nodestack** pl){
    if(*pl == NULL)
        return NULL;
    nodestack *aux = *pl;
    node *no = aux->root;
    *pl = aux->next;
    free(aux);
    return no;
}

//Função para liberar memoria usada pela pilha
void free_stack(nodestack *pl){
    if(pl!=NULL){
        free_stack(pl->next);
        free(pl);
    }
}

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

//Função para trocar o conteudo de dois nós, remtorna 1 caso o no trocado passua algum filho
int exchange(node* A, node* B){
    if(B->right!=NULL || B->left!=NULL)
        return 1;
    int aux = A->element;
    A->element = B->element;
    B->element = aux;
    return 0;
}

//Função para remover um nó da arvore
node* remove_tree(node* arv, int n){
    node *auxaux = arv, *aux = search(arv, n);
    int i;
    //Caso em que o nó não esta na arvore
    if(aux == NULL)
        return arv;
    //Caso em que o nó a ser removido é uma folha
    else if(aux->left == NULL && aux->right == NULL){
        //Caso para remover de uma arvore unitaria, raiz
        if(aux->element==auxaux->element){
            free(aux);
            return NULL;
        }
        nodestack* pl = NULL;
        //Percorre arvore empilhando caminho
        while(auxaux->element != n && auxaux != NULL){
            pl = push(pl, auxaux);
            if (n < auxaux->element)
                auxaux = auxaux->left;
            else
                auxaux = auxaux->right;
        }
        auxaux = pop(&pl);
        //Verifica se o filho da direita ou da esquerda
        if (auxaux->left == aux)
            auxaux->left = NULL;
        else
            auxaux->right = NULL;
        //Libera nó e pilha
        free(aux);
        free_stack(pl);
        return arv; 
    }
    //Caso em que o nó a ser removido possui um unico filho
    else if(aux->left == NULL || aux->right == NULL){
        //Troca nó com seu filho e remove o filho
        if(aux->left != NULL){
            i = exchange(aux, aux->left);
            //Caso o filho do nó também possua filhos
            if(i){
                nodestack* pl = NULL;
                //Percorre arvore empilhando caminho
                while(auxaux->element != n && auxaux != NULL){
                    pl = push(pl, auxaux);
                    if (n < auxaux->element)
                        auxaux = auxaux->left;
                    else
                        auxaux = auxaux->right;
                }
                //Caso o no a ser removido seha a raiz
                if(auxaux == arv){
                    free(auxaux);
                    return arv->left;
                }
                auxaux = pop(&pl);
                if(auxaux->left == aux){
                    auxaux->left = aux->left;
                }
                else    
                    auxaux->right = aux->left;
                //libera memoria alocada
                free(aux);
                free_stack(pl);
            }
            //Caso o filho do nó a ser removido não tenha filhos
            else{
                free(aux->left);
                aux->left = NULL;
            }
        }
        else{
            i = exchange(aux, aux->right);
            //Caso o filho do nó também possua filhos 
            if(i){
                nodestack* pl = NULL;
                //Percorre arvore empilhando caminho
                while(auxaux->element != n && auxaux != NULL){
                    pl = push(pl, auxaux);
                    if (n < auxaux->element)
                        auxaux = auxaux->left;
                    else
                        auxaux = auxaux->right;
                }
                //Caso o no a ser removido seha a raiz
                if(auxaux == arv){
                    free(auxaux);
                    return arv->right;
                }
                auxaux = pop(&pl);
                if(auxaux->left == aux){
                    auxaux->left = aux->right;
                }
                else 
                    auxaux->right = aux->right;
                free(aux);
                free_stack(pl);
            }
            //Caso o filho do nó a ser removido não tenha filhos
            else{
                free(aux->right);
                aux->right = NULL;
            }
        }
    return arv;
    }
    //Caso de remoção de um nó interno na arvore
    else{
        node* suc = successor(arv, n);
        nodestack* pl = NULL;        
        //Percorre arvore empilhando caminho ate o sucessor
        while(auxaux->element != suc->element && auxaux!= NULL){
            pl = push(pl, auxaux);
            if (n < auxaux->element)
                auxaux = auxaux->left;
            else
                auxaux = auxaux->right;
        }
        //Troca nó com seu sucessor
        i = aux->element;
        aux->element = suc->element;
        suc->element = i;
        node *psuc = pop(&pl);
        //Caso em que o pai so sucessor e o nó a ser removido
        if(aux == psuc){
            aux->right = suc->right;
            free(suc);
            free_stack(pl);
            return arv;
        }
        //Como o sucessor nao possui filho esquerdo basta fazer o pai dele apontar para seu filho da direita
        psuc->left = suc->right;
        //Libera memoria alocada
        free(suc);
        free_stack(pl);     
        return arv;
    }
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

//Função para encontrar o minimo de uma arvore
node* minimum(node *arv){
    if(arv == NULL)
        return NULL;
    while (arv->left != NULL)
       arv = arv->left;
    return arv;
}

//Função para encontrar o maximo de uma arvore
node* maximum(node *arv){
    if(arv == NULL)
        return NULL;
    while (arv->right != NULL)
       arv = arv->right;
    return arv;
}
//Função para encontrar o sucessor de um determinado nó da arvore
node* successor(node *arv, int n){
    node *p, *aux = search(arv, n);
    //Para o caso da arvore vazia e de estar buscando sucessor de um elemento que nao existe na arvore
    if(arv == NULL || aux == NULL)
        return NULL;
    //Para o caso onde o elemento tem filho da direita, o sucessor e o minimo da subarvore que tem o filho diretio como raiz
    else if(aux->right != NULL)
        return minimum(aux->right);
    else{
        //Nesse caso e usada uma pilha para guardar o caminho ate o elemento e depois achar seu sucessor
        nodestack* pl = NULL;
        while(arv->element != n){
            pl = push(pl, arv);
            if (n < arv->element)
                arv = arv->left;
            else
                arv = arv->right;
        }
        //Buscamos de qual raiz presente na pilha o elemento n é maximo
        p = pop(&pl);
        while(p != NULL && aux == (p->right)){
            aux = p;
            p = pop(&pl);
        }
        free_stack(pl);
        return p;
    }
}

//Função para encontrar o predecessor de um determinado nó da arvore
node* predecessor(node *arv, int n){
    node *p, *aux = search(arv, n);
    //Para o caso da arvore vazia e de estar buscando sucessor de um elemento que nao existe na arvore
    if(arv == NULL || aux == NULL)
        return NULL;
    //Para o caso onde o elemento tem filho da direita, o sucessor e o minimo da subarvore que tem o filho diretio como raiz
    else if(aux->left != NULL)
        return maximum(aux->left);
    else{
        //Nesse caso e usada uma pilha para guardar o caminho ate o elemento e depois achar seu sucessor
        nodestack* pl = NULL;
        while(arv->element != n){
            pl = push(pl, arv);
            if (n < arv->element)
                arv = arv->left;
            else
                arv = arv->right;
        }
        //Buscamos de qual raiz presente na pilha o elemento n é maximo
        p = pop(&pl);
        while(p != NULL && aux == (p->left)){
            aux = p;
            p = pop(&pl);
        }
        free_stack(pl);
        return p;
    }
}

//Função para buscar um intervalo de elementos em uma arvore binaria
void range_query(node *arv, int x, int y){
    if (arv != NULL){
        range_query(arv->left, x, y);
        if(arv->element >= x && arv->element <= y)
            printf("%d ", arv->element);
        range_query(arv->right, x, y);
    }
}

//Função para liberar a memoria alocada pela arvore
void free_tree(node *arv){
    if (arv != NULL){
        free_tree(arv->left);
        free_tree(arv->right);
        free(arv);
    }
}
