#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"

char *digitarNomeEvento() {
  char *nome = (char*) malloc(sizeof(char) * 100);
  
  printf("Digite o nome do evento: ");
  scanf("%99[^\n]", nome);

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
  scanf("%9s", data);

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
  scanf("%99[^\n]", nome);

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

  return horario;
}