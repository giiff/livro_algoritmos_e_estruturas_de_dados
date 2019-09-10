#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No contendo
typedef struct Item {
    int dado;
    struct Item *prox;
} No;

//Define o primeiro No da lista
No* ponteiroInicio = NULL;

// Funcao que define a lista como vazia.
void criarLista() {
    ponteiroInicio = NULL;
}

//Funcao que adiciona dados
void adicionarDado(int dado) {
    No* ponteiroNo;
    ponteiroNo = (No *) malloc(sizeof (ponteiroNo));
    if (ponteiroNo == NULL) {
        printf("Erro de memoria. Voce esta programando o Windows?\n");
    }
    ponteiroNo->dado = dado;
    ponteiroNo->prox = NULL;
    if (ponteiroInicio == NULL)
        ponteiroInicio = ponteiroNo;
    else {
        ponteiroNo->prox = ponteiroInicio;
        ponteiroInicio = ponteiroNo;
    }
}

void imprimirLista() {
    No* ponteiroNo;
    if (ponteiroInicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ponteiroNo = ponteiroInicio;
    while (ponteiroNo != NULL) {
        printf("[%d(%p)|%p]\n", ponteiroNo->dado, ponteiroNo, ponteiroNo->prox);
        ponteiroNo = ponteiroNo->prox;
    }
}

void main() {
    criarLista();
    // Insere na lista os numeros de 1 a 5
    for (int i = 1; i <= 5; i++)
        adicionarDado(i);
    imprimirLista();
}