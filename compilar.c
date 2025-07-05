#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Compilando...\n");
  system("gcc -o programa main.c listas/lista_circular_eventos.c listas/lista_duplamente_encadeada_participante.c listas/lista_encadeada_atividade.c listas/fila_check_in.c funcoes/funcoes.c");
  system("./programa");

  return 0;
}