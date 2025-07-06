#ifndef PILHA_ATIVIDADE_H
#define PILHA_ATIVIDADE_H
#include "../estruturas/struct_atividade.h"
// Forward declaration para evitar dependência circular
struct ListaAtividade;
typedef struct ListaAtividade ListaAtividade;

// Estrutura da pilha de atividades
// Cada nó da pilha será um ListaAtividade, mas só o campo info será usado
// para guardar uma cópia da Atividade

typedef struct PilhaAtividade {
    ListaAtividade *topo;
} PilhaAtividade;

PilhaAtividade *inicializarPilhaAtividades();
int empilharAtividade(PilhaAtividade *pilha, Atividade atividade);
int desempilharAtividade(PilhaAtividade *pilha, Atividade *destino);
void liberarPilhaAtividades(PilhaAtividade *pilha);

#endif
