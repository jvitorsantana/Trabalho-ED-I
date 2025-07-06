#include "../estruturas/struct_participante.h" 

#ifndef PILHA_PARTICIPANTE_H
#define PILHA_PARTICIPANTE_H


typedef struct NoParticipante{
    Participante info;
    struct NoParticipante *proximo;
} NoParticipante;

typedef struct PilhaParticipante{
    struct NoParticipante *topo;
} PilhaParticipante;


PilhaParticipante *inicializarPilhaParticipantes();
int empilharParticipante(PilhaParticipante *pilha, Participante Participante);
int desempilharParticipante(PilhaParticipante *pilha, Participante *destino);
void liberarPilhaParticipante(PilhaParticipante *pilha);

#endif