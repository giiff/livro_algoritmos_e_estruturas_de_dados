#include <stdio.h>
#include <stdlib.h>
#define TAM 1024

// Define o tipo No contendo o nome de um diretorio
typedef struct No {
    char diretorio[TAM];
    struct No *prox;
} No;

//Define No cabeca da lista (o diretorio atual)
No* cabeca = NULL;

//Entra em um subdiretorio: insere um No no inicio da lista
void avancarDiretorio(const char diretorio[]) {
    No* no = malloc(sizeof(No));
    if (no == NULL) {
        printf("Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    snprintf(no->diretorio, sizeof(no->diretorio), "%s", diretorio);
    no->prox = cabeca;
    cabeca = no;
}

//Volta ao diretorio anterior: remove o No do inicio da lista
void voltarDiretorio(void) {
    if (cabeca != NULL) { // lista NAO vazia
        No *no = cabeca;
        cabeca = cabeca->prox;
        free(no); // libera memoria
    }
}

//Imprime o caminho do diretorio raiz ate o atual (do fim para o inicio da lista)
void imprimirCaminho(No* no) {
    if (no == NULL)
        return;
    imprimirCaminho(no->prox);
    printf("/%s", no->diretorio);
}

void imprimirLista(void) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    imprimirCaminho(cabeca);
    printf("\n");
}

int main(void) {
    avancarDiretorio("A0");
    imprimirLista();
    avancarDiretorio("A1");
    imprimirLista();
    avancarDiretorio("A2");
    imprimirLista();
    voltarDiretorio();
    imprimirLista();
    while (cabeca != NULL) //libera o que restou
        voltarDiretorio();
    return 0;
}
