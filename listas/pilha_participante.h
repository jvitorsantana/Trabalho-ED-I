#ifndef PILHA_PARTICIPANTE_H
#include "estruturas/struct_participante.h" 
#define PILHA_PARTICIPANTE_H


typedef struct NoParticipante{
    Participante info;
    struct NoParticipante *proximo;
} NoParticipante;

typedef struct PilhaParticipante{
    struct NoParticipante *topo;
} PilhaParticipante;


// void 

#endif