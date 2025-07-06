#include "../listas/lista_encadeada_atividade.h"
#include "../listas/fila_check_in.h"

#ifndef STRUCT_EVENTO_H
#define STRUCT_EVENTO_H

typedef struct Evento {
  char nome[51];
  char data[11];
  ListaAtividade *atividades;
  FilaCheckIn *filaCheckIn;
  PilhaAtividade *pilhaAtividades;
}Evento;

#endif