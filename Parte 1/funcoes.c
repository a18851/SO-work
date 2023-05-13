#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

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

void copiaFicheiro(const char *ficheiro) {
    int fdIn, fdOut;
    ssize_t bytesPorLeitura, bytesPorEscrita;
    char buffer[BUFFER_SIZE];
    char nomeCopia[PATH_MAX];

    // Abrir o ficheiro original em modo de leitura
    fdIn = open(ficheiro, O_RDONLY);
    if (fdIn == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Gerar o nome do ficheiro cópia adicionando ".copia" ao nome original
    snprintf(nomeCopia, PATH_MAX, "%s.copia", ficheiro);

    // Criar o ficheiro cópia em modo de escrita
    fdOut = open(nomeCopia, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fdOut == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Copiar o conteúdo do ficheiro original para o ficheiro cópia
    while ((bytesPorLeitura = read(fdIn, buffer, BUFFER_SIZE)) > 0) {
        bytesPorEscrita = write(fdOut, buffer, bytesPorLeitura);
        if (bytesPorEscrita != bytesPorLeitura) {
            fprintf(stderr, "Erro ao escrever no ficheiro cópia\n");
            exit(EXIT_FAILURE);
        }
    }

    if (bytesPorLeitura == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Fechar os descritores dos ficheiros
    if (close(fdIn) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (close(fdOut) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    printf("O ficheiro %s foi copiado para %s\n", ficheiro, nomeCopia);
}


