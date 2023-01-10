#include <stdio.h>
#include <stdlib.h>
#include "lab12.h"

int main(){
    int N, i;
    scanf(" %d", &N);
    int vet[N];
    //Ler valores a serem ordenados
    for(i=0; i<N; i++)
        scanf(" %d", &vet[i]);
    HeapSort(vet, N);
    //Imprime valores já ordenados
    if(N!=0){
        for(i=0; i<N; i++)
            printf("%d ", vet[i]);
        printf("\n");
    }
    return 0;
}
