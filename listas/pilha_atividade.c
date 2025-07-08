#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_atividade.h"

PilhaAtividade *inicializarPilhaAtividades() {
  PilhaAtividade *pilha = (PilhaAtividade *) malloc(sizeof(PilhaAtividade));
  if (pilha == NULL) {
    printf("Erro ao alocar memória para a pilha de atividades.\n");
    exit(1);
  }
  pilha->topo = NULL;
  return pilha;
}

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