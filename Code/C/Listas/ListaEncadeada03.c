#include <stdio.h>
#include <stdlib.h>

// Define o tipo No com links para o proximo e para o anterior
typedef struct No {
    struct No *proximo;
    struct No *anterior;
    int dado;
} No;

//Define o primeiro No (cabeca) da lista
No* cabeca = NULL;

//Funcao que adiciona dados no inicio da lista
void inserir(int dado) {
    No* no = malloc(sizeof(No)); //aloca o tamanho da struct, e nao do ponteiro
    if (no == NULL) {
        printf("Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    no->dado = dado;
    no->anterior = NULL; //o novo No sera o primeiro
    no->proximo = cabeca;
    if (cabeca != NULL) { //lista nao vazia: a antiga cabeca aponta de volta para o novo No
        cabeca->anterior = no;
    }
    cabeca = no;
}

//Funcao que imprime a lista
void imprimirLista(void) {
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    No* no = cabeca;
    while (no != NULL) {
        printf("|%p|%d(%p)|%p|\n", (void *) no->anterior, no->dado, (void *) no, (void *) no->proximo);
        no = no->proximo;
    }
    printf("\n");
}

//Funcao que libera todos os Nos da lista
void liberarLista(void) {
    while (cabeca != NULL) {
        No *proximo = cabeca->proximo;
        free(cabeca);
        cabeca = proximo;
    }
}

int main(void) {
    // Insere na lista os numeros de 1 a 5
    for (int i = 1; i <= 5; i++)
        inserir(i);
    imprimirLista();
    liberarLista();
    return 0;
}
