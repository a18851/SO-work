#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void mostraFicheiro(const char *ficheiro) {
    int fd;                             // variável para o descritor de ficheiro
    ssize_t bytesPorLeitura;            // variável para o número de bytes lidos
    char buffer[BUFFER_SIZE];           // buffer para armazenar os dados lidos

    fd = open(ficheiro, O_RDONLY);      // abre o ficheiro apenas para leitura
    if (fd == -1) {                     // verifica se houve erro na abertura do ficheiro
        perror("open");                 // exibe mensagem de erro padrão para o último erro ocorrido
        exit(EXIT_FAILURE);             // encerra o programa com falha
    }

    while ((bytesPorLeitura = read(fd, buffer, BUFFER_SIZE)) > 0) {  // lê o arquivo até o final
        if (write(STDOUT_FILENO, buffer, bytesPorLeitura) != bytesPorLeitura) {  // escreve os dados lidos no stdout
            fprintf(stderr, "Erro ao escrever no ecrã\n");  // exibe mensagem de erro caso ocorra
            exit(EXIT_FAILURE);                             // encerra o programa com falha
        }
    }

    if (bytesPorLeitura == -1) {        // verifica se houve erro na leitura do arquivo
        perror("read");                 // exibe mensagem de erro padrão para o último erro ocorrido
        exit(EXIT_FAILURE);             // encerra o programa com falha
    }

    if (close(fd) == -1) {              // fecha o arquivo
        perror("close");                // exibe mensagem de erro padrão para o último erro ocorrido
        exit(EXIT_FAILURE);             // encerra o programa com falha
    }
}



