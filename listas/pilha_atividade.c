#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_atividade.h"

// Inicializa uma nova pilha de atividades, com topo igual a NULL.
PilhaAtividade *inicializarPilhaAtividades() {
  PilhaAtividade *pilha = (PilhaAtividade *) malloc(sizeof(PilhaAtividade));
  if (pilha == NULL) {
    printf("Erro ao alocar memória para a pilha de atividades.\n");
    exit(1);
  }
  pilha->topo = NULL;
  return pilha;
}

// Empilha uma nova atividade no topo da pilha.
int empilharAtividade(PilhaAtividade *pilha, Atividade atividade){
  NoPilhaAtividade *novoNo = (NoPilhaAtividade *) malloc(sizeof(NoPilhaAtividade));
  if (novoNo == NULL) {
    return 0;
  }
  novoNo->info = atividade;
  novoNo->proximo = pilha->topo;
  pilha->topo = novoNo;
  return 1;
}

// Desempilha a atividade do topo e armazena seus dados no destino.
int desempilharAtividade(PilhaAtividade *pilha, Atividade *destino) {
  if (pilha->topo == NULL) {
    return 0; // Pilha vazia
  }

  NoPilhaAtividade *temp = pilha->topo;
  *destino = temp->info; 
  pilha->topo = temp->proximo; 
  free(temp);
  return 1;
}

// Libera toda a memória alocada para a pilha e seus elementos.
void liberarPilhaAtividades(PilhaAtividade *pilha) {
  NoPilhaAtividade *atual = pilha->topo;
  if (atual != NULL) {
    while (atual != NULL) {
      NoPilhaAtividade *temp = pilha->topo;
      if (temp->info.participantes != NULL) {
        liberarListaParticipantes(&temp->info.participantes);
      }
      if (temp->info.pilhaParticipantes != NULL) {
        liberarPilhaParticipante(temp->info.pilhaParticipantes);
      }
      atual = temp->proximo;
      free(temp);
    }
  }
  free(pilha);
}