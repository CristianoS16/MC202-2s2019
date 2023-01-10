/*
Cristiano Sampaio Pinheiro
Esse programa deve realizar ações simples em um vetor dinamico como: Adicionar ao inicio, Adiciona ao fim, Remover do inicio, Remover do fim,
Imprimir o primeiro, Imprimir o ultimo e verificar se a lista possui algum elemento.

OBS.: O Programa roda corretamente na minha maquina mas ao envialo ele apresenta erro em realocc ou no free, tais erros nao se manifestaram em minha maquina e por isso nao 
foi possivel sua correção, ao final do arquivo esta presente as saidas para os testes abertos resultados desse mesmo programa rodando no valgrind
ps. a logica me parece estar correta . . .
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Registro para guardar dados do vetor
typedef struct{
    int inicio;
    int fim;
    int tamanho;
    int numelementos;
} ddvetor;

//Função para zerar todos os valores do registro de informações do vetor
void resert(ddvetor *info){
    info->tamanho=0;
    info->numelementos=0;
    info->inicio=0;
    info->fim=0;
}

//Função para verificar se o vetor dinamico possui algum elemento
int is_empty(ddvetor *info){
    if(!(info->tamanho)){
        return 1;
    }
    return 0;
}

//Função para copiar elementos de um vetor
int* copia(int*p, int*h, ddvetor *info){
    int i = 0, j = 0, cont = 0;
    i = info->inicio;
    if (info->inicio == info->fim){
        h[j] = p[i];
    }
    else if (info->numelementos == 2){
        h[0] = p[info->inicio];
        h[1] = p[info->fim];
    }
    else {
        while(cont != info->numelementos){
            h[j] = p[i];
            cont++;
            i++;
            j++;
            if(i > ((info->tamanho)-1))
                i=0;
        }
    }
    return h;
}

//Função para inserir elementos no incio do vetor dinamico
int* insert_first(int *p, ddvetor *info){
    int* h=NULL;
    //Vetor vazio, então é criado
    if(info->tamanho == 0){
        p = (int*) malloc(sizeof(int));
        //Verifica se a alocação foi bem sucedida
        if(p==NULL){
            printf("Alocação falhou");
            exit(1);
        }
        //Ler valor e reajusta informações sobre o vetor
        scanf(" %d", p);
        info->tamanho++;
        info->numelementos++;
        return p;
    }
    //Caso o vetor ja possua elementos
    else{
        //Verifica se sera necessario duplicar
        if(info->tamanho == info->numelementos){
            h = (int*) malloc((2*(info->tamanho))*sizeof(int));
            if (h==NULL){
                printf("Alocação falhou");
                exit(1);
            }
        h = copia(p,h,info);
        //Libera memoria e ajusta informaçõs do vetor
        //free(p);
        info->inicio = 0;
        info->fim = (info->tamanho)-1;
        info->tamanho = 2*(info->tamanho); 
        //p = realloc(p,info->tamanho*sizeof(int));
        free(p);
        p = (int*) malloc((info->tamanho)*sizeof(int));
        p = copia(h,p,info);
        //p = h;
        free(h);
        }
    }
    //Verifica condições de inicio para adicionar o novo elemento
    if(info->inicio == 0)
        info->inicio = (info->tamanho)-1;
    else{
        info->inicio = (info->inicio)-1;
    }
    //Ler o elemento, ajusta numero de elementos e retorna o vetor
    scanf(" %d", &p[(info->inicio)]);
    info->numelementos++;
    return p;
}

//função para inserir elementos no final do vetor dinamico
int* insert_last(int *p, ddvetor *info){
    int* h=NULL;
    //Vetor vazio, entao é criado
    if(info->tamanho == 0){
        p = (int*) malloc(1*sizeof(int));
        //Verifica se a alocação foi bem sucedida
        if(p==NULL){
            printf("Alocação falhou");
            exit(1);
        }
        //Ler valor e reajusta informações do vetor
        scanf(" %d", p);
        info->tamanho++;
        info->numelementos++;
        return p;
    }
        //Caso o vetor ja possua elementos
    else{
        //Verifica se sera necessario duplicar
        if(info->tamanho == info->numelementos){
            h = (int*) malloc((2*info->tamanho)*sizeof(int));
            if (h==NULL){
                printf("Alocação falhou\n");
                exit(1);
            }
            h = copia(p,h,info);
        //Libera memoria e ajusta informações do vetor
        info->inicio = 0;
        info->fim = (info->tamanho);//-1;
        info->tamanho = 2*(info->tamanho);
        scanf(" %d", &h[(info->fim)]);
        info->numelementos++;
        //p = realloc(p, info->tamanho*sizeof(int));
        free(p);
        p = (int*) malloc((info->tamanho)*sizeof(int));
        //p = h;
        p = copia(h,p,info);
        free(h);
        return p;
        }
    }
    //Verifica condições do fim para adicionar o novo elemento
    if(info->fim == (info->tamanho-1))
        info->fim = 0;
    else{
        info->fim = (info->fim)+1;
    }
    //Ler o elemento, ajusta numero de elemento e retorna o vetor
    scanf(" %d", &p[(info->fim)]);
    info->numelementos++;
    return p;
}

//Função para remover o primeiro elemento do vetor
int* remove_first(int *p, ddvetor *info){
    int* h=NULL;
    //Vetor vazio nao tem o que remover, retorna o vetor
    if((info->tamanho) == 0)
        return p;
    //Vetor unitario, libera memoria e retorna o vetor
    else if(info->inicio == info->fim){
        free(p);
        resert(info);
        return p;
    }
    //Caso especial do inicio na primeira possição, contorna o vetor
    else if(info->inicio == ((info->tamanho)-1))
        info->inicio = 0;
    //Caso geral, desloca inicio uma posição a frente
    else{
        info->inicio = (info->inicio)+1;
    }
    info->numelementos--;
    //Apos remover verifica se precisa reduzir o vetor
    if((info->tamanho/4) == info->numelementos){
        h = malloc((info->numelementos)*sizeof(int));
        //Verifica se a alocação foi bem sucedida
        if (h==NULL){
            printf("Alocação falhou\n");
            exit(1);
        }
        h = copia(p,h,info);
        //Libera memoria, ajusta informações e retorna vetor 
        info->inicio = 0; 
        info->tamanho = info->numelementos;
        info->fim = ((info->tamanho)-1);
        free(p);
        p = (int*) malloc((info->tamanho)*sizeof(int));
        //p = realloc(p, info->tamanho*sizeof(int));
        if (p==NULL){
            printf("Alocação falhou\n");
            exit(1);
            }
        p = copia(h,p,info);
        //p = h
        free(h);
        return p;  
        }
        return p;
}

//Função para remover o ultimo elemento do vetor
int* remove_last(int *p, ddvetor *info){
    int *h=NULL;
    //Vetor vazio nao tem o que remover, retorna o vetor
    if((info->tamanho) == 0)
        return p;
    //Vetor unitario, libera memoria e retorna o vetor
    else if(info->inicio == info->fim){
        free(p);
        resert(info);
        return p;
    }
    //Caso especial do fim na primeira possição, contorna o vetor
    else if(info->fim == 0)
        info->fim = (info->tamanho)-1;
    //Caso geral, desloca fim uma posição para frente
    else{
        info->fim = (info->fim)-1;
    }
    info->numelementos--;    
    //Apos remover verifica se precisa reduzir o vetor
    if((info->tamanho/4) == info->numelementos){
        h = malloc((info->numelementos)*sizeof(int));
        if (h==NULL){
            printf("Alocação falhou\n");
            exit(1);
        }
        h = copia(p,h,info);        
        //Libera memoria, ajusta informações e retorna vetor 
        info->inicio = 0;
        info->tamanho = info->numelementos;
        info->fim = (info->tamanho)-1;
        //p = realloc(p, info->tamanho*sizeof(int));
        free(p);
        p = (int*) malloc((info->tamanho)*sizeof(int));
        p = copia(h,p,info);   
        //p = h;
        free(h);
        return p;
        }
    return p;
}

//Função para imprimir o primeiro elemento 
void print_first(int* p, ddvetor *info){
    if(info->tamanho)
        printf("%d\n", p[info->inicio]);    
}

//Função para imprimir o ultimo elemento
void print_last(int* p, ddvetor *info){
    if(info->tamanho)
        printf("%d\n", p[info->fim]);
}

//Função para imprimir todos os elementos da lista
void imprime(int *p, ddvetor *info){
    int i = info->inicio, cont=0;
    if(info->inicio == info->fim)
        printf("inicico: %d\n", p[info->inicio]);
    else{
        while(cont!=info->numelementos){
            printf("%d\n", p[i]);
            i++;
            if(i > ((info->tamanho)-1)){
                i=0;
            }
            cont++;
        }
    }
}

//Função de menu para gerenciar as entradas e ações do programa
void menu(){
    //Inicia apontador para o vetor, string para guarda comandos recebidos e registro de informações do vetor
    char comando[12];
    int *p = NULL;
    ddvetor info;
    resert(&info);
    while(scanf(" %s", comando) && strcmp(comando, "exit")){
        if (!(strcmp(comando, "insert-first"))){
            p = insert_first(p, &info);
        }
        else if (!(strcmp(comando, "remove-first"))){
            p = remove_first(p, &info);
        }
        else if (!(strcmp(comando, "print-first"))){
            print_first(p, &info);
        }
        else if (!(strcmp(comando, "insert-last"))){
            p = insert_last(p, &info);
        }
        else if (!(strcmp(comando, "remove-last"))){
            p = remove_last(p, &info);
        }
        else if (!(strcmp(comando, "print-last"))){
            print_last(p, &info);
        }
        else if (!(strcmp(comando, "is-empty"))){
            if(is_empty(&info))
                printf("yes\n");
            else
                printf("no\n");
        }
    }
    //Verifica se o vetor esta vazio, e o libera se ainda possuir elementos
    if(!info.tamanho == 0){
        free(p);
        }
}

int main(){
    menu();
    return 0;
}

/*
///////////////////////////Testes no Valgrind\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Saidas do valgrind para o is testes abertos usando o programa anterior\\

//////////////////////01-enunciado.in\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

cristiano@Cristiano:~/mc202$ gcc -Wall -g lab07.c -o testetes
cristiano@Cristiano:~/mc202$ valgrind --leak-check=full ./testetes < 01-enunciado.in 
==3968== Memcheck, a memory error detector
==3968== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3968== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3968== Command: ./ultimomsm
==3968== 
yes
no
13
101
51
51
==3968== 
==3968== HEAP SUMMARY:
==3968==     in use at exit: 0 bytes in 0 blocks
==3968==   total heap usage: 9 allocs, 9 frees, 5,180 bytes allocated
==3968== 
==3968== All heap blocks were freed -- no leaks are possible
==3968== 
==3968== For counts of detected and suppressed errors, rerun with: -v
==3968== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


//////////////////////02-small.in\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

cristiano@Cristiano:~/mc202$ valgrind --leak-check=full ./testetes < 02-small.in 
==3978== Memcheck, a memory error detector
==3978== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3978== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3978== Command: ./ultimomsm
==3978== 
-5
-5
4
4
-3
-3
2
2
-1
-1
yes
==3978== 
==3978== HEAP SUMMARY:
==3978==     in use at exit: 0 bytes in 0 blocks
==3978==   total heap usage: 15 allocs, 15 frees, 5,404 bytes allocated
==3978== 
==3978== All heap blocks were freed -- no leaks are possible
==3978== 
==3978== For counts of detected and suppressed errors, rerun with: -v
==3978== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


//////////////////////03-epsilon.in \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

cristiano@Cristiano:~/mc202$ valgrind --leak-check=full ./testetes < 03-epsilon.in 
==3983== Memcheck, a memory error detector
==3983== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3983== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3983== Command: ./ultimomsm
==3983== 
yes
yes
yes
yes
==3983== 
==3983== HEAP SUMMARY:
==3983==     in use at exit: 0 bytes in 0 blocks
==3983==   total heap usage: 2 allocs, 2 frees, 5,120 bytes allocated
==3983== 
==3983== All heap blocks were freed -- no leaks are possible
==3983== 
==3983== For counts of detected and suppressed errors, rerun with: -v
==3983== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


//////////////////////06-head-tail.in \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

cristiano@Cristiano:~/mc202$ valgrind --leak-check=full ./testetes < 06-head-tail.in 
==3997== Memcheck, a memory error detector
==3997== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3997== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3997== Command: ./testetes
==3997== 
no
10
10
no
9
9
no
8
8
no
7
7
no
6
6
no
5
5
no
4
4
no
3
3
no
2
2
no
1
1
yes
yes
yes
yes
yes
yes
yes
==3997== 
==3997== HEAP SUMMARY:
==3997==     in use at exit: 0 bytes in 0 blocks
==3997==   total heap usage: 17 allocs, 17 frees, 5,700 bytes allocated
==3997== 
==3997== All heap blocks were freed -- no leaks are possible
==3997== 
==3997== For counts of detected and suppressed errors, rerun with: -v
==3997== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/