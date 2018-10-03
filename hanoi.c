#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fila.h"

typedef struct stack Stack;

struct stack{
    int topo;
    int tamanho;
    int *vetor;
    char nome;
    int numDiscos;
};

//prototipo das funcoes
Stack *criaStack(int tamanho,char nome);
int pop(Stack *torre);
void push(Stack *torre, int valor); 
int cheia(Stack *torre);
int vazia(Stack *torre);
void moveTorre(int Discos,Stack *origem, Stack *destino,Stack *aux, Fila *list);
void completaTorre(Stack *torre);
void exibe(Stack *torre);
void exibeTorres();
//fim prototipo funcoes

int main(){
    int numDiscos;
    printf("Digite o numero de Discos da torre de Hanoi: ");
    scanf("%d",&numDiscos);
    int tamanhoLista = pow(2,numDiscos)-1;

    Stack *t1 = criaStack(numDiscos+1,'A');
    Stack *t2 = criaStack(numDiscos+1,'B');
    Stack *t3 = criaStack(numDiscos+1,'C');
    Fila *list = criaFila();
    completaTorre(t1);
    exibeTorres(t1,t2,t3);
    moveTorre(numDiscos+1,t1,t2,t3, list);
    exibeTorres(t1,t2,t3);
    printar(list);
    return 0;
}




//funcoes

void exibeTorres(Stack *torre1,Stack *torre2,Stack *torre3){
    printf("------------------------------------");
    exibe(torre1);
    exibe(torre2);
    exibe(torre3);
    printf("------------------------------------\n");
}

void exibe(Stack *torre){
    int i;
    printf("\nHanoi %c :",torre->nome);
    for(i = 0;i  < torre->numDiscos-1; i++){
        printf(" %d",torre->vetor[i]);
    }
    printf("\n");
}

void moveTorre(int Discos,Stack *origem, Stack *destino,Stack *aux, Fila *list){
    if(Discos == 1){
        push(destino, pop(origem));
    } else {
        moveTorre(Discos-1, origem,aux, destino, list);
        push(destino, pop(origem));
        char str[50] = "Mover    da torre   para a torre  \n";
        int disco = Discos-1;
        char dis[5];
        sprintf(dis, "%d", disco);
        if(strlen(dis) > 1) {
            str[6] = dis[0];
            str[7] = dis[1];
        } else {
            str[6] = dis[0];
        }
        str[6] = dis[0];
        str[18] = origem->nome;
        str[34] = destino->nome;
        enfileira(list, str);
        moveTorre(Discos-1,aux,destino, origem, list);
    }
}

int cheia(Stack *torre){
    return torre->topo == torre->tamanho-1;
}

int vazia(Stack *torre){
    return torre->topo == -1;
}

int pop(Stack *torre){
    if(vazia(torre)){
        printf("Nao foi possivel retirar:torre vazia!\n");
    }else{
        torre->numDiscos--;
        return torre->vetor[(torre->topo)--];
    }
}


void push(Stack *torre, int valor){
    if(cheia(torre)){
        printf("Nao foi possivel adicionar:torre cheia!\n");
    }else{
        torre->vetor[++(torre->topo)] = valor;
        torre->numDiscos++;
    }
} 

void completaTorre(Stack *torre){
    int i = torre->tamanho;
    while(i--){
        push(torre,i);
    }
}

Stack *criaStack(int tamanho, char nome){
    Stack *torre = (Stack*) malloc(sizeof(Stack));
    torre->topo = -1;
    torre->numDiscos = 0;
    torre->tamanho =tamanho;
    torre->vetor = (int *) malloc(torre->tamanho*sizeof(int));
    torre->nome = nome;
    return torre;
}

// Implementacao da fila
Fila *criaFila(){
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->tamanho = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void enfileira(Fila *fila, char *str){
    fila->tamanho++;
    Node *novo = (Node *) malloc(sizeof(Node));
    strcpy(novo->str, str);
    novo->proximo = NULL;
    if(fila->inicio == NULL){
        fila->inicio = novo;
        fila->fim = fila->inicio;
    } else {
        fila->fim->proximo = novo;
        fila->fim = fila->fim->proximo;
    }
}

void printar(Fila *fila){
    Node *indice = fila->inicio;
    int i = 0;
    while(i < fila->tamanho){
        printf("%s\n", indice->str);
        indice = indice->proximo;  
        i++;
    }
}