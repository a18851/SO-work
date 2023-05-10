#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{

  char nome[50], atime[50], mtime[50], ctime[50];
  struct stat buf;

  stat("teste.txt", &buf);
  printf("i-node= %d\n", buf.st_ino);
  //strcpy(st_uid, nome)
  printf("nome do utilizador dono: %d\n", buf.st_uid);
  strcpy(mtime, time(&buf.st_mtime));
  strcpy(atime, time(&buf.st_atime));
  strcpy(ctime, time(&buf.st_ctime));

  printf("ultimo acesso: %d\n", atime);
  printf("ultima modificacao: %d\n", mtime);
  printf("data de criacao= %d\n", ctime);
  return 0;
}
