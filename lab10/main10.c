/*
"As arvores somos nós e jesus e o jardineiro"
Cristiano Sampaio Pinheiro RA: 256352
Espe programa deve criar uma arvore binaria de busca e permitir operação, como:
inserir elementos, buscar por elementos, remover um elemento, imprimir em ordem, 
pre-ordem, pos-ordem, largura, encontra sucessor, encontrar predecessor, imprimir um intervalo de valores.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab10.h"

//Função de menu para gerenciar as entradas e ações do programa
void menu(){
    int value, x, y;
    char comando[20];
    node *aux, *arv = create_tree();
    //Recebe entradas e direciona comandos
    while(scanf(" %s", comando) && strcmp(comando, "terminar")){
        //Caso para inserir um novo elemento
        if (!(strcmp(comando, "inserir"))){
            scanf(" %d", &value);
            //Verifica se o elemento já não foi inserido anteriormente antes de inserir
            if(!search(arv, value))
                arv = insert_tree(arv, value);
        }
        //Caso para buscar um elemento
        else if (!(strcmp(comando, "buscar"))){
            scanf(" %d", &value);
            aux = search(arv, value);
            aux != NULL? printf("%d pertence\n", value): printf("%d nao pertence\n", value);
        }
        //Caso para imprimir em pos-ordem
        else if (!(strcmp(comando, "pos-ordem"))){
            if(arv != NULL){
                pos_ordem(arv);
                printf("\n");
            }
            else
                printf("vazia\n");
        }
        //Caso para imprimir em em ordem
        else if (!(strcmp(comando, "em-ordem"))){
            if(arv != NULL){
                em_ordem(arv);
                printf("\n");
            }
            else
                printf("vazia\n");
        }
        //Caso para imprimir em pre-ordem
        else if (!(strcmp(comando, "pre-ordem"))){
            if(arv != NULL){
                pre_ordem(arv);
                printf("\n");
            }
            else
                printf("vazia\n");
        }
        //Caso para imprimir em largura
        else if (!(strcmp(comando, "largura"))){
            if(arv != NULL){
                largura(arv);
                printf("\n");
            }
            else
                printf("vazia\n");
        }
        //Caso para a remoção de um elemento
        else if (!(strcmp(comando, "remover"))){
            scanf(" %d", &value);
            if(arv != NULL)
                arv = remove_tree(arv, value);
        }
        //Caso para buscar o minimo da arvore
        else if (!(strcmp(comando, "minimo"))){
            aux = minimum(arv);
            if(aux != NULL)
                printf("%d\n", aux->element);
            else
                printf("vazia\n");
        }
        //Caso para buscar o maximo da arvore
        else if (!(strcmp(comando, "maximo"))){
            aux = maximum(arv);
            if(aux != NULL)
                printf("%d\n", aux->element);
            else
                printf("vazia\n");
        }
        //Caso para encontra o sucessor de um determinado elemento da arvore
        else if (!(strcmp(comando, "sucessor"))){
            scanf(" %d", &value);
            if(arv!=NULL){
                aux = successor(arv, value);
                aux != NULL? printf("%d\n", aux->element): printf("nao ha\n");
                }
            else
                printf("vazia\n");
        }
        //Caso para encontra o predecessor de um determinado elemento da arvore
        else if (!(strcmp(comando, "predecessor"))){
            scanf(" %d", &value);
            if(arv!=NULL){
                aux = predecessor(arv, value);
                aux != NULL? printf("%d\n", aux->element): printf("nao ha\n");
            }
            else
                printf("vazia\n");
        }
        //Caso para buscar um intervalo de valores na arvore
        else if (!(strcmp(comando, "buscar-intervalo"))){
            scanf(" %d %d", &x, &y);
            //Verifica caso a arvore esteja desmatada ou o intervalo não pertença
            if (arv != NULL && x <= maximum(arv)->element && y >= minimum(arv)->element){
                range_query(arv, x, y);
                printf("\n");
            }
            else 
                printf("nenhuma\n");
        }
    }
    //Libera memoria alocada para arvore
    free_tree(arv);
}

int main(){
    menu();
    return 0;
}