/*
Cristiano Sampaio Pinheiro RA: 256352
Espe programa deve implementar uma lista auto-organizavel, a qual se modifica de acordo com os
elementos acessados seguindo 3 estrategias de reorganização: Move-to-front, Transpose e Count. 
para cada estrategia e contado seu custo e os 3 custo sao impressos ao fim da execução
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "lab06.h"

//Função para o caso Move-to-front
int acss_MTF(node **p, int req){
    int ct;
    //Remove o elemento da posição atual e retorna o custo
    ct = remov(p, req);
    //Insere o elemento novamente no inicio da lista
    insert(p, req);
    return ct;
}

//Função para o caso Transpose
int acss_TR(node **p, int req){
    int cont=0;
    node *aux, *auxant = NULL, *auxantant = NULL;
    //Percorre a lista procurando o elemento requisitado
    for(aux = *p; aux != NULL; aux = aux->next){
        cont++;
        if(aux->element == req){
            //Caso especifico do elemento ja estar no inicio da lista
            if(auxant == NULL){
                *p = aux;
                return cont;
            }
            //Caso especifico do elemento ser o segundo da lista
            else if(auxantant == NULL){
                auxant->next = aux->next;
                aux->next = auxant;
                *p = aux;
                return cont;
            }
            else{
                auxant->next = aux->next;
                aux->next = auxantant->next;
                auxantant->next = aux;
                return cont;
            }
        }
    //modifica valores de auxant e auxantant
    if(cont>1)
        auxantant = auxant;
    auxant = aux;
    }
    return 0;
}

//Fução para o caso Count
int acss_C(node **p, int req){
    int cont=0;
    node *aux, *auxant = NULL, *q, *k = NULL;
    //Percorre a lista procurando o elemento requisitado
    for(aux = *p; aux != NULL; aux = aux->next){
        cont++;
        if(aux->element == req){
            aux->cont +=1;
            //Caso especifico do elemento ja estar na primeira posição
            if(auxant == NULL){
                return cont;
            }
            else{       //Apos encontrar o elemento procura qual deve ser sua nova posição
            for(q = *p; q != NULL; q = q->next){
                if((q->cont) <= (aux->cont)){
                    //Caso especifico em que o elemento deve assumir a primeira posição da fila
                    if(k == NULL){
                        auxant->next = aux->next;
                        aux->next = q;
                        *p = aux;
                        return cont;
                    }
                    //Caso especifico do elemento ja estar na posição correta
                    else if((q->element) == (aux->element)){
                        return cont;
                    }
                    else{
                        auxant->next = aux->next;
                        aux->next = q;
                        k->next = aux;
                    return cont;
                    }
                }
                //Modifica o valor de k, usado como anterior quando espa se procurando a nova posição do elemento
                k = q;
                }
            }
        }
    //Modificar o valor de auxant
    auxant = aux; 
    }
    return 0;
}

int main(){
    int i, chaves, r, mtf, tr, c;
    mtf = 0;
    tr = 0;
    c = 0;
    //Cria lista e aponta para NULL indicando que ainda nao ha elementos
    node *p, *aux;
    p = NULL;

    //Realiza a leitura dos dados 
    scanf(" %d %d", &chaves, &r);
    int req[r];
    for(i=0; i<r; i++)
        scanf(" %d", &req[i]);

    //insere elementos de 1 a N na lista
    for(i=chaves; i>=1; i--)
        insert(&p, i);
    
    //Passa valores para MTF
    for (i=0; i<r; i++)
        mtf += acss_MTF(&p, req[i]);

    //Reformula a lista para seu estado inicial
    p = (node*) reset(&p, chaves);

    //Passa valores para TR
    for (i=0; i<r; i++)
        tr += acss_TR(&p, req[i]);
        
    //Reformula a lista para seu estado inicial
    p = (node*) reset(&p, chaves);

    //Passa valores para C
    for(i=0; i<r; i++)
        c += acss_C(&p, req[i]);
    
    //Libera a memoria alocada
    while(p != NULL){
        aux = p;
        p = p->next;
        free(aux);
    }

    printf("%d %d %d\n", mtf, tr, c);
    
    return 0;
}
