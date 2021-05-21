#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct No{
    int a;
    struct No* prox;
 } No;

void main() {
    No* no1 = (No *) malloc (sizeof(No));
    no1->a = 1;
    
    No* no2 = (No *) malloc (sizeof(No));
    no2->a = 2;
    no2->prox = NULL;

    no1->prox = no2;

    printf ("[%d(%p)->%p]\n", no1->a, no1, no1->prox);
    printf ("[%d(%p)->%p]\n", no2->a, no2, no2->prox);


}