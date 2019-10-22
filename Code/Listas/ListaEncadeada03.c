#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No contendo
typedef struct No{
    struct No *proximo;
    struct No *anterior;
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
        no->proximo = NULL;
        no->anterior = NULL;        
    }
    else {
        no->proximo = cabeca;
        cabeca->anterior = no;
        no->anterior = NULL;
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
        printf("|%p|%d(%p)|%p|\t", no->anterior, no->dado, no, no->proximo);
        no = no->proximo;
    }
    printf("\n");return;
}

void main() {
    // Insere na lista os numeros de 1 a 3
    for (int i = 1; i <= 3; i++)
        inserir(i);
    imprimirLista();
}