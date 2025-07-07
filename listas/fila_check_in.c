#include "fila_check_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FilaCheckIn *criarFila() {
  FilaCheckIn *fila = (FilaCheckIn *) malloc(sizeof(FilaCheckIn));
  fila->inicio = NULL;
  fila->fim = NULL;

  return fila;
}

void liberarFila(FilaCheckIn *fila) {
  NoFilaCheckIn *atual = fila->inicio;
  while (atual != NULL) {
    NoFilaCheckIn *temp = atual->proximo;
    free(atual);
    atual = temp;
  }
  free(fila);
}

void inserirFila(FilaCheckIn *fila, char matriculaParticipante[]) {
  NoFilaCheckIn *novo_no = (NoFilaCheckIn *)malloc(sizeof(NoFilaCheckIn));

  strncpy(novo_no->matriculaParticipante, matriculaParticipante, sizeof(novo_no->matriculaParticipante) - 1);
  novo_no->matriculaParticipante[sizeof(novo_no->matriculaParticipante) - 1] = '\0';
  novo_no->proximo = NULL;

  if (filaVazia(fila)) {
    fila->inicio = novo_no;
  } else {
    fila->fim->proximo = novo_no;
  }

  fila->fim = novo_no;
}

int filaVazia(FilaCheckIn *fila) {
  return fila->fim == NULL;
}

int existeNaFila(FilaCheckIn *fila, char matriculaParticipante[]) {
  int existe = 0;

  if (filaVazia(fila)) {
    return existe;
  }

  NoFilaCheckIn *atual = fila->inicio;
  while (atual != NULL) {
    if (strcasecmp(atual->matriculaParticipante, matriculaParticipante) == 0) {
      existe = 1;
      return existe;
    }
    atual = atual->proximo;
  }

  return existe;
}

int posicaoNaFila(FilaCheckIn *fila, char matriculaParticipante[]) {
  int posicao = 1;

  if (filaVazia(fila)) {
    posicao = -1;
    return posicao;
  }

  NoFilaCheckIn *atual = fila->inicio;
  while (atual != NULL) {
    if (strcasecmp(atual->matriculaParticipante, matriculaParticipante) == 0) {
      return posicao;
    }
    posicao++;
    atual = atual->proximo;
  }

  posicao = -1;
  return posicao;
}

void imprimirFila(FilaCheckIn *fila) {
  if (filaVazia(fila)) {
    printf("Ninguem fez o check-in ainda");
    return;
  }
  NoFilaCheckIn *atual = fila->inicio;
  int pos = 1;
  while (atual != NULL) {
    printf("%d. %s\n", pos, atual->matriculaParticipante);
    atual = atual->proximo;
    pos++;
  }
  printf("\n");
}

int removerFila(FilaCheckIn* fila, char matriculaParticipante[]){
  if (fila == NULL || fila->inicio == NULL){
    return 0; 
  }
  
  NoFilaCheckIn* atual = fila->inicio;
  NoFilaCheckIn* anterior = NULL;

  while (atual != NULL){
    if (strcasecmp(atual->matriculaParticipante, matriculaParticipante) == 0){
      if (anterior == NULL){
        fila->inicio = atual->proximo;
        if (fila->fim == atual){
          fila->fim = NULL;
        }
      } else{
        anterior->proximo = atual->proximo;
        if (fila->fim == atual){
          fila->fim = anterior;
        }
      }
      free(atual);
      return 1;
    }
    anterior = atual;
    atual = atual->proximo;
  }
  return 0;
}