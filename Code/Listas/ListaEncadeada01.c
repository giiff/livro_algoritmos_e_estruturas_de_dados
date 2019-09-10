#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define o tipo No com struct
typedef struct No{
    int dado;
    struct No *prox;
} No;

void printFormat01(No* ponteiroNo);
void printFormat02(No* ponteiroNo);
//Variavel global com o no mais recente da lista
No* ponteiroFinal = NULL;

//Funcao que adiciona dados
void adicionarDado(int dado) {
    No* ponteiroNo;
    ponteiroNo = (No *) malloc(sizeof (ponteiroNo));
    ponteiroNo->dado = dado;
    ponteiroNo->prox = NULL;
    if (ponteiroFinal == NULL)
        ponteiroFinal = ponteiroNo;
    else {
        ponteiroNo->prox = ponteiroFinal;
        ponteiroFinal = ponteiroNo;
    }
}

//Funcao que imprime a lista
void imprimirLista() {
    No* ponteiroNo;
    if (ponteiroFinal == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    ponteiroNo = ponteiroFinal;
    while (ponteiroNo != NULL) {
        if (ponteiroNo->prox !=NULL){
            printFormat01(ponteiroNo);
        }else{
            printFormat02(ponteiroNo);
        }
        ponteiroNo = ponteiroNo->prox;
    }

}

void printFormat01(No* ponteiroNo){
    printf("[%d(%p)|%p]\n", ponteiroNo->dado, ponteiroNo, ponteiroNo->prox);
    printf("                  |\n");
    printf("                  V\n");
    printf("      -------------\n");
    printf("      |\n");
    printf("      V\n");
}
void printFormat02(No* ponteiroNo){
    printf("[%d(%p)|%p]\n", ponteiroNo->dado, ponteiroNo, ponteiroNo->prox);
    printf("                  |\n");
    printf("                  V\n");
    printf("                 NULL\n");
}

void main() {
    // Insere na lista os numeros de 1 a 4
    for (int i = 1; i <= 4; i++)
        adicionarDado(i);
    imprimirLista();
}