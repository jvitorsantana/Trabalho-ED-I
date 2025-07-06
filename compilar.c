#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
#endif

int main() {
  printf("Compilando...\n");
  int resultado;
  #if defined(_WIN32) || defined(_WIN64)
    resultado = system("gcc -o programa.exe -Wall -Wextra -finput-charset=UTF-8 main.c listas/lista_circular_eventos.c listas/lista_duplamente_encadeada_participante.c listas/lista_encadeada_atividade.c listas/fila_check_in.c funcoes/funcoes.c");
    if (resultado) {
      printf("\nErro na compilacao!\n");
    } else {
      SetConsoleOutputCP(CP_UTF8); // gambiarra para mostrar os simbolos no terminal windows, se ainda persistir, executa chcp 65001.
      system("programa.exe");
    }
  #else
    resultado = system("gcc -o programa -Wall -Wextra -finput-charset=UTF-8 main.c listas/lista_circular_eventos.c listas/lista_duplamente_encadeada_participante.c listas/lista_encadeada_atividade.c listas/fila_check_in.c funcoes/funcoes.c");
    if (resultado) {
      printf("\nErro na compilacao!\n");
    } else {
      system("./programa");
    }
  #endif

  return 0;
}