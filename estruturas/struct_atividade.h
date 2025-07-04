#include "../listas/lista_duplamente_encadeada_participante.h"

#ifndef STRUCT_ATIVIDADE_H
#define STRUCT_ATIVIDADE_H

typedef struct Atividade {
  char titulo[100];
  char horario[10];
  struct ListaParticipante *participantes;
} Atividade;

#endif