#include <stdio.h>
int main(void) {
	int a, b, soma;

	printf("Digite um numero inteiro: ");
	scanf("%d", &a); 

	printf("Digite um numero inteiro: ");
	scanf("%d", &b); 

	soma = a + b; 
	printf("O valor da soma: %d\n", soma); 
	return 0;
}
