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
    Marca marca; //uma struct dentro de outra struct (composicao)
} Carro; // nome do novo tipo criado

void setMarca(Marca* marca, const char nome[], const char nacionalidade[]) {
    // copia as strings sem ultrapassar o tamanho dos campos e garante o '\0' final
    snprintf(marca->nome, sizeof(marca->nome), "%s", nome);
    snprintf(marca->nacionalidade, sizeof(marca->nacionalidade), "%s", nacionalidade);
}

void setCarro(Carro* carro, const char modelo[], float motor, Marca marca) {
    snprintf(carro->modelo, sizeof(carro->modelo), "%s", modelo);
    carro->motor = motor;
    carro->marca = marca; //structs podem ser copiadas por atribuicao
}

void printCarro(Carro carro) {
    printf("%s\n", carro.modelo);
    printf("%.2f\n", carro.motor);
    printf("%s\n", carro.marca.nacionalidade);
    printf("%s\n", carro.marca.nome);
}

int main(void) {
    Marca ford;
    Marca vw;
    setMarca(&ford, "Ford", "EUA");
    setMarca(&vw, "VW", "Alemanha");
    Carro gol;
    setCarro(&gol, "Gol", 1.0f, vw);
    printCarro(gol);
    Carro ka;
    setCarro(&ka, "Ka", 1.5f, ford);
    printCarro(ka);
    return 0;
}
