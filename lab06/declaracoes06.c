//Arquivo .c contendo as implementações das funções da lista
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lab06.h"

//Função para inserir um novo nó na cabeça da lista
void insert(node **p, int n){
    node *new;
    new = malloc(sizeof(node));
    //Faz verificação de alocação de memoria
    if (new == 0){
    printf("Alocação Falhou");
    }
    new->next = *p;
    new->element = n;
    new->cont = 0;
    *p = new;
}

//Função para remover nós e retornar a contagem do custo para essa ação
int remov(node **p, int n){
    node *aux, *auxant = NULL;
    int cont=0;
    for(aux = *p; aux != NULL; aux = aux->next){
        cont++;
        //Para encontra o elemento a ser removido
        if(aux->element == n){ 
            //Caso especifico do elemento no inicio da lista
            if(auxant == NULL){
                *p = aux->next;
                free(aux);
                return cont;
            }
            else{
                auxant->next = aux->next;
                free(aux);
                return cont;
            }
        }
    //modifica valores de auxant
    auxant = aux; 
    }
    return 0;
}

//Função para voltar a lista ao seu formato original
node* reset(node **p, int n){
    int i;
    node *aux;
    for(aux = *p; aux != NULL; aux = aux->next)
        free(aux);
    //p = NULL;
    for(i=n; i>=1; i--)
        insert(&aux, i);
    return aux;
}
