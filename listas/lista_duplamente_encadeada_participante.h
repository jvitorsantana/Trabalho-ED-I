#ifndef LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H
#include "estruturas/struct_participante.h" 
#define LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H

typedef struct ListaParticipante {
  Participante info;
  struct ListaParticipante *anterior;
  struct ListaParticipante *proximo;
} ListaParticipante;

// void 

#endif