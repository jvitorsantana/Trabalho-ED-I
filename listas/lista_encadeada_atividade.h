#include "../estruturas/struct_atividade.h"

#ifndef LISTA_ENCADEADA_ATIVIDADES_H
#define LISTA_ENCADEADA_ATIVIDADES_H

typedef struct ListaAtividade {
    Atividade *info;
    struct ListaAtividade *prox;
} ListaAtividade;

ListaAtividade *inicializar();
ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario);
ListaAtividade *removerAtividade(ListaAtividade *lista, char *nome);
void exibirAtividades(ListaAtividade *lista);
void liberarAtividades(ListaAtividade *lista);
ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo);
ListaAtividade *ordenarListaAtividadesPorHorario(ListaAtividade *lista);

#endif