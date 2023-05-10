#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define TAMANHO 50

int main() {
char nome[1000];
int ficheiro, leitura;
char conteudo[TAMANHO], ch;
int x=0, i;

printf ("Introduza o nome do arquivo : ");
gets (nome);

ficheiro = open(nome, O_RDONLY);
if (ficheiro == -1){
  perror("Erro ao abrir");
  return (1);
}
for(i=0;i<TAMANHO;i++){
leitura = read(ficheiro, conteudo, sizeof(conteudo));
if(conteudo[i] == '\n') x++;
}

printf ("\nO ficheiro possui %d linhas \n", x);

close(ficheiro);
return 0;
}
