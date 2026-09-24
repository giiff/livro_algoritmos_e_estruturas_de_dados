#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 4

void bubbleSort(int vetor[], int tamanho);
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
    bubbleSort(vetor, TAMANHO); //ordena pelo metodo da bolha
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

void bubbleSort(int vetor[], int tamanho) {
    int aux; //variavel usada na troca
    int houveTroca = 1; //indica se alguma troca ocorreu na passagem
    //a cada passagem, o maior elemento ainda desordenado "sobe" para o fim do vetor
    for (int i = 0; i < tamanho - 1 && houveTroca; i++) {
        houveTroca = 0;
        //os ultimos i elementos ja estao em sua posicao final
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                houveTroca = 1;
            }
        }
    } //se uma passagem inteira nao fez trocas, o vetor ja esta ordenado
}
