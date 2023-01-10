#include <stdio.h>
#include <stdlib.h>
#include "lab12.h"

//Função para trocar dois valores de um vetor
void swap(int *vet, int A, int B){
    int k = vet[A];
    vet[A] = vet[B];
    vet[B] = k;
}

//Função para crear uma heap
void create_heap(int *vet, int N){
    int i;
    for(i=1; i<N; i++){
        //Sobe com o novo no ate coloca-lo na posição correta
        while(i>=0 && vet[i]>vet[dad(i)]){
            swap(vet, i, dad(i));
            i = dad(i);
        }
    }
}

//Remove o máximo(raiz) de um heap
int remove_max(int *vet, int N){
    if(N <= 0)
        return vet[0];
    int i, max;
    swap(vet, 0, N-1);
    N--;
    i = 0;
    //Desce com a raiz ate encontrar sua posição válida
    while(N){
        max = i;
        if(sonl(i)<N){
            max = sonl(i);
            if(sonr(i)<N && vet[sonr(i)]>vet[sonl(i)])
                max = sonr(i);
        }
        if(vet[max] > vet[i]){
            swap(vet, i, max);
            i = max;
        }
        else{
            return vet[N];
        }
    }
    return vet[N];
}

//Função para realizar a ordenação
void HeapSort(int *vet, int N){
    create_heap(vet, N);
    int i;
    for(i=N; i>0; i--){
        remove_max(vet, N);
        N--;
    }
}