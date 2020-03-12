#include <stdio.h>
void main() {
    printf ("Quem descobriu o Brasil?\n\n");
    printf ("a) Cabral\n");
    printf ("b) Cabrel\n");
    printf ("c) Cabril\n");
    printf ("d) Cabrol\n");
    printf ("e) Cabrul\n\n");
    char resposta;
    printf("Resposta (a,b,c,d ou e): ");
    scanf("%c", &resposta);
    if (resposta=='a'){
        printf("Certo.\n");
    }
    else if (resposta=='b'){
        printf("Errado.\n");
    }
    else if(resposta=='c'){
        printf("Errado.\n");
    }
    else if(resposta=='d'){
        printf("Errado.\n");
    }
    else if(resposta=='e'){
        printf("Errado.\n");
    }
    else{
        printf("Opcao invalida.\n");
    }
}
