#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_encadeada_atividade.h"
#include "lista_duplamente_encadeada_participante.h"
#include "pilha_atividade.h"

// Desfaz a última remoção de uma atividade, restaurando da pilha para a lista.
int desfazerRemocaoAtividade(ListaAtividade **lista, PilhaAtividade *pilha){
  if(pilha->topo == NULL){
    printf("Pilha vazia\n");
    return 0;
  }

  Atividade atividadeRestaurada;
  if(!desempilharAtividade(pilha, &atividadeRestaurada)){
    return 0;
  }

  ListaAtividade *novaAtividade = (ListaAtividade *) malloc(sizeof(ListaAtividade));
  
  if(novaAtividade == NULL){
    printf("Erro ao alocar memória para nova atividade\n");
    return 0;
  }

  ListaAtividade *atividadeBusca = buscarAtividade(*lista, atividadeRestaurada.titulo);

  if (atividadeBusca != NULL){
    printf("Atividade com título '%s' já existe na lista\n", atividadeRestaurada.titulo);
    free(novaAtividade);
    return 0;
  }
  
  novaAtividade->info = atividadeRestaurada;
  novaAtividade->prox = *lista;
  *lista = novaAtividade;
  printf("Atividade '%s' restaurada com sucesso.\n", atividadeRestaurada.titulo);
  return 1;
}

// Inicializa a lista de atividades como vazia (NULL).
ListaAtividade *inicializar(){
  return NULL;
}

// Insere uma nova atividade na lista, caso o título ainda não exista.
ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario) {
    ListaAtividade *busca = buscarAtividade(lista, titulo);
    if (busca != NULL) {
      printf("Atividade com título '%s' já existe.\n", titulo);
      return lista; // Retorna a lista sem alterações 
    }

    ListaAtividade *nova = (ListaAtividade *) malloc(sizeof(ListaAtividade));
    if (nova == NULL) {
      printf("Erro ao alocar memória para nova atividade.\n");
      return lista;
    }
    
    strcpy(nova->info.titulo, titulo);
    strcpy(nova->info.horario, horario);
    nova->info.participantes = NULL;
    nova->info.pilhaParticipantes = inicializarPilhaParticipantes();
    nova->prox = lista;
    printf("Atividade inserida com sucesso!\n");
    return nova;
}
      
// Remove uma atividade da lista e empilha para possível desfazer.
ListaAtividade *removerAtividade(ListaAtividade *lista, char *titulo, PilhaAtividade *pilhaDesfazerAtividade) {
  if (!pilhaDesfazerAtividade) {
    printf("Pilha de desfazer não inicializada!\n");
    return lista;
  }
  ListaAtividade *atual = lista;
  ListaAtividade *anterior = NULL;
  
  while(atual != NULL){
    if(strcasecmp(atual->info.titulo, titulo) == 0){
      break;
    }
    anterior = atual;
    atual = atual->prox; 
  }
  
  if(atual == NULL){
    printf("Atividade com título '%s' não encontrada.\n", titulo);
    return lista; 
  }
  
  empilharAtividade(pilhaDesfazerAtividade, atual->info); // Empilha a atividade removida
  
  if(anterior == NULL){
    lista = atual->prox; 
  }else{
    anterior->prox = atual->prox;
  }
  // Remove a atividade da lista mas não libera o nó Atividade, pois ela foi empilhada.
  free(atual);
  
  printf("Atividade '%s' removida com sucesso.\n", titulo);
  
  return lista;
}

// Libera toda a memória da lista de atividades, incluindo subestruturas.
void liberarAtividades(ListaAtividade *lista) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    if (atual->info.participantes != NULL) {
      liberarListaParticipantes(&atual->info.participantes);
    }
    if (atual->info.pilhaParticipantes != NULL) {
      liberarPilhaParticipante(atual->info.pilhaParticipantes);
    }
    
    ListaAtividade *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

// Busca uma atividade pelo título na lista. Retorna ponteiro ou NULL.
ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    if (strcasecmp(atual->info.titulo, titulo) == 0) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL; // Atividade não encontrada
}

// Ordena a lista de atividades com base no horário (bubble sort).
ListaAtividade *ordenarListaAtividadesPorHorario(ListaAtividade * lista) {
  if (lista == NULL || lista->prox == NULL)
    return lista; // já está ordenada

  int trocou;
  ListaAtividade *anterior, *atual, *proximo;
  do {
    trocou = 0;
    anterior = NULL;
    atual = lista;

    while (atual != NULL && atual->prox != NULL) {
      proximo = atual->prox;
      if (strcmp(atual->info.horario, proximo->info.horario) > 0) {
        if (anterior == NULL) {
          atual->prox = proximo->prox;
          proximo->prox = atual;
          lista = proximo;
          anterior = proximo;
        } else {
          anterior->prox = proximo;
          atual->prox = proximo->prox;
          proximo->prox = atual;
          anterior = proximo;
        }

        trocou = 1;
      } else {
        anterior = atual;
        atual = atual->prox;
      }
    }

  } while (trocou);

  return lista;
}

// Cria uma cópia da lista de atividades (sem duplicar participantes).
ListaAtividade* copiarListaAtividade(ListaAtividade* lista) {
    if (lista == NULL) return NULL;

    ListaAtividade *copia = NULL;
    ListaAtividade *ultimo = NULL;

    while (lista != NULL) {
        ListaAtividade* novo = (ListaAtividade*) malloc(sizeof(ListaAtividade));
        if (novo == NULL) {
            return NULL;
        }

        novo->info = lista->info;
        novo->prox = NULL;

        if (copia == NULL) {
            copia = novo;
        } else {
            ultimo->prox = novo;
        }

        ultimo = novo;
        lista = lista->prox;
    }

    return copia;
}

// Exibe todas as atividades ordenadas por horário (com título e horário).
void exibirAtividades(ListaAtividade *lista){
  ListaAtividade *copia = copiarListaAtividade(lista);
  ListaAtividade *resultado = ordenarListaAtividadesPorHorario(copia);

  if(resultado == NULL){
    printf("Nenhuma atividade cadastrada.\n");
    return;
  }

  ListaAtividade *atual = resultado;
  printf("Atividades cadastradas: \n");
  while (atual != NULL){
    printf("Título: %s, Horário: %s\n", atual->info.titulo, atual->info.horario);
    atual = atual->prox;
  }
  
  atual = resultado;
  while (atual != NULL) {
    ListaAtividade *temp = atual;
    atual = atual->prox;
    free(temp);
  }
}

// Exibe apenas os nomes das atividades, ordenadas por horário.
void exibirNomeAtividades(ListaAtividade *lista) {
  ListaAtividade *copia = copiarListaAtividade(lista);
  ListaAtividade *resultado = ordenarListaAtividadesPorHorario(copia);
  if(resultado == NULL){
    printf("Nenhuma atividade cadastrada.\n");
    return;
  }

  ListaAtividade *atual = resultado;
  while (atual != NULL){
    printf("- %s | Horario: %s\n", atual->info.titulo, atual->info.horario);
    atual = atual->prox;
  }

  atual = resultado;
  while (atual != NULL) {
    ListaAtividade *temp = atual;
    atual = atual->prox;
    free(temp);
  }
}