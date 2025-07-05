#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista_encadeada_atividade.h"
#include "lista_duplamente_encadeada_participante.h"

int validarHorario(char *horario) {
  if(strlen(horario) != 5 || horario[2] != ':') { // se o tamanho não for 5 ou o terceiro caractere não for ':'
    return 0; 
  }
  if(isdigit(horario[0]) && isdigit(horario[1]) && isdigit(horario[3]) && isdigit(horario[4])) { // "HH:MM", verifica se os caracteres numeros
    
    int horas = (horario[0] - '0') * 10 + (horario[1] - '0'); 
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');
    // Converte os caracteres para inteiros com ASCII, 
    // onde '0' é subtraído para obter o valor numérico, pois '0' tem o valor ASCII 48, '1' tem 49, '2' tem 50...

    if(horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60) {
      return 1; 
    }
  }
  return 0; 
}

ListaAtividade *inicializar(){
  return NULL;
}

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
    return nova;
}
      

ListaAtividade *removerAtividade(ListaAtividade *lista, char *titulo){
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

  liberarListaParticipantes(&(atual->info.participantes)); // Libera a lista de participantes da atividade
  
  if(anterior == NULL){
    lista = atual->prox; 
  }else{
    anterior->prox = atual->prox;
  }

  free(atual);
  
  printf("Atividade '%s' removida com sucesso.\n", titulo);
  
  return lista;
}

void liberarAtividades(ListaAtividade *lista) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    ListaAtividade *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

ListaAtividade *buscarAtividade(ListaAtividade *lista, char *titulo) {
  ListaAtividade *atual = lista;
  while (atual != NULL) {
    if (strcmp(atual->info.titulo, titulo) == 0) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL; // Atividade não encontrada
}

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

void exibirAtividades(ListaAtividade *lista){
  ListaAtividade *copia = copiarListaAtividade(lista);
  ListaAtividade *resultado = ordenarListaAtividadesPorHorario(copia);
  ListaAtividade *atual = resultado;
  if(atual == NULL){
    printf("Nenhuma atividade cadastrada.\n");
    return;
  }
  printf("Atividades cadastradas: \n");
  while (atual != NULL){
    printf("Título: %s, Horário: %s\n", atual->info.titulo, atual->info.horario);
    atual = atual->prox;
  }
  free(copia);
}

void exibirNomeAtividades(ListaAtividade *lista) {
  ListaAtividade *copia = copiarListaAtividade(lista);
  ListaAtividade *resultado = ordenarListaAtividadesPorHorario(copia);
  ListaAtividade *atual = resultado;
  if(atual == NULL){
    printf("Nenhuma atividade cadastrada.\n");
    return;
  }

  while (atual != NULL){
    printf("- %s | Horario: %s\n", atual->info.titulo, atual->info.horario);
    atual = atual->prox;
  }
  free(copia);
}