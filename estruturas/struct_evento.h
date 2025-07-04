#ifndef STRUCT_EVENTO_H
#define STRUCT_EVENTO_H

#include "../listas/lista_encadeada_atividade.h"

typedef struct Evento {
  char nome[50];
  char data[10];
  struct ListaAtividade* atividades;
}Evento;

#endif