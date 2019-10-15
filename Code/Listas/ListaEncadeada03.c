#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No contendo
typedef struct No{
    struct No *ante;
    struct No *prox;
    int dado;
} No;

//Define o ultimo No da lista
No* cabeca = NULL;

//Funcao que adiciona dados
void inserir(int dado) {
    No* no = (No *) malloc(sizeof (no));
    no->dado = dado;
    if (cabeca == NULL){//lista vazia
        cabeca = no;
        no->ante = NULL;
        no->prox = NULL;        
    }
    else {
        no->ante = cabeca;
        cabeca->prox = no;
        no->prox = NULL;
        cabeca = no;
    }
}

//Funcao que imprime a lista
void imprimirLista() {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    No* no = cabeca;
    while (no != NULL) {
        printf("[a_%p|%d(%p)|p_%p]\t", no->prox, no->dado, no, no->ante);
        no = no->ante;
    }
    printf("\n");return;
}

void main() {
    // Insere na lista os numeros de 1 a 3
    for (int i = 1; i <= 3; i++)
        inserir(i);
    imprimirLista();
}