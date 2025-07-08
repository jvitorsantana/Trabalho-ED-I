#include "lista_duplamente_encadeada_participante.h"
#include "../estruturas/struct_atividade.h"
#include "pilha_atividade.h"

// Evita que o conteúdo do cabeçalho seja incluído mais de uma vez no mesmo arquivo
#ifndef LISTA_ENCADEADA_ATIVIDADES_H
#define LISTA_ENCADEADA_ATIVIDADES_H

// Estrutura da lista encadeada de atividades
typedef struct ListaAtividade {
    struct Atividade info;
    struct ListaAtividade *prox;
} ListaAtividade;

// Inicializa uma lista de atividades
ListaAtividade *inicializar();
// Insere uma nova atividade na lista 
ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario);
// Remove uma atividade da lista com base no título, salvando a atividade removida na pilha de desfazer
ListaAtividade *removerAtividade(ListaAtividade *lista, char *titulo, PilhaAtividade *pilhaDesfazerAtividade);
// Libera toda a memória da lista encadeada de atividades
void liberarAtividades(ListaAtividade *lista);
// Busca uma atividade na lista pelo título (retorna ponteiro para o nó)
ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo);
// Cria uma cópia da lista de atividades
ListaAtividade *copiarListaAtividade(ListaAtividade *lista);
// Ordena a lista de atividades pelo campo `horario`
ListaAtividade *ordenarListaAtividadesPorHorario(ListaAtividade *lista);
// Exibe todas as informações das atividades da lista
void exibirAtividades(ListaAtividade *lista);
// Exibe apenas os nomes das atividades e seus horários
void exibirNomeAtividades(ListaAtividade *lista);
// Verifica se o horário tem um formato válido (por exemplo, "HH:MM")
int validarHorario(char *horario);
// Desfaz uma remoção de atividade usando a pilha (reinsere a atividade removida)
int desfazerRemocaoAtividade(ListaAtividade **lista, PilhaAtividade *pilha);

// Fim da diretiva de inclusão condicional
#endif