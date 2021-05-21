#include <stdio.h>
void main() {
    int x;
    printf("Informe um valor inteiro: ");
    scanf("%d", &x);
    if (x==10){
        printf("%d.\n", x);
    }
    else if (x==20){
        printf("%d.\n", x);
    }
    else if(x==30){
        printf("%d.\n", x);
    }
    else{
        printf("Diferente de 10, 20 ou 30.\n");
    }
}
