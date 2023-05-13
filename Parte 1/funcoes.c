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

void acrescentaFicheiro(const char *origem, const char *destino) {
    int fdOrigem, fdDestino;
    ssize_t bytesPorLeitura, bytesPorEscrita;
    char buffer[BUFFER_SIZE];

    // Abrir o ficheiro origem em modo de leitura
    fdOrigem = open(origem, O_RDONLY);
    if (fdOrigem == -1) {
        fprintf(stderr, "Erro ao abrir o ficheiro origem: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Abrir o ficheiro destino em modo de escrita com a flag O_APPEND
    fdDestino = open(destino, O_WRONLY | O_APPEND);
    if (fdDestino == -1) {
        fprintf(stderr, "Erro ao abrir o ficheiro destino: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Copiar o conteúdo do ficheiro origem para o ficheiro destino
    while ((bytesPorLeitura = read(fdOrigem, buffer, BUFFER_SIZE)) > 0) {
        bytesPorEscrita = write(fdDestino, buffer, bytesPorLeitura);
        if (bytesPorEscrita != bytesPorLeitura) {
            fprintf(stderr, "Erro ao escrever no ficheiro destino: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    if (bytesPorLeitura == -1) {
        fprintf(stderr, "Erro ao ler do ficheiro origem: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Fechar os descritores dos ficheiros
    if (close(fdOrigem) == -1) {
        fprintf(stderr, "Erro ao fechar o ficheiro origem: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (close(fdDestino) == -1) {
        fprintf(stderr, "Erro ao fechar o ficheiro destino: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("O ficheiro %s foi acrescentado ao ficheiro %s\n", origem, destino);
}

int contaFicheiro(char *ficheiro) {
    int fd, nr, linhas = 0;
    char buffer[BUFFER_SIZE];

    // Abrir o ficheiro para leitura
    fd = open(nome_ficheiro, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir ficheiro");
        exit(EXIT_FAILURE);
    }

    // Ler o conteúdo do ficheiro em blocos de tamanho BUFFER_SIZE
    while ((nr = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Percorrer o buffer e contar o número de linhas
        for (int i = 0; i < nr; i++) {
            if (buffer[i] == '\n') {
                linhas++;
            }
        }
    }

    // Verificar se ocorreu um erro na leitura
    if (nr == -1) {
        perror("Erro ao ler ficheiro");
        exit(EXIT_FAILURE);
    }

    // Fechar o ficheiro
    if (close(fd) == -1) {
        perror("Erro ao fechar ficheiro");
        exit(EXIT_FAILURE);
    }

    return linhas;
}

void removeFicheiro(const char *ficheiro) {
    int status = unlink(filename);
    if (status == -1) {
        perror("Erro a remover ficheiro");
    }
}