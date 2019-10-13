#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No com struct
typedef struct No{
    int dado;
    struct No *prox;
} No;

void printFormat01(No* no);
void printFormat02(No* no);
//Variavel global com o no mais recente da lista
No* cabeca = NULL;

//Funcao que adiciona dados
void inserir(int dado) {
    No* no;
    no = (No *) malloc(sizeof (no));
    no->dado = dado;
    no->prox = NULL;
    if (cabeca == NULL)
        cabeca = no;
    else {
        no->prox = cabeca;
        cabeca = no;
    }
}

//Funcao que imprime a lista
void imprimirLista() {
    No* no;
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    no = cabeca;
    while (no != NULL) {
        if (no->prox !=NULL){
            printFormat01(no);
        }else{
            printFormat02(no);
        }
        no = no->prox;
    }

}

void printFormat01(No* no){
    printf("[%d(%p)|%p]\n", no->dado, no, no->prox);
    printf("                  |\n");
    printf("                  V\n");
    printf("      -------------\n");
    printf("      |\n");
    printf("      V\n");
}
void printFormat02(No* no){
    printf("[%d(%p)|%p]\n", no->dado, no, no->prox);
    printf("                  |\n");
    printf("                  V\n");
    printf("                 NULL\n");
}

void main() {
    // Insere na lista os numeros de 1 a 4
    for (int i = 1; i <= 4; i++)
        inserir(i);
    imprimirLista();
}