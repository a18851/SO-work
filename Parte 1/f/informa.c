#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Utilização: infoficheiro <nome_do_ficheiro>\n");
        exit(1);
    }
    
    struct stat info;
    if (stat(argv[1], &info) != 0) {
        fprintf(stderr, "Erro ao obter informação do ficheiro.\n");
        exit(1);
    }

    char *tipo_ficheiro;
    switch (info.st_mode & S_IFMT) {
        case S_IFREG:
            tipo_ficheiro = "ficheiro normal";
            break;
        case S_IFDIR:
            tipo_ficheiro = "diretoria";
            break;
        case S_IFLNK:
            tipo_ficheiro = "link simbólico";
            break;
        default:
            tipo_ficheiro = "tipo desconhecido";
            break;
    }

    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);

    printf("Tipo de ficheiro: %s\n", tipo_ficheiro);
    printf("Número do i-node: %lu\n", info.st_ino);
    printf("Utilizador dono: %s (%d)\n", pw->pw_name, info.st_uid);
    printf("Grupo dono: %s (%d)\n", gr->gr_name, info.st_gid);
    printf("Data de criação: %s", ctime(&info.st_ctime));
    printf("Data de modificação: %s", ctime(&info.st_mtime));
    printf("Data de acesso: %s", ctime(&info.st_atime));

    return 0;
}

