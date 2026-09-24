#include <stdio.h>
#include <string.h>
#define CPF_TAM 15 // 14 caracteres do CPF formatado + 1 para o '\0'
#define NOME_TAM 100

typedef struct { // cria um novo tipo como struct
    float peso; // campo peso
    int idade; // campo idade
    float altura; // campo altura
    char cpf[CPF_TAM]; //campo cpf
    char nome[NOME_TAM]; //campo nome
} Pessoa; // nome do novo tipo criado

/*Funcao para calcular o IMC*/
float calcularIMC(Pessoa p) {
    return p.peso / (p.altura * p.altura);
}

/*Funcao para imprimir dados da pessoa (parametro por valor)*/
void imprimirPessoa(Pessoa p) {
    printf("CPF: %s\nNome: %s\nIdade: %d\nPeso: %.2f\nAltura: %.2f\n", p.cpf, p.nome, p.idade, p.peso, p.altura);
    printf("IMC: %.2f\n", calcularIMC(p));
}

/*Funcao para "preencher" uma pessoa (parametro por referencia)*/
void setPessoa(Pessoa* p, int idade, float peso, float altura, const char cpf[], const char nome[]) {
    // Quando usando ponteiros, o campo pode ser acessado de 2 formas:
    // a) (*nome_do_ponteiro).nome_do_campo
    // b) nome_do_ponteiro->nome_do_campo
    (*p).idade = idade; //exemplo a)
    p->peso = peso; //exemplo b)
    p->altura = altura;
    // copia as strings sem ultrapassar o tamanho dos campos e garante o '\0' final
    snprintf(p->cpf, sizeof(p->cpf), "%s", cpf);
    snprintf(p->nome, sizeof(p->nome), "%s", nome);
}

int main(void) {
    Pessoa pessoa01;
    setPessoa(&pessoa01, 37, 70.0f, 1.75f, "111.111.111-11", "Pessoa da Silva");
    imprimirPessoa(pessoa01);
    return 0;
}
