#include <stdio.h>
#define TAMANHO 100
void main(){
    char vetor[TAMANHO] = "Aqui vai uma frase bastante longa para servir de exemplo!";
    int qtd_de_letras_a_na_string = 0;
    for (int i=0; i<TAMANHO; i++){
    	if (vetor[i] == 'a' || vetor[i] == 'A'){
            qtd_de_letras_a_na_string++;
        }
    }
    printf("Quantidade de letras \'a\' ou \'A\' na string: %d\n", qtd_de_letras_a_na_string);
}
// Quantidadte de letras 'a' ou 'A' na string: 8