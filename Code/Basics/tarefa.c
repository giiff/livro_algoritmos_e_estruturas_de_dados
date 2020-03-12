#include <stdio.h>
void main() {
    float valor;
    printf("Informe um valor do item: ");
    scanf("%f", &valor);
    if (valor<2500){
        valor += valor*0.07;
        printf("Valor com impostos: R$ %.2f\n", valor);
    }
    else{
        valor += valor*0.075;
        printf("Valor com impostos: R$ %.2f\n", valor);
    }
}
