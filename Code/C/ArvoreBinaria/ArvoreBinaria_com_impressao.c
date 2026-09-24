#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No* direita;
    struct No* esquerda;
} No;

No* criarArvore(void) { return NULL; }

int arvoreVazia(No* raiz) { // 1 se a arvore esta vazia, 0 caso contrario
    return raiz == NULL;
}

// Percurso em ordem simetrica (esquerda, raiz, direita): mostra os dados em ordem crescente
void mostrarArvore(No* raiz) {
    if (!arvoreVazia(raiz)) {
        mostrarArvore(raiz->esquerda);
        printf("%d ", raiz->dado);
        mostrarArvore(raiz->direita);
    }
}

// Devolve 1 se o dado estiver na arvore e 0 caso contrario
int buscarDado(No* raiz, int dado) {
    if (arvoreVazia(raiz))
        return 0; // chegou a uma folha sem encontrar
    if (dado == raiz->dado)
        return 1;
    if (dado < raiz->dado) // dado menor? vai pra esquerda
        return buscarDado(raiz->esquerda, dado);
    return buscarDado(raiz->direita, dado); // dado maior? vai pra direita
}

// Recebe o endereco do ponteiro para poder alterar a arvore do chamador
void inserirDado(No** raiz, int dado) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(No));
        if (*raiz == NULL) {
            printf("Memoria insuficiente.\n");
            exit(EXIT_FAILURE);
        }
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
        (*raiz)->dado = dado;
    } else if (dado < (*raiz)->dado) { // dado menor? vai pra esquerda
        inserirDado(&(*raiz)->esquerda, dado);
    } else if (dado > (*raiz)->dado) { // dado maior? vai pra direita
        inserirDado(&(*raiz)->direita, dado);
    } // dado igual: nao insere repetidos
}

int getAltura(No* raiz) {
    if (raiz == NULL) return -1; // altura da arvore vazia
    int hEsquerda = getAltura(raiz->esquerda);
    int hDireita = getAltura(raiz->direita);
    return (hEsquerda < hDireita) ? hDireita + 1 : hEsquerda + 1;
}

// Escreve no arquivo as arestas da arvore no formato DOT do Graphviz
// Para gerar a imagem e preciso ter o Graphviz instalado
// Ubuntu: sudo apt install graphviz
// Fedora: sudo dnf install graphviz
void gerarArquivoDot(FILE* arquivoDot, No* raiz) {
    if (raiz != NULL) {
        if (raiz->esquerda != NULL)
            fprintf(arquivoDot, "%d:sw->%d [ label=\"esq\"];\n", raiz->dado, raiz->esquerda->dado);
        if (raiz->direita != NULL)
            fprintf(arquivoDot, "%d:se->%d [ label=\"dir\"];\n", raiz->dado, raiz->direita->dado);
        gerarArquivoDot(arquivoDot, raiz->esquerda); //esquerda (subarvore)
        gerarArquivoDot(arquivoDot, raiz->direita); //direita (subarvore)
    }
}

// Libera os nos em pos-ordem: primeiro os filhos, depois o pai
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main(void) {
    No* raiz = criarArvore();
    srand(42); // semente fixa: mesma arvore a cada execucao
    for (int i = 0; i < 50; i++) {
        inserirDado(&raiz, rand() % 100);
    }
    mostrarArvore(raiz);
    printf("\n");
    printf("7 %s\n", buscarDado(raiz, 7) ? "encontrado." : "nao encontrado.");
    printf("Altura: %d\n", getAltura(raiz));
    FILE* arquivoDot = fopen("arvore.dot", "w");
    if (arquivoDot == NULL) {
        printf("Nao foi possivel criar arvore.dot\n");
        liberarArvore(raiz);
        return 1;
    }
    fprintf(arquivoDot, "digraph G {\nsplines=line;\n");
    gerarArquivoDot(arquivoDot, raiz);
    fprintf(arquivoDot, "}\n");
    fclose(arquivoDot);
    liberarArvore(raiz);
    printf("Para gerar a imagem: dot -Tpng arvore.dot -o arvore.png\n");
    return 0;
}
