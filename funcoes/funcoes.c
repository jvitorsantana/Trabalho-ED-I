#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"

void limparTerminal() {
  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #else
    printf("\033[H\033[2J");
    fflush(stdout);
  #endif
}

void pausarTerminal() {
  printf("\nPressione ENTER para continuar...\n");
  char c;
  while((c = getchar()) != '\n' && c != EOF) {}
  getchar();
}

void limparBuffer() {
  fflush(stdin);
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

char *digitarNomeEvento() {
  char *nome = (char*) malloc(sizeof(char) * 100);
  
  printf("Digite o nome do evento: ");
  scanf("%50[^\n]", nome);
  limparBuffer();

  return nome;
}

char *digitarDataEvento() {
  char *data = (char *)malloc(sizeof(char) * 10);
  if (data == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite a data do evento: ");
  scanf("%10s", data);
  limparBuffer();

  return data;
}

char *digitarNomeAtividade() {
  char *nome = (char *)malloc(sizeof(char) * 100);
  if (nome == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite o nome da atividade: ");
  scanf("%50[^\n]", nome);
  limparBuffer();

  return nome;
}

char *digitarHorarioAtividade() {
  char *horario = (char *)malloc(sizeof(char) * 10);
  if (horario == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite o horario da atividade: ");
  scanf("%9[^\n]", horario);
  limparBuffer();

  return horario;
}

char *digitarNomeParticipante() {
  char *nome = (char *)malloc(sizeof(char) * 50);
  if (nome == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite o nome do participante: ");
  scanf("%50[^\n]", nome);
  limparBuffer();

  return nome;
}

char *digitarEmailParticipante() {
  char *email = (char *)malloc(sizeof(char) * 50);
  if (email == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite o e-mail do participante: ");
  scanf("%50[^\n]", email);
  limparBuffer();

  return email;
}

char *digitarMatriculaParticipante() {
  char *matricula = (char *)malloc(sizeof(char) * 25);
  if (matricula == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite a matricula do participante: ");
  scanf("%25[^\n]", matricula);
  limparBuffer();

  return matricula;
}