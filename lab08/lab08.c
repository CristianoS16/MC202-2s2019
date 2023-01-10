/*
Cristiano Sampaio Pinheiro RA: 256352
Espe programa deve implementar uma lista dinamica que permita a inserção de um elemento
em uma determinada posição, a inversão dos elementos entre duas posições dadas(realizando
 um numero contante de operações) e a impressão dessa lista.
*/
#include <stdio.h>
#include <stdlib.h>

//Registro para os nós da lista
struct node{ 
    double element;
    struct node *B;
    struct node *A;
};
typedef struct node node;

//Registo para guardar a lista, obs: possui sentinelas na cabeça e no rabo
struct list{
    node *head;
    node *tail;
    int size;
};
typedef struct list list;

//Função para cria uma lista
list* create_list(){
    //Aloca memoria para lista
    list *ls = malloc(sizeof(list));
    //Caso a alocação falhe:
    if(!ls)
        return NULL;
    //Aloca memoria para a sentinela da cabeça
    node* first_node = malloc(sizeof(node));
    //Caso a alocação falhe:
    if(!first_node){
        free(ls);
        return NULL;
    }
    //Aloca memoria para sentinela do rabo
    node* second_node = malloc(sizeof(node));
    //Caso a alocação falhe:
    if(!second_node){
        free(ls);
        free(first_node);
        return NULL;
    }
    //Ajusta parametros da lista
    ls->head = first_node;
    ls->tail = second_node;
    ls->size = 0;
    //Ajusta apontadores das sentinelas
    first_node->B = second_node;
    second_node->A = first_node;
    first_node->A = NULL;
    second_node->B = NULL;
    return ls;
}

//Função para buscar uma posição n na lista
node* search(list* ls, int n){
    //Caso seja solicitada uma posição antes do inicio e delvido o sentinela
    if(n == -1)
        return ls->head;
    int cont = 0;
    node *auxaux = ls->head;
    node *aux;
    //Verifica como deve iniciar o percurso da lista
    if (ls->head->A == NULL)
        aux = ls->head->B;
    else{
        aux = ls->head->A;
    }
    //Percorre a lista implementando a contadora ate chegar a posição solicitada
    while(cont <= ls->size){
        if(cont == n)
            return aux;
        //Verifica qual deve ser o proximo nó:
        else if(aux->B == auxaux){
            auxaux = aux;
            aux = aux->A;
        }
        else if(aux->A == auxaux){
            auxaux = aux;
            aux = aux->B;
            }
        cont++;
    }
    return aux;
}

//Função para inserir um novo nó em uma determinada posição
int insert(list* ls, int position, double value){
    //Aloca memoria para o novo nó
    node* new = malloc(sizeof(node));
    //Caso a alocação falhe:
    if(!new)
        return 0; 
    //insere o elemento no novo nó
    new->element = value;
    //Caso para inserir primeiro elemento na lista
    if(ls->size == 0){
        new->B = ls->tail; 
        new->A = ls->head;
        ls->head->B = new;
        ls->tail->A = new;

        ls->size++;
        return 1;
    }
    //Caso a posição seja maior que o tamanho da lista é inserido no final,  simplesmente altera a posiçao de inserção para a ultima
    if(position > ls->size)
        position = ls->size;
    //Caso geral de inserção
    node* p = search(ls, position);
    node* pa = search(ls, position-1);
    new->A = pa;
    new->B = p;
    //Verifica como o novo nó deve ser encaixado na posição, conferindo a situação atual dos apontadores da posição e de sua anterior 
    if(pa->A == p){
        pa->A = new;
    }
    else{
        pa->B = new;
    }
    if(p->A == pa){
        p->A = new;
    }
    else{
        p->B = new;
    }

    ls->size++;
    return 1;
}

//Imprime conteudo da lista
void print(list* ls){
    //Procura o inicio da lista a partir da sentinela
    node *aux;
    node *auxaux = ls->head;
    if (ls->head->A == NULL)
        aux = ls->head->B;
    else{
        aux = ls->head->A;
    }
    //Percorre lista imprimindo seu conteudo
    while(aux != ls->tail){
        printf("%.4f ", aux->element);
        //Veridfica condições de percurso e implementa aux para o proximo nó
        if(aux->B == auxaux){
            auxaux = aux;
            aux = aux->A;
        }
        else{
            auxaux = aux;
            aux = aux->B;
        }
    }
    printf("\n");
}

//Função para inverte conteudo da lista entre duas posições dadas
int reverse(list* ls, int start, int end){
    //Caso para "inverter" uma poisção com ela mesma
    if (start == end)
        return 1;
    //Cria apontadores para:antecessor ao inicio da inversão(qa), inicio da inversao(q), final da inversão(p), sucessor do final da inversão(pd)
    node* qa = search(ls, start-1);
    node* q = search(ls, start);
    node* pd = search(ls, end+1);
    node* p = search(ls, end);
    //Faz antecessor ao inicio ter como proximo o ultimo da inversão
    if (qa->A == q){
        qa->A = p;
    }
    else{
        qa->B = p;
    }
    //Faz o proximo ao final ter como antecessor o antecessor o inicio  
    if (p->A == pd){
        p->A = qa;
    }
    else{
        p->B = qa;
    }
    //Faz o inicio ter como sucessor o sucecesor do fim
    if(q->A == qa){
        q->A = pd;
    }
    else{
        q->B = pd;
    }
    //Faz o sucessor do fim ter como anterior o inicio da inversao
    if(pd->A == p){
        pd->A = q;
    }
    else{
        pd->B  = q;
    }
    return 1;
}

//Função para deletar a lista e liberar a memoria
void delete_list(list* ls){
    //Procura o inicio da lista a partir da sentinela
    node *aux;
    node *auxaux = ls->head;
    if (ls->head->A == NULL)
        aux = ls->head->B;
    else{
        aux = ls->head->A;
    }
    //Percorre a lista liberando a memoria
    while (aux != ls->tail){
        node* q = aux;
        //Veridfica condições de percurso e implementa aux para o proximo nó
        if(aux->B == auxaux){
            auxaux = aux;
            aux = aux->A;
        }
        else{
            auxaux = aux;
            aux = aux->B;
        }
        free(q);
    }
    //Libera memoria das sentinelas
    free(ls->head);
    free(ls->tail);
    ls->size = 0;
}

//Função de menu para gerenciar as entradas e ações do programa
void menu(){
    char c;
    int position, start, end;
    double value;
    list *vetsi = create_list();
    //Verifica se a criação da lista foi bem sucedida
    if(!vetsi){
        printf("Falha na criação");
        exit(1);
    }
    //Laço para capturar caracteres e direcionar entredas as devidas funções
    while(scanf(" %c", &c) && c != 't'){
        //Chamada para inserir um novo elemento
        if (c == 'i'){
            scanf(" %d %lf", &position, &value);
            insert(vetsi, position, value);
        }
        //Chamada para imprimir a lista
        else if (c == 'p'){
            print(vetsi);            
        }
        //Chamada para inverter o conteudo entre duas posições da lista
        else if (c == 'v'){
            scanf(" %d %d", &start, &end);
            reverse(vetsi, start, end);
        }
    }
    if(vetsi->size)
        delete_list(vetsi);
    free(vetsi);
}

int main(){
    menu();
    return 0;
}