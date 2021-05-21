#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    struct No *prox;
    int dado;
} No;

No *cabeca;

void adicionarDado(int dado) {
    No* no = (No *) malloc(sizeof (no));
    if (cabeca != NULL) {
        no->prox = cabeca;
    }
    cabeca = no;
    no->dado = dado;
}

void imprimirLista() {
    if (cabeca == NULL) {
        printf("\nLista vazia...\n\n");
    } else {
        No *no;
        no = cabeca;
        while (no != NULL) {
            printf("{%d[%p]->[%p]}\n", no->dado, no, no->prox);
            no = no->prox;
        }
    }
    printf("\n");
}

void main() {
    for (int i = 1; i <= 5; i++) {
        adicionarDado(i);
    }
    imprimirLista();
}