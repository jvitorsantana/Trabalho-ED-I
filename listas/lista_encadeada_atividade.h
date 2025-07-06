#include "../estruturas/struct_atividade.h"
#include "lista_duplamente_encadeada_participante.h"

#ifndef LISTA_ENCADEADA_ATIVIDADES_H
#define LISTA_ENCADEADA_ATIVIDADES_H

// Forward declaration para evitar dependência circular

struct PilhaAtividade;
typedef struct PilhaAtividade PilhaAtividade;

// // // // // // // // // // // // // // // // // // //

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
int validarHorario(char *horario);
int desfazerRemocaoAtividade(ListaAtividade **lista, PilhaAtividade *pilha);

#endif