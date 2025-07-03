#include "../estruturas/struct_evento.h"

#ifndef LISTA_CICULAR_EVENTOS_H
#define LISTA_CIRCULAR_EVENTOS_H

typedef struct listaeventos {
  Evento info;
  struct listaeventos *prox;
} ListaEventos;

ListaEventos* inicializar();

ListaEventos* inserir_evento(ListaEventos *lista, const char *nome, const char *data);
void remove_aux(ListaEventos **lista, ListaEventos *anterior, ListaEventos *atual);
ListaEventos* remover_evento(ListaEventos *lista, const char *nome);
void imprimir_lista_circular(ListaEventos *lista);
void liberar_lista_circular(ListaEventos *lista);
ListaEventos* buscar_evento(ListaEventos *lista, const char *nome);


#endif