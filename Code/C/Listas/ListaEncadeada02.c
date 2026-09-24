#include <stdio.h>
#include <stdlib.h>

// Define o tipo No contendo um dado e o link para o proximo No
typedef struct No {
    int dado;
    struct No *link;
} No;

void printFormat01(No* no);
void printFormat02(No* no);
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
    no->link = cabeca; //o novo No aponta para a antiga cabeca (ou NULL)
    cabeca = no;
}

//Funcao que imprime a lista
void imprimirLista(void) {
    No* no;
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    no = cabeca;
    while (no != NULL) {
        if (no->link != NULL) {
            printFormat01(no);
        } else {
            printFormat02(no);
        }
        no = no->link;
    }
}

void printFormat01(No* no) {
    printf("[%d(%p)|%p]\n", no->dado, (void *) no, (void *) no->link);
    printf("                  |\n");
    printf("                  V\n");
    printf("      -------------\n");
    printf("      |\n");
    printf("      V\n");
}

void printFormat02(No* no) {
    printf("[%d(%p)|%p]\n", no->dado, (void *) no, (void *) no->link);
    printf("                  |\n");
    printf("                  V\n");
    printf("                 NULL\n");
}

void buscarDado(int dado) {
    No* no;
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    no = cabeca;
    while (no != NULL) {
        if (no->dado == dado)
            printf("[%d(%p)]\n", no->dado, (void *) no);
        no = no->link;
    }
}

void removerDado(int dado) {
    No *no = cabeca, *anterior = NULL;
    while (no != NULL) { //lista vazia: o laco nao executa
        if (no->dado == dado) {
            if (anterior == NULL) { // removendo o primeiro
                cabeca = no->link;
            } else { // removendo do meio ou do fim
                anterior->link = no->link; //refaz links
            }
            free(no); // libera memoria
            return;
        }
        anterior = no; // continua procurando na lista
        no = no->link;
    }
}

//Funcao que libera todos os Nos da lista
void liberarLista(void) {
    while (cabeca != NULL) {
        No *proximo = cabeca->link;
        free(cabeca);
        cabeca = proximo;
    }
}

int main(void) {
    // Insere na lista os numeros de 1 a 4
    for (int i = 1; i <= 4; i++)
        inserir(i);
    imprimirLista();
    removerDado(2);
    printf("--------------\n");
    imprimirLista();
    buscarDado(3);
    liberarLista();
    return 0;
}
