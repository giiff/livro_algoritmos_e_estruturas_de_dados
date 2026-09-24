#include <stdio.h>
#define TAMANHO 100
int main(void) {
    char vetor[TAMANHO] = "Aqui vai uma frase bastante longa para servir de exemplo!";
    int qtd_de_letras_a_na_string = 0;
    // percorre a string ate encontrar o caractere nulo '\0' que marca o seu fim
    for (int i = 0; vetor[i] != '\0'; i++) {
        if (vetor[i] == 'a' || vetor[i] == 'A') {
            qtd_de_letras_a_na_string++;
        }
    }
    printf("Quantidade de letras \'a\' ou \'A\' na string: %d\n", qtd_de_letras_a_na_string);
    return 0;
}
// Quantidade de letras 'a' ou 'A' na string: 8
