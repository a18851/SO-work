#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
char nome[1000];
int ficheiro, leitura;
char conteudo[49];

printf ("Entre com o nome do arquivo : ");
gets (nome);

ficheiro = open(nome, O_RDONLY);
if (ficheiro == -1){
  perror("Erro ao abrir");
  return 1;
}
else{
  close(ficheiro);

  printf("\nArquivo removido com sucesso\n", remove (nome));

  return 0;
}
}
