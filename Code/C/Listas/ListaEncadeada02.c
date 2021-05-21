#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No contendo
typedef struct No{
    int dado;
    struct No *link;
} No;

void printFormat01(No* no);
void printFormat02(No* no);
//Define o ultimo No da lista
No* cabeca = NULL;

//Funcao que adiciona dados
void inserir(int dado) {
    No* no;
    no = (No *) malloc(sizeof (no));
    no->dado = dado;
    no->link = NULL;
    if (cabeca == NULL)
        cabeca = no;
    else {
        no->link = cabeca;
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
        if (no->link !=NULL){
            printFormat01(no);
        }else{
            printFormat02(no);
        }
        no = no->link;
    }

}

void printFormat01(No* no){
    printf("[%d(%p)|%p]\n", no->dado, no, no->link);
    printf("                  |\n");
    printf("                  V\n");
    printf("      -------------\n");
    printf("      |\n");
    printf("      V\n");
}
void printFormat02(No* no){
    printf("[%d(%p)|%p]\n", no->dado, no, no->link);
    printf("                  |\n");
    printf("                  V\n");
    printf("                 NULL\n");
}

void buscarDado(int dado){
    No* no;
    if (cabeca == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    no = cabeca;
    while (no != NULL) {
        if (no->dado == dado)
            printf("[%d(%p)]\n", no->dado, no);
        no = no->link;
    }
}

void removerDado(int dado) {
    No *no, *anterior;
    if (cabeca == NULL) {// lista vazia
        return; 
    } else { // lista NAO vazia
        no = cabeca;
        anterior = cabeca;
        while (no != NULL) {
            if (no->dado == dado){
                if (no == cabeca){// removendo o primeiro
                    cabeca = cabeca->link;
                    free(no);// libera memoria
                    return;
                } 
                else{ // removendo do meio
                    anterior->link = no->link;//refaz links
                    free(no);// libera memoria
                    return;
                }
            } 
            else{ // continua procurando na lista
                anterior = no;
                no = no->link;
            }
        }
        return;
    }
}

void main() {
    // Insere na lista os numeros de 1 a 3
    for (int i = 1; i <= 4; i++)
        inserir(i);
    imprimirLista();
    removerDado(2);
    printf("--------------\n");
    imprimirLista();
    buscarDado(3);
}