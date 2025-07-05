#include "../estruturas/struct_atividade.h"
#include "lista_duplamente_encadeada_participante.h"

#ifndef LISTA_ENCADEADA_ATIVIDADES_H
#define LISTA_ENCADEADA_ATIVIDADES_H

typedef struct ListaAtividade {
    struct Atividade info;
    struct ListaAtividade *prox;
    struct ListaParticipante *participantes;
    struct PilhaParticipante *pilhaParticipantes;
} ListaAtividade;

ListaAtividade *inicializar();
ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario);
ListaAtividade *removerAtividade(ListaAtividade *lista, char *nome);
void liberarAtividades(ListaAtividade *lista);
ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo);
ListaAtividade *copiarListaAtividade(ListaAtividade *lista);
ListaAtividade *ordenarListaAtividadesPorHorario(ListaAtividade *lista);
void exibirAtividades(ListaAtividade *lista);

#endif