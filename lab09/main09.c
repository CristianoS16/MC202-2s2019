/*
"As arvores somos nós e jusus e o jardineiro"
Cristiano Sampaio Pinheiro RA: 256352
Espe programa deve criar uma arvore binaria de busca e permitir operação simples na mesma, como:
inserir elementos, buscar por elementos, imprimir em ordem, pre-ordem, pos-ordem e largura.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab09.h"

//Função de menu para gerenciar as entradas e ações do programa
void menu(){
    int value;
    char comando[10];
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
    }
    //Libera memoria alocada para arvore
    free_tree(arv);
}

int main(){
    menu();
    return 0;
}