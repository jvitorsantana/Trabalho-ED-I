#include "../listas/lista_duplamente_encadeada_participante.h"
#include "../listas/pilha_participante.h"

#ifndef STRUCT_ATIVIDADE_H
#define STRUCT_ATIVIDADE_H

typedef struct Atividade { // Estrutura que representa uma atividade.
  char titulo[51];
  char horario[10];
  struct ListaParticipante *participantes;
  struct PilhaParticipante *pilhaParticipantes;
} Atividade;

#endif