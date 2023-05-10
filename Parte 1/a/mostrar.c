#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
char nome[1000];
int ficheiro, leitura;
char conteudo[49];

printf ("Introduza o nome do arquivo : ");
gets (nome);

ficheiro = open(nome, O_RDONLY);
if (ficheiro == -1){
  perror("Erro ao abrir");
  return 1;
}

leitura = read(ficheiro, conteudo, sizeof(conteudo));
write(STDOUT_FILENO, conteudo, leitura);
close(ficheiro);
return 0;
}
