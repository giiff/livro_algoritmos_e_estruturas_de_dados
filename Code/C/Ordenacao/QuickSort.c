#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 4

void trocar(int *x, int *y);
void quickSort(int vetor[], int inicio, int fim);
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
    quickSort(vetor, 0, TAMANHO - 1); //ordena pelo metodo rapido
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

void trocar(int *x, int *y) { //troca os valores usando ponteiros
    int aux = *x;
    *x = *y;
    *y = aux;
}

void quickSort(int vetor[], int inicio, int fim) {
    int pivo, i, j;
    if (inicio < fim) { //condicao de parada
        pivo = inicio; //o primeiro elemento e escolhido como pivo
        i = inicio;
        j = fim;
        while (i < j) {
            while (vetor[i] <= vetor[pivo] && i < fim) //avanca enquanto menor ou igual ao pivo
                i++;
            while (vetor[j] > vetor[pivo]) //recua enquanto maior que o pivo
                j--;
            if (i < j) {
                trocar(&vetor[i], &vetor[j]);
            }
        }
        trocar(&vetor[pivo], &vetor[j]); //coloca o pivo em sua posicao final
        quickSort(vetor, inicio, j - 1); //ordena os menores que o pivo
        quickSort(vetor, j + 1, fim); //ordena os maiores que o pivo
    }
}
