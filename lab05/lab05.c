/*Cristiano Sampaio Pinheiro RA:256352
Esse programa deve receber uma matriz triangular inferior de numeros fracionarios com n linhas,
aloca-la dinamicamente, e retorna essa mesma matriz com os valores normalizados juntamente com a 
media dos valores e o desvio padrão.
retornar essa mesma matriz 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Função para calcular a media
double media(int ordem, double **mat){
    int i, j;
    double cont = 0, n = 0;
     for(i=0; i<ordem; i++){
        for(j=0; j<=i; j++){
            cont += mat[i][j];
            n++;
        }
    }
    return cont/n;
}

//Função para calcular o desvio padrao
double desvio_padrao(int ordem, double **mat, double m){
    int i, j;
    double sum, n;
    n = 0;
    sum = 0;
     for(i=0; i<ordem; i++){
        for(j=0; j<=i; j++){
            sum +=  pow(mat[i][j]-m, 2);
            n++;
        }
    }
    return sqrt(sum/n);
}

//Função para substituir os elementos da matriz por seus valores normalizados
void norma(int ordem, double **mat, double m, double dp){
    int i, j;
     for(i=0; i<ordem; i++){
        for(j=0; j<=i; j++){
            mat[i][j] = (mat[i][j]-m)/dp;
        }
    }
}

int main(){
    int i,j, ordem;
    double m, dp;

    //Ler ordem da matriz
    scanf(" %d", &ordem);

    //Aloca memoria para matriz triangular
    double **mat = malloc(ordem*sizeof(double*));
    if(!mat){
        return 0;
    }
    for(i=0; i<ordem; i++){
        mat[i] = malloc((i+1)*sizeof(double));
        if (!mat[i]){
            while (i)
                free(mat[--i]);
            free(mat);
            return 0;
        }
    }

    //ler entradas para matriz
    for(i=0; i<ordem; i++){
        for(j=0; j<=i; j++){
            scanf(" %lf", &mat[i][j]);
        }
    }

    m = media(ordem, mat);
    dp = desvio_padrao(ordem, mat, m);
    norma(ordem, mat, m, dp);
    
    //Imprime a matriz apos a modificação
    for(i=0; i<ordem; i++){
        for(j=0; j<=i; j++){
            printf("%.12lf ", mat[i][j]);
        }
        printf("\n");
    }
    
    //Imprime a media e o desvio padrão
    printf("\n%.12lf %.12lf \n", m, dp);
   
    //libera memoria alocada
    for(i=0; i<ordem; i++)
        free(mat[i]);
    free(mat);

    return 0;
}