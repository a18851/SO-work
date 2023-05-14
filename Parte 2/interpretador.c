#include <stdio.h> // Para printf() e fgets()
#include <string.h> // Para strtok() e strcmp()
#include <stdlib.h> // Para exit()
#include <unistd.h> // Para fork() e execvp()
#include <sys/wait.h> // Para wait()

#define MAX_CMD_LEN 128 // Comprimento máximo do comando
#define MAX_NUM_ARGS 10 // Número máximo de argumentos

int main() {
    char cmd[MAX_CMD_LEN + 1]; // +1 para o caractere nulo
    char* args[MAX_NUM_ARGS + 1]; // +1 para o argumento nulo necessário para execvp()

    while(1) {
        printf("% "); // Mostra o símbolo do interpretador

        // Lê o comando do usuário
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) {
            printf("\n");
            exit(0);
        }

        // Remove o '\n' do final
        cmd[strcspn(cmd, "\n")] = 0;

        // Divide o comando em argumentos
        int i = 0;
        args[i] = strtok(cmd, " ");
        while(args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // Se o comando for "termina", termina o interpretador
        if(strcmp(args[0], "termina") == 0) {
            break;
        }

        // Cria um novo processo para executar o comando
        pid_t pid = fork();
        if(pid == 0) { 
            // Substitui o comando "criar", "apagar", "editar" e "listar" pelos comandos equivalentes do Linux
            if(strcmp(args[0], "cria") == 0) {
                args[0] = "mkdir";
            } else if(strcmp(args[0], "apaga") == 0) {
                args[0] = "rm";
            } else if(strcmp(args[0], "edita") == 0) {
                args[0] = "nano";
            } else if(strcmp(args[0], "lista") == 0) {
                args[0] = "ls";
            }

            // Executa o comando
            execvp(args[0], args);

            // Se chegarmos aqui, houve um erro na execução do comando
            perror("execvp");
            exit(1);
        } else if(pid > 0) { 
            // Espera o processo anteriror terminar e mostra o código de terminação
            int status;
            waitpid(pid, &status, 0);
            printf("Terminou comando %s com código %d\n", args[0], WEXITSTATUS(status));
        } else { // Erro
            perror("fork");
            exit(1);
        }
    }

    return 0;
}