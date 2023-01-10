#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab11.h"

//Função para cria a tabela de hashing
data* create(){
  data* table = malloc(sizeof(data));
  //Caso a alocação falhe
  if(!table)
    return NULL;
  return table;
}

//Função para transformar uma string em um inteiro(Fornecida pelo professor e levemente modificada)
unsigned long djb2(char *str){
  unsigned long hash = 5381;
  int c;
  while((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 32 + hash + c
  return hash;
}

//Função para calcular o hash de um dado elemento, usando o metodo da divisão
int hash(char *str){
  unsigned long num = djb2(str);
  int x = num%M;
  return x;
}

//Função para inserir um novo elemento na tabela
data* insert(data* table, int i, char str[251]){
  int h = hash(str);
  //Caso em que não há colisão
  if(table->id[h] < 0){
    strcpy(table->string[h], str);
    table->id[h] = i; 
    return table;
  }
  //Caso em que há colisão, realiza o encadeamento linear(+1) na propria tabela
  else{
    //Define a nova posição
    while (table->id[h]>=0){
      h++;
      if(h>M)
        h=0;
    }
    table->id[h] = i;
    strcpy(table->string[h], str);
    return table;
  }
}

//Função para comparar duas strings, strcmp não funcionou :(
int comp(char str1[251], char str2[251]){
  //usa a quantidade de elementos a string recebida como parametro de parada da comparação
  int i=0, l = strlen(str1);
  while(i<l){
    if(str1[i]==str2[i])
      i++;
    else
      return 0;
  }
  return 1;
}

//Função para buscar um elemento na tabela
int buscar(char *str, data* table){
  int h = hash(str);
  if((table->id[h])>=0 && comp(str, table->string[h])){  
    return h;
  }
  else{
    //Caso em que há colisão
    while(table->id[h]!=-1){   
      h++;
      if(h>M)
        h=0;
      if((table->id[h])>=0 && comp(str, table->string[h])){
        return h;
      }
    }
  }
  //Caso apos comparar as colisões não encontre o elemento
  return -1;
}

//Função para remover um elemento da tabela 
void remover(data* table){
  char str[251];
  scanf(" %s", str);
  int place = buscar(str, table);
  if(place >= 0)
  //-2 no indice indica que o elemento foi removido
  table->id[place] = -2;
}