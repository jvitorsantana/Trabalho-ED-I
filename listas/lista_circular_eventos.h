#include "../estruturas/struct_evento.h"

#ifndef LISTA_CICULAR_EVENTOS_H
#define LISTA_CIRCULAR_EVENTOS_H

typedef struct listaeventos {
  Evento info;
  struct listaeventos *prox;
} ListaEventos;


ListaEventos* inicializar();
ListaEventos* inserirEvento(ListaEventos *lista, char nome[], char data[]);
void removeAux(ListaEventos **lista, ListaEventos *anterior, ListaEventos *atual);
ListaEventos* removerEvento(ListaEventos *lista, char nome[]);
void imprimirListaCircular(ListaEventos *lista);
void liberarListaCircular(ListaEventos *lista);
ListaEventos* buscarEvento(ListaEventos *lista, char nome[]);


#endif