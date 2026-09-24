#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 4

void selectionSort(int vetor[], int tamanho);
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
    selectionSort(vetor, TAMANHO); //ordena pelo metodo da selecao
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

void selectionSort(int vetor[], int tamanho) {
    int eleito, posicaoDoMenor;
    for (int i = 0; i < tamanho - 1; i++) { //da posicao 0 ate a penultima
        eleito = vetor[i];
        posicaoDoMenor = i;
        //procura o menor valor a direita da posicao i
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[posicaoDoMenor]) {
                posicaoDoMenor = j;
            }
        }
        if (posicaoDoMenor != i) { //troca o eleito com o menor encontrado
            vetor[i] = vetor[posicaoDoMenor];
            vetor[posicaoDoMenor] = eleito;
        }
    }
}
