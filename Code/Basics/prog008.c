#include <stdio.h>
void main() {
	signed char v1 = 'A';
    int  v2 = 2147483647;
    short  v3 = 32767;
    long int  v4 = 2147483647;
    float  v5 = 3.4E38;
    double  v6 = 1.7E+308;
    long double  v7 = 1.79769e+308;
    printf("Tamanho de %c = %d bytes \n", v1, sizeof(v1) );
    printf("Tamanho de %d = %d bytes \n", v2, sizeof(v2) );  
    printf("Tamanho de %d = %d bytes \n", v3, sizeof(v3) ); 
    printf("Tamanho de %d = %d bytes \n", v4, sizeof(v4) ); 
    printf("Tamanho de %.1f = %d bytes \n", v5, sizeof(v5) ); 
    printf("Tamanho de %.1f = %d bytes \n", v6, sizeof(v6) ); 
    printf("Tamanho de %.1f = %d bytes \n", v7, sizeof(v7) );  
}
