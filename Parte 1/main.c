#include "funcoes.h"

int main(){

    mostraFicheiro("exemplo");
    copiaFicheiro("exemplo");
    acrescentaFicheiro("exemplo", "exemplo2");
    printf("O ficheiro %s tem %d linhas.\n", "exemplo.txt", contaFicheiro("exemplo.txt"));
    removeFicheiro("exemplo.txt");
    return 0;
}

