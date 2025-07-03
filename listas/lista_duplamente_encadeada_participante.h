#include "estruturas/struct_participante.h"

#ifndef LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H
#define LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H

typedef struct ListaParticipante {
  Participante info;
  struct ListaParticipante *ant;
  struct ListaParticipante *prox;
} ListaParticipante;


#endif