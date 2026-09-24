#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 4

void merge(int vetor[], int inicio, int meio, int fim);
void mergeSort(int vetor[], int inicio, int fim);
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
    mergeSort(vetor, 0, TAMANHO - 1); //ordena pelo metodo da intercalacao
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

//intercala as metades ordenadas vetor[inicio..meio] e vetor[meio+1..fim]
void merge(int vetor[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int vetorEsquerda[n1], vetorDireita[n2]; //copias temporarias das duas metades
    for (i = 0; i < n1; i++)
        vetorEsquerda[i] = vetor[inicio + i];
    for (j = 0; j < n2; j++)
        vetorDireita[j] = vetor[meio + 1 + j];
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) { //copia sempre o menor dos dois primeiros
        if (vetorEsquerda[i] <= vetorDireita[j]) { //"<=" mantem a ordenacao estavel
            vetor[k] = vetorEsquerda[i];
            i++;
        } else {
            vetor[k] = vetorDireita[j];
            j++;
        }
        k++;
    }
    while (i < n1) { //copia o que restou da metade esquerda
        vetor[k] = vetorEsquerda[i];
        i++;
        k++;
    }
    while (j < n2) { //copia o que restou da metade direita
        vetor[k] = vetorDireita[j];
        j++;
        k++;
    }
}

void mergeSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) { //condicao de parada: subvetor com um unico elemento
        int meio = inicio + (fim - inicio) / 2; //posicao para dividir o vetor
        mergeSort(vetor, inicio, meio); //chamada recursiva para a metade esquerda
        mergeSort(vetor, meio + 1, fim); //chamada recursiva para a metade direita
        merge(vetor, inicio, meio, fim); //intercala as duas metades ordenadas
    }
}
