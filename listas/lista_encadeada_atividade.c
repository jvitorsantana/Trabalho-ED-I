#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_encadeada_atividade.h"

ListaAtividade *inicializar(){
  return NULL;
}

ListaAtividade *inserirAtividade(ListaAtividade *lista, char *titulo, char *horario) {
    ListaAtividade *busca = buscarAtividade(lista, titulo);
    if (busca != NULL) {
      printf("Atividade com título '%s' já existe.\n", titulo);
      return lista; // Retorna a lista sem alterações 
    }
    ListaAtividade *nova = (ListaAtividade *)malloc(sizeof(ListaAtividade));
    if (nova == NULL) {
      printf("Erro ao alocar memória para nova atividade.\n");
      return lista;
    }

    nova->info = (Atividade *) malloc(sizeof(Atividade));
    if (nova->info == NULL) {
      printf("Erro ao alocar memória para informações da atividade.\n");
      free(nova);
      return lista;
    }

    strcpy(nova->info->titulo, titulo);
    strcpy(nova->info->horario, horario);
    nova->prox = lista;
    return nova;
}
      

ListaAtividade *removerAtividade(ListaAtividade *lista, char *titulo){
  ListaAtividade *atual = lista;
  ListaAtividade *anterior = NULL;
  
  while(atual != NULL){
    if(strcmp(atual->info->titulo, titulo) == 0){
      break;
    }
    anterior = atual;
    atual = atual->prox; 
  }

  if(atual == NULL){
    printf("Atividade com título '%s' não encontrada.\n", titulo);
    return lista; 
  }

  
  if(anterior == NULL){
    lista = atual->prox; 
  }else{
    anterior->prox = atual->prox;
  }

  free(atual->info);
  free(atual);
  
  printf("Atividade '%s' removida com sucesso.\n", titulo);
  
  return lista;
}

void exibirAtividades(ListaAtividade *lista){
  ListaAtividade *atual = lista;
  if(atual == NULL){
    printf("Nenhuma atividade cadastrada.\n");
    return;
  }
  printf("Atividades cadastradas: \n");
  while (atual != NULL){
    printf("Título: %s, Horário: %s\n", atual->info->titulo, atual->info->horario);
    atual = atual->prox;
  }
}

void liberarAtividades(ListaAtividade *lista) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    ListaAtividade *prox = atual->prox;
    free(atual->info);
    free(atual);
    atual = prox;
  }
}

ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    if (strcmp(atual->info->titulo, titulo) == 0) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL; // Atividade não encontrada
}