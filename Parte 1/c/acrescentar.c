#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
  char nome[10000];
  int file1, file2, leitura, escrita;
  char conteudo[50];

  file1 = open("origem", O_RDONLY);
  if (file1 == -1) {
  printf("\nNao foi possivel abrir o ficheiro.\n");
  return 1;
  }else{
      file2 = open("destino", O_APPEND);
      if(file2 == -1){
      printf("\nNao foi possivel abrir o ficheiro.\n");
      return 1;
      }
      else{

        file2 = open("destino", O_APPEND);

        leitura = read(file1, conteudo, sizeof(conteudo));

        escrita = write(file2, conteudo, sizeof(conteudo));

        printf("\nEdicao efetuada com sucesso\n");

      }
    }
close(file1);
close(file2);
return 0;
}
