// Testa as funcoes de ordenacao dos exemplos do livro com milhares de vetores
// aleatorios e todos os casos pequenos. Cada exemplo e incluido com a sua
// funcao main renomeada, para que apenas as funcoes de ordenacao sejam usadas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define imprimirVetor imprimirVetor_bubble
#define main main_bubble
#include "BubbleSort.c"
#undef main
#undef imprimirVetor
#undef TAMANHO

#define imprimirVetor imprimirVetor_selection
#define main main_selection
#include "SelectionSort.c"
#undef main
#undef imprimirVetor
#undef TAMANHO

#define imprimirVetor imprimirVetor_insertion
#define main main_insertion
#include "InsertionSort.c"
#undef main
#undef imprimirVetor
#undef TAMANHO

#define imprimirVetor imprimirVetor_merge
#define main main_merge
#include "MergeSort.c"
#undef main
#undef imprimirVetor
#undef TAMANHO

#define imprimirVetor imprimirVetor_quick
#define main main_quick
#include "QuickSort.c"
#undef main
#undef imprimirVetor
#undef TAMANHO

#define MAX 64

static void mergeSortTamanho(int v[], int n) { if (n > 0) mergeSort(v, 0, n - 1); }
static void quickSortTamanho(int v[], int n) { if (n > 0) quickSort(v, 0, n - 1); }

typedef void (*Ordenador)(int[], int);

static int comparar(const void *a, const void *b) {
    int x = *(const int *) a, y = *(const int *) b;
    return (x > y) - (x < y);
}

int main(void) {
    const char *nomes[] = {"bubbleSort", "selectionSort", "insertionSort", "mergeSort", "quickSort"};
    Ordenador ordenadores[] = {bubbleSort, selectionSort, insertionSort, mergeSortTamanho, quickSortTamanho};
    int original[MAX], esperado[MAX], vetor[MAX];
    int falhas = 0;
    srand(1);
    for (int caso = 0; caso < 20000; caso++) {
        int n = caso % (MAX + 1);
        int faixa = 1 + rand() % 100; // faixas pequenas geram muitos valores repetidos
        for (int i = 0; i < n; i++) {
            if (caso % 7 == 0) original[i] = i;             // ja ordenado
            else if (caso % 7 == 1) original[i] = n - i;    // ordem decrescente
            else original[i] = rand() % faixa - faixa / 2;  // aleatorio (inclui negativos)
        }
        memcpy(esperado, original, sizeof(int) * n);
        qsort(esperado, n, sizeof(int), comparar);
        for (int k = 0; k < 5; k++) {
            memcpy(vetor, original, sizeof(int) * n);
            ordenadores[k](vetor, n);
            if (memcmp(vetor, esperado, sizeof(int) * n) != 0) {
                if (falhas < 10) printf("%s falhou com n = %d (caso %d)\n", nomes[k], n, caso);
                falhas++;
            }
        }
    }
    return falhas == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
