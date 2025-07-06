#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int validarHorario(char *horario) {
  if(strlen(horario) != 5 || horario[2] != ':') { // se o tamanho não for 5 ou o terceiro caractere não for ':'
    return 0; 
  }
  if(isdigit(horario[0]) && isdigit(horario[1]) && isdigit(horario[3]) && isdigit(horario[4])) { // "HH:MM", verifica se os caracteres numeros
    
    int horas = (horario[0] - '0') * 10 + (horario[1] - '0'); 
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');
    // Converte os caracteres para inteiros com ASCII, 
    // onde '0' é subtraído para obter o valor numérico, pois '0' tem o valor ASCII 48, '1' tem 49, '2' tem 50...

    if(horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60) {
      return 1; 
    }
  }
  return 0; 
}