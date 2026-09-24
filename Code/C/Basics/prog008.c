#include <stdio.h>
int main(void) {
    signed char v1 = 'A';
    int v2 = 2147483647;
    short v3 = 32767;
    long int v4 = 2147483647L;
    float v5 = 3.4E38f;
    double v6 = 1.7E+308;
    long double v7 = 1.79769e+308L;
    // sizeof devolve um valor do tipo size_t, impresso com %zu
    printf("Tamanho de %c = %zu bytes \n", v1, sizeof(v1));
    printf("Tamanho de %d = %zu bytes \n", v2, sizeof(v2));
    printf("Tamanho de %hd = %zu bytes \n", v3, sizeof(v3));
    printf("Tamanho de %ld = %zu bytes \n", v4, sizeof(v4));
    printf("Tamanho de %.1e = %zu bytes \n", v5, sizeof(v5));
    printf("Tamanho de %.1e = %zu bytes \n", v6, sizeof(v6));
    printf("Tamanho de %.1Le = %zu bytes \n", v7, sizeof(v7));
    return 0;
}
