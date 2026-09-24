#include <stdio.h>
#include <stdlib.h>
typedef struct No {
    int a;
    struct No* prox;
} No;

int main(void) {
    No* no1 = malloc(sizeof(No));
    No* no2 = malloc(sizeof(No));
    if (no1 == NULL || no2 == NULL) { //malloc devolve NULL se nao houver memoria
        free(no1);
        free(no2);
        return 1;
    }
    no1->a = 1;
    no2->a = 2;
    no2->prox = NULL; //no2 e o ultimo: nao aponta para ninguem
    no1->prox = no2; //no1 aponta para no2

    printf("[%d(%p)->%p]\n", no1->a, (void *) no1, (void *) no1->prox);
    printf("[%d(%p)->%p]\n", no2->a, (void *) no2, (void *) no2->prox);

    free(no1); //toda memoria alocada com malloc deve ser liberada com free
    free(no2);
    return 0;
}
