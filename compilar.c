#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Compilando...\n");
  system("gcc listas/lista_circular_eventos.c listas/lista_duplamente_encadeada_participante.c listas/lista_encadeada_atividade.c funcoes/funcoes.c main.c -o programa");
  system("./programa");

  return 0;
}