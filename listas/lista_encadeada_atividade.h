#include "lista_duplamente_encadeada_participante.h"
#include "../estruturas/struct_atividade.h"
#include "pilha_atividade.h"

#ifndef LISTA_ENCADEADA_ATIVIDADES_H
#define LISTA_ENCADEADA_ATIVIDADES_H

typedef struct ListaAtividade {
    struct Atividade info;
    struct ListaAtividade *prox;
} ListaAtividade;

ListaAtividade *inicializar();
ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario);
ListaAtividade *removerAtividade(ListaAtividade *lista, char *titulo, PilhaAtividade *pilhaDesfazerAtividade);
void liberarAtividades(ListaAtividade *lista);
ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo);
ListaAtividade *copiarListaAtividade(ListaAtividade *lista);
ListaAtividade *ordenarListaAtividadesPorHorario(ListaAtividade *lista);
void exibirAtividades(ListaAtividade *lista);
void exibirNomeAtividades(ListaAtividade *lista);
int validarHorario(char *horario);
int desfazerRemocaoAtividade(ListaAtividade **lista, PilhaAtividade *pilha);

#endif