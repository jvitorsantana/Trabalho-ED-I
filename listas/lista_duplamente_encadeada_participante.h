#include "pilha_participante.h"
#include "fila_check_in.h"
#include "../estruturas/struct_participante.h" 

#ifndef LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H
#define LISTA_DUPLAMENTE_ENCADEADA_PARTICIPANTE_H


typedef struct ListaParticipante { // Lista duplamente encadeada de participantes
  Participante info; // Estrutura do participante.
  struct ListaParticipante *anterior;
  struct ListaParticipante *proximo;
} ListaParticipante;

// Protótipos das funções para manipulação da lista de participantes.
ListaParticipante *inicializarListaParticipantes();
ListaParticipante *criarParticipante(char matricula[], char nome[], char email[]);
int existeParticipante(ListaParticipante *lista, char matriculaParticipante[]);
int inserirParticipante(ListaParticipante **lista, ListaParticipante *novoParticipante);
void liberarListaParticipantes(ListaParticipante **lista);
int removerParticipante(ListaParticipante **lista, char matricula[], PilhaParticipante *pilha, FilaCheckIn** fila);
int desfazerRemocaoParticipante(ListaParticipante **lista, PilhaParticipante *pilha);
ListaParticipante *ordernarListaParticipantesPeloNome(ListaParticipante *lista);
void imprimirListaParticipantesOrdenada(ListaParticipante *lista);

#endif 