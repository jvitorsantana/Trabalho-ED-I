// Inclusão das bibliotecas
#include "../estruturas/struct_evento.h"

#ifndef LISTA_CICULAR_EVENTOS_H
#define LISTA_CIRCULAR_EVENTOS_H

// Estrututa da lista circular de eventos
typedef struct ListaEventos {
  Evento info;
  struct ListaEventos *prox;
} ListaEventos;

// Protótipos das funções vinculadas a manipulação da lista de eventos
ListaEventos* inicializarListaEventos();
ListaEventos* inserirEvento(ListaEventos *lista, char nome[], char data[]);
void removerAux(ListaEventos **lista, ListaEventos *anterior, ListaEventos *atual);
ListaEventos* removerEvento(ListaEventos *lista, const char *nome);
void imprimirEventos(ListaEventos *lista);
void imprimirParticipantesEvento(Evento evento);
void liberarListaCircularEventos(ListaEventos *lista);
ListaEventos* buscarEvento(ListaEventos *lista, char nome[]);
int participanteCadastradoNoEvento(Evento *evento, char matriculaParticipante[]);
void realizarCheckIn(Evento *evento, char matriculaParticipante[]);

#endif