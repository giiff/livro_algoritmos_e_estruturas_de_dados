#include <stdio.h>
#include <string.h>
#include <math.h>
#define CPF_TAM 14
#define NOME_TAM 100

typedef struct { // cria um novo tipo como struct
    float peso; // campo peso
    int idade; // campo idade
    float altura; // campo altura
    char cpf[CPF_TAM]; //campo cpf
    char nome[NOME_TAM]; //campo nome
} Pessoa; // nome do novo tipo criado

/*Funcao para calcular o IMC*/
float calcularIMC(Pessoa p){
    return p.peso / (p.altura*p.altura);
}

/*Funcao para imprimir dados da pessoa (parametro por valor)*/
void imprimirPessoa(Pessoa p) {
    printf("CPF: %s\nNome: %s\nIdade: %d\nPeso: %.2f\nAltura: %.2f\n", p.cpf, p.nome, p.idade, p.peso, p.altura);
    printf("IMC: %.2f\n", calcularIMC(p));
}
/*Funcao para "preencher" uma pessoa (parametro por referencia)*/
void setPessoa(Pessoa* p, int idade, float peso, float altura, char cpf[], char nome[]) {
    // Quando usando ponteiros, o campo pode ser acessado de 2 formas:
    // a) (*nome_do_ponteiro).nome_do_campo
    // b) nome_do_ponteiro->nome_do_campo
    (*p).idade = idade; //exemplo a)
    p->peso = peso; //exemplo b)
    p->altura = altura;
    for (int i=0;i<CPF_TAM;i++)
        p->cpf[i] = cpf[i];
    for (int i=0;i<NOME_TAM;i++)
        p->nome[i] = nome[i];
}

void main() {
    Pessoa pessoa01;
    char cpf[CPF_TAM] = "111.111.111-11";
    char nome[NOME_TAM] = "Pessoa da Silva";
    setPessoa(&pessoa01, 37, 70, 1.75, cpf, nome);
    imprimirPessoa(pessoa01);
}