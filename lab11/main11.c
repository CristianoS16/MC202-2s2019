/*
Cristiano Sampaio Pinheiro RA: 256352
Esse programa deve gerar uma tabela de hashing e implementar operações simples como inserção, busca e remoção
Aqui estou usando uma tabela de tamanho 5381, um numero primo que condiz o metodo da divisão aplicado, as colisões
são tratatas por sondagem linear na propria tabela
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab11.h"

//Função de menu para gerenciar as entradas e ações do programa
void menu(){
    data* table = create();
    int i, h;
    char a, str[251];
    //Inicia todas as posições do indice com o dummy para vazio(-1), (-2) é usado para indicar remoção
    for(i=0; i<M; i++) 
        table->id[i] = -1;
    i = 0;//Usado para registrar os indices
    while (scanf(" %c", &a) && a != 'f'){
        //Caso para inserir um novo elemento na tabela
        if(a == 'i'){
            //So realiza a inserção se a busca por str na tabela falhar
            scanf(" %s", str);
            if (buscar(str, table)<0){
                table = insert(table, i, str); 
                i++;
            }            
        }
        //Caso para buscar um elemento na tabela
        else if(a == 'b'){
            scanf(" %s", str);
            h = buscar(str, table);
            h>=0? printf("%s encontrada, id %d\n", str, table->id[h]): printf("%s nao encontrada\n", str);
        }
        //Caso para remover um elemento da tabela
        else if(a == 'r'){
            remover(table);
        }
    }
    //Libera a memoria alocada para a tabela
    free(table);
}

int main(){
    menu();
    return 0;
}