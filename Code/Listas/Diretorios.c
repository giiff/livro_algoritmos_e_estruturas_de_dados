#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 1024

// Define o tipo No contendo
typedef struct No{
    char diretorio[TAM];
    struct No *prox;
} No;

//Define No cabeca da lista
No* cabeca = NULL;

void printFormatado(No* no);

void avancarDiretorio(char diretorio[]) {
    No* no = (No *) malloc(sizeof (no) * 1024);
    for (int i=0;i<TAM;i++)
        no->diretorio[i] = diretorio[i];
    no->prox = NULL;
    if (cabeca == NULL)
        cabeca = no;
    else {
        no->prox = cabeca;
        cabeca = no;
    }
}

void voltarDiretorio() {
    No *no;
    if (cabeca == NULL) {// lista vazia
        return; 
    } else { // lista NAO vazia
        cabeca = cabeca->prox;
        free(no);// libera memoria
        return;
    } 
}

void imprimirLista() {
    No* no;
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    no = cabeca;
    while (no != NULL) {
        printFormatado(no);
        no = no->prox;
    }
    printf("\n");
}

void printFormatado(No* no){
    printf("/%s", no->diretorio, no, no->prox);
}

void main() {
    avancarDiretorio("A0");
    imprimirLista();
    avancarDiretorio("A1");
    imprimirLista();
    avancarDiretorio("A2");
    imprimirLista();
    voltarDiretorio("A2");
    imprimirLista();
}