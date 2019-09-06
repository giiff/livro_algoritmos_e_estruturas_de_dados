#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Define o tipo No contendo

typedef struct Item {
    int dado;
    struct Item *prox;
} No;
//Define o primeiro No da lista
No* inicio = NULL;
// Funcao que define a lista como vazia.

void criarLista() {
    inicio = NULL;
}

void adicionarDado(int dado) {
    No *no;
    no = (No *) malloc(sizeof (No));
    if (no == NULL) {
        printf("Erro de memoria. Voce esta programando o Windows?\n");
    }
    no->dado = dado;
    no->prox = NULL;
    if (inicio == NULL)
        inicio = no;
    else {
        no->prox = inicio;
        inicio = no;
    }
}

void imprimirLista() {
    No *ponteiroNo;
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ponteiroNo = inicio;
    while (ponteiroNo != NULL) {
        printf("[%d(%p)|%p]\n", ponteiroNo->dado, ponteiroNo, ponteiroNo->prox);
        ponteiroNo = ponteiroNo->prox;
    }
}

void main() {
    No *aux;
    criarLista();
    // Insere na lista os numeros de 1 a 5
    for (int i = 1; i <= 5; i++)
        adicionarDado(i);
    imprimirLista();

}