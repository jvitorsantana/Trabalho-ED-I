#include "../estruturas/struct_atividade.h"

// Evita que o conteúdo do cabeçalho seja incluído mais de uma vez no mesmo arquivo
#ifndef PILHA_ATIVIDADE_H
#define PILHA_ATIVIDADE_H

// Define a estrutura de um nó da pilha de atividades
typedef struct NoPilhaAtividade {
    Atividade info;
    struct NoPilhaAtividade *proximo;
} NoPilhaAtividade;

// Define a estrutura da pilha de atividades
typedef struct PilhaAtividade {
    NoPilhaAtividade *topo;
} PilhaAtividade;

// Inicializa uma nova pilha vazia de atividades
PilhaAtividade *inicializarPilhaAtividades();
// Insere uma nova atividade no topo da pilha
int empilharAtividade(PilhaAtividade *pilha, Atividade atividade);
// Remove a atividade do topo da pilha e armazena seu conteúdo em `destino`
int desempilharAtividade(PilhaAtividade *pilha, Atividade *destino);
// Libera toda a memória alocada pela pilha e seus nós
void liberarPilhaAtividades(PilhaAtividade *pilha);

// Fim da diretiva de inclusão condicional
#endif
