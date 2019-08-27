#include<stdlib.h> 
#include <stdio.h>
#include <time.h>
#define TAMANHO 4 
void trocar(int *x, int *y);
void quickSort(int vetor[], int inicio, int fim);

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
    //Chamada da funcao
    quickSort(vetor, 0, TAMANHO - 1);    
    //Mostra valores do vetor ordenado   
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d\t", vetor[i]);
    }
    printf("\n");
    tempoFinal = clock(); //finaliza contagem do tempo
    //calcula e mostra o tempo total de execucao
    printf("Tempo: %f s\n", (double) (tempoFinal - tempoInicial) / CLOCKS_PER_SEC);
}

void trocar(int *x, int *y) {
    int aux; aux = *x; *x = *y; *y = aux;
}

void quickSort(int vetor[], int inicio, int fim) {
    int pivo, i, j;
    if(inicio < fim) {//condicao de parada
        pivo = inicio;
        i = inicio;
        j = fim;
        while (i < j) {
            while(vetor[i] <= vetor[pivo] && i < fim)
                i++;
            while(vetor[j] > vetor[pivo])
                j--;
            if(i < j) {
                trocar(&vetor[i], &vetor[j]);
            }
        }
        trocar(&vetor[pivo], &vetor[j]);//troca os valores usando ponteiros
        quickSort(vetor, inicio, j - 1);
        quickSort(vetor, j + 1, fim);
    }
}

