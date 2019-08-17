#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAMANHO 4
void main() {
    int vetor[TAMANHO]; //vetor com tamanho definido
    int eleito = 0;
    int j = 0;
    clock_t inicio, fim; //Variaveis para guardar o tempo de execucao
    srand(time(NULL)); //Cria uma semente para numeros aleatorios
    inicio = clock(); //inicia contagem do tempo
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 10; //Atribui um inteiro aleatorio entre 0 e 5
    }
    //Mostra valores do vetor nao ordenado
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    //Ordena vetor pelo metodo da da selecao
    for (int i = 1; i < TAMANHO; i++) {
        eleito = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > eleito) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = eleito;
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