#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No contendo
typedef struct No{
    int dado;
    struct No *prox;
} No;

//Define o ultimo No da lista
No* ponteiroFinal = NULL;

// Funcao que define a lista como vazia.
void criarLista() {
    ponteiroFinal = NULL;
}

//Funcao que adiciona dados
void adicionarDado(int dado) {
    No* ponteiroNo;
    ponteiroNo = (No *) malloc(sizeof (ponteiroNo));
    ponteiroNo->dado = dado;
    ponteiroNo->prox = NULL;
    if (ponteiroFinal == NULL)
        ponteiroFinal = ponteiroNo;
    else {
        ponteiroNo->prox = ponteiroFinal;
        ponteiroFinal = ponteiroNo;
    }
}

//Funcao que imprime a lista
void imprimirLista() {
    printf("-------------------------\n");
    No* ponteiroNo;
    if (ponteiroFinal == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ponteiroNo = ponteiroFinal;
    while (ponteiroNo != NULL) {
        printf("[%d(%p)|%p]\n", ponteiroNo->dado, ponteiroNo, ponteiroNo->prox);
        ponteiroNo = ponteiroNo->prox;
    }
    printf("-------------------------\n");
}

void main() {
    criarLista();
    // Insere na lista os numeros de 1 a 5
    for (int i = 1; i <= 5; i++)
        adicionarDado(i);
    imprimirLista();
}