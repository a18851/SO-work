#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>


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
    fd = open(ficheiro, O_RDONLY);
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
    int status = unlink(ficheiro);
    if (status == -1) {
        perror("Erro a remover ficheiro");
    }
}

int informaFicheiro(char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        fprintf(stderr, "Erro ao obter informações do arquivo: %s\n", strerror(errno));
        return 1;
    }


    char *file_type;
    if (S_ISREG(file_stat.st_mode)) {
        file_type = "Arquivo regular";
    } else if (S_ISDIR(file_stat.st_mode)) {
        file_type = "Diretório";
    } else if (S_ISLNK(file_stat.st_mode)) {
        file_type = "Link simbólico";
    } else {
        file_type = "Tipo de arquivo desconhecido";
    }

    struct passwd *pw = getpwuid(file_stat.st_uid);
    if (pw == NULL) {
        fprintf(stderr, "Erro ao obter informações do dono do arquivo: %s\n", strerror(errno));
        return 1;
    }

    char created_time[20], modified_time[20], accessed_time[20];
    strftime(created_time, sizeof(created_time), "%b %d %Y %H:%M:%S", localtime(&file_stat.st_ctime));
    strftime(modified_time, sizeof(modified_time), "%b %d %Y %H:%M:%S", localtime(&file_stat.st_mtime));
    strftime(accessed_time, sizeof(accessed_time), "%b %d %Y %H:%M:%S", localtime(&file_stat.st_atime));

    printf("%s:\n", filename);
    printf("Tipo: %s\n", file_type);
    printf("Número I-node: %ld\n", (long) file_stat.st_ino);
    printf("Dono: %s\n", pw->pw_name);
    printf("Criado em: %s\n", created_time);
    printf("Última modificação: %s\n", modified_time);
    printf("Último acesso: %s\n", accessed_time);

    return 0;
}

int lista(char *dir_name) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        fprintf(stderr, "Erro ao abrir diretoria: %s\n", strerror(errno));
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        struct stat file_stat;
        if (stat(path, &file_stat) == -1) {
            fprintf(stderr, "Erro ao obter informações do arquivo: %s\n", strerror(errno));
            return 1;
        }

        if (S_ISDIR(file_stat.st_mode)) {
            printf("%s [Pasta]\n", entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    if (closedir(dir) == -1) {
        fprintf(stderr, "Erro ao fechar diretoria: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}