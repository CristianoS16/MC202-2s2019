/*Cristiano Sampaio Pinheiro RA:256352
Esse programa deve, a partir de uma mariz mxn dada, encontra qual a maior soma possiveis dos elementos de uma submatriz rxs contida na matriz principal*/
#include <stdio.h>

int main() {
    int i, j, r, s, acm, cont, vf[4];
    //Realiza a leitura da primeira linha que contem os parametros das matrizes 
    for (cont = 0; cont<4; cont++){
        scanf("%d", &vf[cont]);
    }

    int matriz[vf[0]][vf[1]];
    cont = 0;
    acm = 0;
    //Realiza a leitura da matriz principal
    for (i = 0; i<(vf[0]); i++){
        for (j = 0; j<(vf[1]); j++){
        scanf("%d", &matriz[i][j]);
    }}

    
    //2 fors para percorrer a matriz principal e e fors para percorrer a matriz interna realizando a soma dos elementos
     for (i = 0; i<=(vf[0]-vf[2]); i++){
        for (j = 0; j<=(vf[1]-vf[3]); j++){      //percorre a matriz mais externa 
            for (r = i; r< (i + vf[2]); r++){
                for (s = j; s< (j + vf[3]); s++){    //percorre a matriz interna realizando a soma
                    cont = cont + matriz[r][s];
                    }
                }
            //Compara a soma atual com a maior obtida anteriormente
            if (cont > acm){
                acm = cont;
                }
            cont = 0;
        }
     }
//Imprime a maior soma encontrada
printf("%d\n", acm);
return 0;
}

