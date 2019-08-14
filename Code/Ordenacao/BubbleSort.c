#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAMANHO 4

void main() {

    int vetor[TAMANHO]; //vetor com tamanho definido
    int aux = 0; //varivel para ser usada na troca
    clock_t inicio, fim; //Variaveis para guardar o tempo de execucao
    srand(time(NULL)); //Cria uma semente para numeros aleatorios
    inicio = clock(); //inicia contagem do tempo

    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 10; //Atribui um inteiro aleatorio entre 0 e 9
    }
    //Mostra valores do vetor nao ordenado
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    //Ordena vetor pelo metodo da bolha
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
    //Mostra valores do vetor ordenado   
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    fim = clock(); //finaliza contagem do tempo
    //calcula e mostra o tempo total de execucao
    printf("Tempo: %f s\n", (double) (fim - inicio) / CLOCKS_PER_SEC);
}

// 2       8       1       3       2                                                                                                                                                                                             
// 1       2       2       3       8  
// Tempo: 0.000351 s 