#ifndef MOSTRAR_H
#define MOSTRAR_H
#define BUFFER_SIZE 1024

void mostraFicheiro(const char *ficheiro);
void copiaFicheiro(const char *ficheiro);
void acrescentaFicheiro(const char *origem, const char *destino);
int contaFicheiro(char *ficheiro);
void removeFicheiro(const char *ficheiro);
int informaFicheiro(char *filename);
int lista(char *dir_name);

#endif