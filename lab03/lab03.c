/*
Cristiano Sampaio Pinheiro RA:256352
Esse programa deve a partir de um conjuto de palavras e frases recebidas, verificar qual das frases contem mais 
ocorrencias das palavras chaves e retornala(s) no formato original da leitura

OBS.:Por algum motivo paranormal ao copiar a str1 para a str2 a str1 se embaralhava, tal dificuldade 
foi superada à moda brasileira criando uma str bkp, para ter um backup. Os printf antes e apos a realização da copia foram 
deixados no codigo.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 

//Função para encontrar o maior numero do vetor que guarda a quantidade de repetições em uma determinada frase
int maior(int atd[], int c){
    int i, maior = atd[0];
    for(i = 0; i < c; i++){
        if (atd[i] > maior)
            maior = atd[i];
    }
    return maior;
}

//Função para ler as palavras chaves 
void ler_palavras (char vet[][20] ,int k){
    int i;
    for(i=0; i<k; i++){
        scanf(" %s", vet[i]);
    }   
}

//Função para ler as desculpas/frases
void ler_desculpas(char des[][101], char copia[][101], int e){
    int i;
    for(i=0; i<e; i++){
        scanf(" %[^\n]", des[i]);
    }
}

//Função para procurar as palavras chaves dentro das frases, recebe uma determinada frase e busca as palavra desejadas contando o numero de ocorrencias
int procura(char pal[][20], char copia[101], int k){
    int i, acm=0;
    for(i=0; i<k; i++){
        char *id= strstr(copia, pal[i]);
        while (id!=0){
            acm = acm+1;
            id = strstr(id+1,pal[i]);
        }
    }
    return acm;
}

//Função para imprimir apos cada interação
void imprime(int acm[], char des[][101], int e, int h, char bkp[][101]){
    int m, i;
    m = maior(acm, e);
    printf("Conjunto de desculpas #%d\n", h);
    for(i=0; i<e; i++){
        if(acm[i]==m){
            printf("%s\n",bkp[i]);
        }
    }
    printf("\n");
}

int main(){
    //"k" e "e" recebem as entradas interias, "i" e "j" são usados para percorrer vetores, "h" contabiliza o numero de interações
    int k, e, i, j, h=0;
    while(scanf(" %d %d", &k, &e) != EOF){
    h++;
    //Vetor para guardar quantas palavras chaves foram encontradas em casa frase
    int acm[e];
    //"pal" para guardas as palavras chaves, "des" para guardas as desculpas, "copia" para armazenas as deculpas com todos os caracteres transformados para minusculos, "bkp" foi necessario como mencioando anteriormente
    char pal[k][20], des[e][101], copia[k][101], bkp[e][101];

    ler_palavras(pal, k);
    ler_desculpas(des, copia, e);
    //Realiza o backup das frases lidas
    for(i=0; i<e; i++)
        strcpy (bkp[i], des[i]);

    //for(i=0; i<e; i++)
    //   printf("pré copia  %s\n", des[i]);
    
    //Copia e transfomar os caracteres em minusculos do vetor "des" para o vetor "copia"
    for(i=0; i<e; i++){
        for(j=0;j < 101; j++){
            if( 'A' <= des[i][j] && des[i][j] <= 'Z')
                copia[i][j] =(char) des[i][j]+32;
            else
                copia[i][j] =(char)des[i][j];
        }
    }

    //for(i=0; i<e; i++)
        //printf("pós copia %s\n", des[i]);
    
    //Passas as frases para que a busca seja realizada
    for(i=0;i<e;i++){
        acm[i] = procura(pal,copia[i], k);
    }
    imprime(acm, des, e, h, bkp);
    }
return 0;
}