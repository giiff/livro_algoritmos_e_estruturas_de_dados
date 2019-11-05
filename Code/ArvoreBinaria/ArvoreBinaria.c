#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
  int dado;
  struct No* direita;
  struct No* esquerda;
} No;

No* criarArvore(){ return NULL; }

int NoVazia(No* raiz){ // 1 se a arvore vazia, 0 caso contrario 
  return raiz == NULL;
}

int getValor(No** no){
  if ((*no) != NULL){
    return (*no)->dado;
  }
}

void mostrarArvore(No* raiz){
  if(!NoVazia(raiz)){ //No nao vazio
    printf("%p<-%d(%p)->%p\n\n", raiz->esquerda, raiz->dado, raiz, raiz->direita);
    printf("%d", getValor(&raiz->esquerda));
    mostrarArvore(raiz->esquerda);//esquerda (subNo)
    mostrarArvore(raiz->direita); //direita (subNo)
  }
}

// Metodo para desenhar a arvore em um arquivo arvore.png
// Precisa de ter o graphviz instalado
// Ubuntu: sudo apt install python-pydot python-pydot-ng graphviz
// Fedora: sudo dnf install graphviz
void gerarArquivoDot(FILE** arquivoDot, No* raiz){
  if(raiz != NULL){
    char s1[20]; 
    char s2[20];
    if (getValor(&raiz->esquerda)!=0){
      sprintf(s1, "%d->%d;\n", raiz->dado, getValor(&raiz->esquerda));
      fprintf((*arquivoDot), "%s", s1);
    }
    if (getValor(&raiz->direita)!=0){
      sprintf(s2, "%d->%d;\n", raiz->dado, getValor(&raiz->direita));
      fprintf((*arquivoDot), "%s", s2);
    }    
    gerarArquivoDot(arquivoDot,raiz->esquerda);//esquerda (subNo)
    gerarArquivoDot(arquivoDot,raiz->direita); //direita (subNo)
  }
}

void buscarDado(No** raiz, int dado){
  if(!NoVazia(*raiz)){ //No nao vazio
    if(dado == (*raiz)->dado){
      printf("%d encontrado.\n", dado);
      return;
    }
    else{
      if(dado < (*raiz)->dado){ //dado menor? vai pra esquerda
        buscarDado(&(*raiz)->esquerda, dado);
      }
      if(dado > (*raiz)->dado){ //dado maior? vai pra direita
        buscarDado(&(*raiz)->direita, dado);
      }
    }
  }
}

void inserirDado(No** raiz, int dado){
    if(*raiz == NULL){
      *raiz = (No*)malloc(sizeof(No));
      (*raiz)->esquerda = NULL; 
      (*raiz)->direita = NULL; 
      (*raiz)->dado = dado; 
    } else {
        if(dado < (*raiz)->dado){ //dado menor? vai pra esquerda
            //percorrer subNo da esquerda
            inserirDado(&(*raiz)->esquerda, dado);
        }
        if(dado > (*raiz)->dado){ //dado maior? vai pra direita
            //percorrer subNo da direita
            inserirDado(&(*raiz)->direita, dado);
        }
    }
}

int getAltura(No* raiz) {
    if (raiz == NULL) return 0;
    else {
        int hEsquerda = getAltura(raiz->esquerda);
        int hDireita = getAltura(raiz->direita);
        return (hEsquerda < hDireita) ? hDireita + 1 : hEsquerda + 1;
    }
}

void main(){
  No* raiz = criarArvore();
  srand(time(0)); 
  for (int i = 0; i < 5; i++) {
    inserirDado(&raiz, rand() % 100); 
  }
  //mostrarArvore(raiz); 
  //buscarDado(&raiz, 7);
  printf("Altura: %d", getAltura(raiz));
  FILE *arquivoDot;
  arquivoDot = fopen("arvore.dot", "w");
  fprintf(arquivoDot, "%s", "digraph G {\n");
  gerarArquivoDot(&arquivoDot, raiz);
  fprintf(arquivoDot, "%s", "}\n");
  fclose(arquivoDot);
  free(raiz);
  system("dot -Tpng arvore.dot -o arvore.png");
}