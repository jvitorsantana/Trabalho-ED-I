#include "../listas/lista_encadeada_atividade.h"

#ifndef STRUCT_EVENTO_H
#define STRUCT_EVENTO_H

typedef struct Evento {
  char nome[51];
  char data[11];
  struct ListaAtividade *atividades;
}Evento;

#endif