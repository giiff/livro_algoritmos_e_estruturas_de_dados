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
  inserirDado(&raiz, 50); 
  inserirDado(&raiz, 25); 
  inserirDado(&raiz, 75); 
  inserirDado(&raiz, 5); 
  exibirNo(raiz); 
  free(raiz);
  system("echo 'digraph G {a->b; a->c;b->d;}' | dot -Tpng >teste.png");

}