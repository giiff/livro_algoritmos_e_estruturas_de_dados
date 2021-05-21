#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No{
  int dado;
  struct No* direita;
  struct No* esquerda;
} No;

No* criarArvore(){ return NULL; }

int ArvoreVazia(No* raiz){ // 1 se a arvore vazia, 0 caso contrario 
  return raiz == NULL;
}

int getValor(No** no){
  if ((*no) != NULL){
    return (*no)->dado;
  }
}

void mostrarArvore(No* raiz){
  if(!ArvoreVazia(raiz)){ //No nao vazio
    printf("%p<-%d(%p)->%p\n\n", raiz->esquerda, raiz->dado, raiz, raiz->direita);
    printf("%d", getValor(&raiz->esquerda));
    mostrarArvore(raiz->esquerda);//esquerda (subNo)
    mostrarArvore(raiz->direita); //direita (subNo)
  }
}

void buscarDado(No** raiz, int dado){
  if(!ArvoreVazia(*raiz)){ //No nao vazio
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
    if (raiz == NULL) return -1;
    else {
        int hEsquerda = getAltura(raiz->esquerda);
        int hDireita = getAltura(raiz->direita);
        return (hEsquerda < hDireita) ? hDireita + 1 : hEsquerda + 1;
    }
}

void main(){
  No* raiz = criarArvore();
  srand(time(0)); 
  for (int i = 0; i < 50; i++) {
    inserirDado(&raiz, rand() % 100); 
  }
  buscarDado(&raiz, 7);
  printf("Altura: %d\n", getAltura(raiz));
  free(raiz);
}