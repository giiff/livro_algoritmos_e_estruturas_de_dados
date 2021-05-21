#include <stdio.h>
#define TAMANHO 4
void main(){
    int vetor[TAMANHO][TAMANHO];
    for (int l=0; l<TAMANHO; l++){
    	for (int c=0; c<TAMANHO; c++){
    		printf("Valor [%d][%d]: ", l,c);
    		scanf("%d", &vetor[l][c]);
    	}
	}

	for (int l=0; l<TAMANHO; l++){
    	for (int c=0; c<TAMANHO; c++){
    		if(l == c){
    			printf("[%d][%d]:%d\t",l,c,vetor[l][c]);
    		}
    	}
    	printf("\n");
	}
}
// Valor [0][0]: 1
// Valor [0][1]: 2
// Valor [0][2]: 2
// Valor [0][3]: 2
// Valor [1][0]: 2
// Valor [1][1]: 1
// Valor [1][2]: 2
// Valor [1][3]: 2
// Valor [2][0]: 2
// Valor [2][1]: 2
// Valor [2][2]: 1
// Valor [2][3]: 2
// Valor [3][0]: 2
// Valor [3][1]: 2
// Valor [3][2]: 2
// Valor [3][3]: 1
// [0][0]:1	
// [1][1]:1	
// [2][2]:1	
// [3][3]:1