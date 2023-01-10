//Aquivo .h contendo a declarações de tipos e funções para implementação de uma tabela hashing 
#ifndef HASH
#define HASH
#define M 5381

//Registo para guardar a tabala hashing
struct data{
    int id[M];   //Indice do acordo com a sequencia de inserção, como começa a partir do 0 tbm será usado como dummy para vazio(-1) e para removido(-2)
    char string[M][251];   //Matriz para receber as cadeias de caracteres
};
typedef struct data data;


//Funções de Manipulação da Tabela Hashing
data* create();
int hash(char *str);
unsigned long djb2(char *str);
data* insert(data* table, int i, char str[251]);
int buscar(char* str, data* table);
void remover(data* table);

#endif