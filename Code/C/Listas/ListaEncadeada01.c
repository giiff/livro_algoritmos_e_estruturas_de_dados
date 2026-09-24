#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    struct No *prox;
    int dado;
} No;

No *cabeca = NULL;

void adicionarDado(int dado) {
    No* no = malloc(sizeof(No)); //aloca o tamanho da struct, e nao do ponteiro
    if (no == NULL) {
        printf("Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    no->dado = dado;
    no->prox = cabeca; //o novo no aponta para a antiga cabeca (ou NULL)
    cabeca = no;
}

void imprimirLista(void) {
    if (cabeca == NULL) {
        printf("\nLista vazia...\n\n");
    } else {
        No *no = cabeca;
        while (no != NULL) {
            printf("{%d[%p]->[%p]}\n", no->dado, (void *) no, (void *) no->prox);
            no = no->prox;
        }
    }
    printf("\n");
}

void liberarLista(void) {
    while (cabeca != NULL) {
        No *proximo = cabeca->prox;
        free(cabeca);
        cabeca = proximo;
    }
}

int main(void) {
    for (int i = 1; i <= 5; i++) {
        adicionarDado(i);
    }
    imprimirLista();
    liberarLista();
    return 0;
}
