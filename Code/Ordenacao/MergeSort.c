#include<stdlib.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAMANHO 4 
void merge(int vetor[], int inicio, int meio, int fim);
void mergeSort(int vetor[], int inicio, int meio);

void main() {
    int vetor[TAMANHO]; //vetor com tamanho definido
    clock_t tempoInicial, tempoFinal; //Variaveis para guardar o tempo de execucao
    srand(time(NULL)); //Cria uma semente para numeros aleatorios
    tempoInicial = clock(); //inicia contagem do tempo
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 10; //Atribui um inteiro aleatorio entre 0 e 9
    }
    //Mostra valores do vetor nao ordenado
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    //Chama a fucao passando o vetor como parametro
    mergeSort(vetor, 0, TAMANHO - 1);
    //Mostra valores do vetor ordenado   
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    tempoFinal = clock(); //finaliza contagem do tempo
    //calcula e mostra o tempo total de execucao
    printf("Tempo: %f s\n", (double) (tempoFinal - tempoInicial) / CLOCKS_PER_SEC);
}

void merge(int vetor[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int vetorEsquerda[n1], vetorDireita[n2];
    for (i = 0; i < n1; i++)
        vetorEsquerda[i] = vetor[inicio + i];
    for (j = 0; j < n2; j++)
        vetorDireita[j] = vetor[meio + 1 + j];
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (vetorEsquerda[i] <= vetorDireita[j]) {
            vetor[k] = vetorEsquerda[i];
            i++;
        }
        else {//troca
            vetor[k] = vetorDireita[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vetor[k] = vetorEsquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = vetorDireita[j];
        j++;
        k++;
    }
}

void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {//condicao de parada
        int m = inicio + (fim - inicio) / 2;//posicao para dividir o vetor
        mergeSort(vetor, inicio, m);//chamada recursiva para a metade esquerda
        mergeSort(vetor, m + 1, fim);//chamada recursiva para a metade direita
        merge(vetor, inicio, m, fim);
    }
}
