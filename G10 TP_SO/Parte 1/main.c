#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
int opcao;
char nomeFicheiro1[50], nomeFicheiro2[50], nomeDiretoria[50];

printf("Escolha uma opcao:\n");
printf("1 - Mostrar ficheiro\n");
printf("2 - Copiar ficheiro\n");
printf("3 - Acrescentar ficheiro\n");
printf("4 - Contar linhas do ficheiro\n");
printf("5 - Remover ficheiro\n");
printf("6 - Informar dados do ficheiro\n");
printf("7 - Listar diretoria\n"); 
scanf("%d", &opcao);

if(opcao >= 1 && opcao <= 7){
    if(opcao != 7){ 
        printf("Introduza o nome do ficheiro de entrada: ");
        scanf("%s", nomeFicheiro1);
    }
    
    switch(opcao){
        case 1:
            mostraFicheiro(nomeFicheiro1);
            break;
        case 2:
            copiaFicheiro(nomeFicheiro1);
            break;
        case 3:
            printf("Introduza o nome do ficheiro de saida: ");
            scanf("%s", nomeFicheiro2);	
            acrescentaFicheiro(nomeFicheiro1, nomeFicheiro2);
            break;
        case 4:
            printf("O ficheiro %s tem %d linhas.\n", nomeFicheiro1, contaFicheiro(nomeFicheiro1));
            break;
        case 5:
            removeFicheiro(nomeFicheiro1);
            break;
        case 6:
            informaFicheiro(nomeFicheiro1);
            break;
        case 7:
            printf("Introduza o nome da diretoria: ");
            scanf("%s", nomeDiretoria);
            lista(nomeDiretoria);
            break; 
        default:
            break;
    }
} else {
    printf("Opcao nao valida!\n");
}

return 0;
}
