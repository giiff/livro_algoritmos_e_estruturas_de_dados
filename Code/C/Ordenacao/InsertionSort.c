#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 4

void insertionSort(int vetor[], int tamanho);
void imprimirVetor(const int vetor[], int tamanho);

int main(void) {
    int vetor[TAMANHO]; //vetor com tamanho definido
    clock_t tempoInicial, tempoFinal; //variaveis para guardar o tempo de execucao
    srand(42); //semente fixa: mesma sequencia a cada execucao (use srand(time(NULL)) para variar)
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 10; //atribui um inteiro aleatorio entre 0 e 9
    }
    imprimirVetor(vetor, TAMANHO); //mostra valores do vetor nao ordenado
    tempoInicial = clock(); //inicia contagem do tempo (somente da ordenacao)
    insertionSort(vetor, TAMANHO); //ordena pelo metodo da insercao
    tempoFinal = clock(); //finaliza contagem do tempo
    imprimirVetor(vetor, TAMANHO); //mostra valores do vetor ordenado
    //calcula e mostra o tempo total de execucao da ordenacao
    printf("Tempo: %f s\n", (double) (tempoFinal - tempoInicial) / CLOCKS_PER_SEC);
    return 0;
}

void imprimirVetor(const int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
}

void insertionSort(int vetor[], int tamanho) {
    int eleito, j;
    for (int i = 1; i < tamanho; i++) { //o eleito comeca pelo segundo elemento
        eleito = vetor[i];
        j = i - 1;
        //desloca para a direita os elementos maiores que o eleito
        while (j >= 0 && vetor[j] > eleito) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = eleito; //insere o eleito na posicao correta
    }
}
