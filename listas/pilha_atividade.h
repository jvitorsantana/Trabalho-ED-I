#ifndef PILHA_ATIVIDADE_H
#define PILHA_ATIVIDADE_H

#include "../listas/lista_encadeada_atividade.h"

typedef struct PilhaAtividade{
  struct ListaAtividade *topo;
} PilhaAtividade;

PilhaAtividade *inicializarPilhaAtividades();
int empilharAtividade(PilhaAtividade *pilha, Atividade *atividade);
int desempilharAtividade(PilhaAtividade *pilha, Atividade **destino);
void liberarPilhaAtividades(PilhaAtividade *pilha);

#endif