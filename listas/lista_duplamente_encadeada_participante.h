#include "../estruturas/struct_participante.h" 
#include "pilha_participante.h"

#include "estruturas/struct_participante.h"

#ifndef LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H
#define LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H

#include "struct_participante.h"

typedef struct ListaParticipante {
  Participante info;
  struct ListaParticipante *anterior;
  struct ListaParticipante *proximo;
  Participante info;
  struct ListaParticipante *ant;
  struct ListaParticipante *prox;
} ListaParticipante;

ListaParticipante *inicializarListaDuplamenteEncadeada();
ListaParticipante *criarParticipante(char matricula[], char nome[], char email[]);
int inserirParticipante(ListaParticipante **lista, ListaParticipante *novoParticipante);
void liberarListaParticipantes(ListaParticipante **lista);
int removerParticipante(ListaParticipante **lista, char matricula[], PilhaParticipante *pilha);
int desfazerRemocaoParticipante(ListaParticipante **lista, PilhaParticipante *pilha);
ListaParticipante *ordernarListaParticipantesPeloNome(ListaParticipante *lista);
void imprimirListaParticipantesOrdenada(ListaParticipante *lista);

#endif