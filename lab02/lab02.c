/*
Cristiano Sampaio Pinheiro RA:256352
Esse programa deve a partir de uma entrada contendo o horario de chagada e o tempo de atendimento a clientes de uma loja 
calcular qual o tempo de espera medio e quantos clientes tiveram de esperar mais de 10 minutos
*/
#include <stdio.h>
//Função para encontra qual caixa ficará livre primeiro(Encontrar qual dos elementos do vetor é menor)
int menor(int atd[], int c){
    int i, menor = atd[0], ind=0;
    for(i = 0; i < c; i++){
        if (atd[i] < menor){
            menor=atd[i];
            ind = i;
    }}
    return ind;
}
//Função para calcular e acumular o tempo de espera, além de contar quantos clientes esperaram por mais de 10 minutos
double espera(int vet[][2], int n, int atd[],int c){
     int i, e = 0, acm = 0, cont = 0, m;
     for (i=0; i<(n); i++){
        m = menor(atd, c);          //Verifica qual caixa ficará desoculpado primeiro
        e = atd[m] - vet[i][0];     //Calcula o tempo de espera
        if(e<0)                     //Se e menor que 0 indica que não houve tempo de espera
            e = 0;
        acm += e;                   //Acumula o tempo de espera para fazer a media
        if (e>10)                   //Verifica quantos clientes ficaram esperando por mais de 10 minutos
            cont++;     
        atd[m] = vet[i][0] + vet[i][1] + e;     //Determina quando o caixa fica livre novamente
    }
    atd[0] = cont;      //Aproveita o vetor que contabiliza o tempo de serviço dos caixas para guardar quantos clientes esperaram por mais de 10 minutos
    return acm;
}
int main(){
    int c ,i, j, n, d;
    //Realiza a leitura da primeira linha que contem parametros necessariso para a inicialização da matriz
    scanf("%d %d", &c ,&n);
    int vet[n][2], atd[c];  //vet para a entrada, atc para o tempo em que cada caixa fica oculpado
    //Realiza a leitura dos horarios de chegada e tempo de atendimento para cada cliente
    for(i = 0 ;i < n; i++){
        for(j = 0; j < 2; j++)
            scanf("%d", &vet[i][j]);
    }
    //Inicialmente todos os caixas estão disponiveis
    for(i = 0 ;i < c; i++){
        atd[i] = 0;
    }
    d = espera(vet, n, atd, c);
    printf("Espera media para %d clientes: %.1f minutos\n", n, d/(double)n);
    printf("Numero de clientes que esperaram mais que 10 minutos: %d\n", atd[0]);
    return 0;
}