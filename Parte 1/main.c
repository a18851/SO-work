#include "funcoes.h"
#include <stdio.h>

int main(){

    mostraFicheiro("exemplo");
    copiaFicheiro("exemplo");
    acrescentaFicheiro("exemplo", "exemplo2");
    printf("O ficheiro %s tem %d linhas.\n", "exemplo", contaFicheiro("exemplo"));
    removeFicheiro("exemplo");
    informaFicheiro("exemplo");

    return 0;
}

