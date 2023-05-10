#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int conta_ficheiro(char* nome_ficheiro) {
    int fd = open(nome_ficheiro, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Erro ao abrir ficheiro %s\n", nome_ficheiro);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int num_linhas = 1;
    int num_bytes_lidos = 0;
    int i;

    while ((num_bytes_lidos = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (i = 0; i < num_bytes_lidos; i++) {
            if (buffer[i] == '\n') {
                num_linhas++;
            }
        }
    }

    if (num_bytes_lidos == -1) {
        fprintf(stderr, "Erro ao ler ficheiro %s\n", nome_ficheiro);
        exit(1);
    }

    close(fd);

    return num_linhas;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Sintaxe inválida. Utilize: conta_ficheiro <nome_do_ficheiro>\n");
        exit(1);
    }

    char* nome_ficheiro = argv[1];
    int num_linhas = conta_ficheiro(nome_ficheiro);

    printf("O ficheiro %s tem %d linhas\n", nome_ficheiro, num_linhas);

    return 0;
}
