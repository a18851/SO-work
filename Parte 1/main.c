#include "funcoes.h"

int main(){

    mostraFicheiro("exemplo");
    copiaFicheiro("exemplo");
    acrescentaFicheiro("exemplo", "exemplo2");
    contaFicheiro("exemplo");
    printf("O ficheiro %s tem %d linhas.\n", "exemplo.txt", contaFicheiro("exemplo.txt"));
    return 0;
}

