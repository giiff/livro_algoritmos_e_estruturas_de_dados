#include <stdio.h>
#include <string.h>
#define TAM 100
typedef struct { // cria um novo tipo como struct
    char nome[TAM]; //nome da marca
    char nacionalidade[TAM]; //nacionalidade da marca
} Marca; // nome do novo tipo criado

typedef struct { // cria um novo tipo como struct
    char modelo[TAM]; //modelo do carro
    float motor; //motorizacao
    Marca marca;
} Carro; // nome do novo tipo criado

void setMarca(Marca* marca, char nome[], char nacionalidade[]) {
    for (int i=0;i<TAM;i++)
        marca->nome[i] = nome[i];
    for (int i=0;i<TAM;i++)
        marca->nacionalidade[i] = nacionalidade[i];
}

void setCarro(Carro* carro, char modelo[], float motor, Marca marca) {
    for (int i=0;i<TAM;i++)
        carro->modelo[i] = modelo[i];
    carro->motor = motor;
    carro->marca = marca;
}

void printCarro(Carro carro){
	printf("%s\n",carro.modelo);
	printf("%.2f\n",carro.motor);
	printf("%s\n",carro.marca.nacionalidade);
	printf("%s\n",carro.marca.nome);
}

void main(){
	Marca ford;
	Marca vw;
	setMarca(&ford, "Ford", "EUA");
	setMarca(&vw, "VW", "Alemanha");
	Carro gol;
	setCarro(&gol, "Gol", 1.0, vw);
	printCarro(gol);
}