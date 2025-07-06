#include "../estruturas/struct_atividade.h"

#ifndef PILHA_ATIVIDADE_H
#define PILHA_ATIVIDADE_H

typedef struct NoPilhaAtividade {
    Atividade info;
    struct NoPilhaAtividade *proximo;
} NoPilhaAtividade;

typedef struct PilhaAtividade {
    NoPilhaAtividade *topo;
} PilhaAtividade;

PilhaAtividade *inicializarPilhaAtividades();
int empilharAtividade(PilhaAtividade *pilha, Atividade atividade);
int desempilharAtividade(PilhaAtividade *pilha, Atividade *destino);
void liberarPilhaAtividades(PilhaAtividade *pilha);

#endif
