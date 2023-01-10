#ifndef heapsort
#define heapsort

//Definições para facilitar a escrita e leitura do codigo
#define dad(i) ((i-1)/2)
#define sonl(i) (2*i+1)
#define sonr(i) (2*i+2)

//Funções para o HeapSort
void create_heap(int *vet, int N);
void swap(int *vet, int A, int B);
int remove_max(int *vet, int N);
void max_heap(int *vet, int i, int N);
void HeapSort(int *vet, int N);

#endif
