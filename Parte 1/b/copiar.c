#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
  char nome[10000];
  int file1, file2, leitura, escrita;
  char conteudo[50];

  file1 = open("ficheiro.txt", O_RDONLY);
  if (file1 == -1) {
    printf("Nao foi possivel abrir o ficheiro.");
    return 1;
  }

  file2 = open("ficheiro.copia.txt", O_WRONLY | O_CREAT | S_IRWXU);

  leitura = read(file1, conteudo, sizeof(conteudo));

  escrita = write(file2, conteudo, sizeof(conteudo));

  printf("\nCopia efetuada com sucesso\n");


close(file1);
close(file2);
return 0;
}
