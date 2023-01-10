/*
Cristiano Sampaio Pinheiro RA:256352
Esse programa deve criar uma agenda de contatos simples, permitindo adicionar novos contatos, remover, fazer buscas e imprimir os contatos presentes
obs.: a saida do teste 06 esta igual a esperada, por comparação usando diff no terminal. . .
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Registro do tipo contato para guardar as informações de cada contato
    typedef struct {
        char Nome[51];
        char Endereco[101];
        char Telefone[13];
        char Niver[11];
    } contatos;

//Função para inserir novos contatos a agenda
    contatos insercao(){
        contatos novo;
        scanf(" %[^\n]", novo.Nome);
        scanf(" %[^\n]", novo.Endereco);
        scanf(" %s", novo.Telefone);
        scanf(" %s", novo.Niver);
        printf("Contato para %s inserido.\n", novo.Nome);
        return novo;
    }

//Função para imprimir todos os contatos da agenda
    void impressao(contatos agenda[1000], int i, int cont){
        //i=0 indica impressão de toda a agenda
        if(i<0){
            i = 0;
            printf("Listagem:\n");
            if (cont==0)
                printf("Nenhum contato.\n");
            for(i=0; i<cont; i++)
                printf("(%d) %s\t%s\t%s\t%s\n",i+1,agenda[i].Nome, agenda[i].Endereco, agenda[i].Telefone, agenda[i].Niver);
            }
        //Indica impressão de dados de um contato em especifico
        else{
            printf("(%d) %s\t%s\t%s\t%s\n",i+1, agenda[i].Nome, agenda[i].Endereco, agenda[i].Telefone, agenda[i].Niver);
        }
    }

//Função para realizar uma busca dentro da agenda
    void busca(contatos agenda[1000], char busca[51], int cont){
        printf("Resultado da busca:\n");
        int i, localizado = 1;
        for(i=0; i<cont; i++){
            if(strstr((agenda[i].Nome), busca)!= 0){
                localizado = 0;                
                impressao(agenda, i, cont);
                printf("\n");
            }
        }
        if (localizado){
            printf("Nenhum contato.\n");
            printf("\n");
        }
    }

//Função para remover um contato da agenda
    int remocao(contatos agenda[1000], char remov[51], int cont){
        int i = 0, j, n = 0;
        for(i=0; i < cont; i++){
            if(strcmp(remov, (agenda[i].Nome))==0){
                for(j=i; j< cont; j++){
                    agenda[j] = agenda[j+1];
                }
            n++;
            }
        }
        cont = cont - n;
        printf("Contatos de %s removidos: %d.\n", remov, n);
        return cont;
    }

//Função menu, permite a interação do usuario com o programa
    void menu(int cont){
        contatos agenda[1000];
        char read , remov[51], buscapor[51];
        while(scanf(" %c", &read) && read != 'f'){
            switch(read){
                case 'i':
                    agenda[cont] = insercao(agenda);
                    cont++;
                    printf("\n");
                break;
                case 'r':
                    scanf(" %[^\n]", remov);
                    cont = remocao(agenda, remov, cont);
                    printf("\n");
                break;
                case 'b':
                    scanf(" %[^\n]", buscapor);
                    busca(agenda, buscapor, cont);
                break;
                case 'p':
                    impressao(agenda, -1, cont);
                    printf("\n");
                break;
                }
            }
        }

int main (){
    int cont = 0;
    menu(cont);
    return 0;
}
