#include <stdio.h>
#include <stdlib.h>

typedef struct No{
  int dado;
  struct No* direita;
  struct No* esquerda;
} No;

No* criarArvore(){
  return NULL;
}

int NoVazia(No* raiz){
  // 1 se a arvore for vazia
  // 0 caso contrario 
  return raiz == NULL;
}

void exibirNo(No* raiz){
  if(!NoVazia(raiz)){ //No nao vazio
    printf("%p<-%d(%p)->%p\n\n", raiz->esquerda, raiz->dado, raiz, raiz->direita);
    exibirNo(raiz->esquerda);//esquerda (subNo)
    exibirNo(raiz->direita); //direita (subNo)
  }
}

void buscar(No** raiz, int dado){
  if(!NoVazia(*raiz)){ //No nao vazio
    if(dado == (*raiz)->dado){
      printf("%d encontrado.\n", dado);
      return;
    }
    else{
        buscar(&(*raiz)->esquerda, dado);
        buscar(&(*raiz)->direita, dado);
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

void main(){
  No* raiz = criarArvore();
  for (int i = 0; i < 10; i++) {
    inserirDado(&raiz, rand() % 20); 
  }
  exibirNo(raiz); 
  buscar(&raiz, 10);
  free(raiz);
  //system("echo 'digraph G {a->b; a->c;b->d;}' | dot -Tpng >teste.png");
}