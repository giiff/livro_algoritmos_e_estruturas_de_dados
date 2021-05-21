#include <stdio.h>
void main() {
    int x;
    printf("Informe um valor inteiro: ");
    scanf("%d", &x);
    if (x>=0){
        printf("%d: positivo.\n", x);
    }
    else{
        printf("%d: negativo.\n", x);
    }
}