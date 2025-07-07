#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas/struct_participante.h"
#include "lista_duplamente_encadeada_participante.h"
#include "pilha_participante.h"
#include "fila_check_in.h"

// Manipulação de participantes na lista duplamente encadeada

ListaParticipante* inicializarListaParticipantes(){
  return NULL;
}

ListaParticipante* criarParticipante(char matricula[], char nome[], char email[]){
  ListaParticipante* novoParticipante = (ListaParticipante*)malloc(sizeof(ListaParticipante));

  if (novoParticipante == NULL){
    printf("Erro ao criar participante\n");
    return NULL;
  }

  strncpy(novoParticipante->info.matricula, matricula, sizeof(novoParticipante->info.matricula) - 1);
  novoParticipante->info.matricula[sizeof(novoParticipante->info.matricula) - 1] = '\0';

  strncpy(novoParticipante->info.nome, nome, sizeof(novoParticipante->info.nome) - 1);
  novoParticipante->info.nome[sizeof(novoParticipante->info.nome) - 1] = '\0';

  strncpy(novoParticipante->info.email, email, sizeof(novoParticipante->info.email) - 1);
  novoParticipante->info.email[sizeof(novoParticipante->info.email) - 1] = '\0';

  novoParticipante->anterior = NULL;
  novoParticipante->proximo = NULL;

  return novoParticipante; 
}

int existeParticipante(ListaParticipante *lista, char matriculaParticipante[]) {
    int existe = 0;
    ListaParticipante *atual = lista;
    while (atual != NULL) {
        if (strcasecmp(atual->info.matricula, matriculaParticipante) == 0){
            existe = 1;
            return existe;
        }
        atual = atual->proximo;
    }

    return existe;
}

int inserirParticipante(ListaParticipante** lista, ListaParticipante* novoParticipante){
  if (*lista == NULL){
    *lista = novoParticipante;
    return 1;
  }

  ListaParticipante* atual = *lista;

  while (atual != NULL){
    if (strcmp(atual->info.matricula, novoParticipante->info.matricula) == 0){
      printf("Participante já existe na lista\n");
      return 0;
    }
    if (atual->proximo == NULL){
        break;
    }
    atual = atual->proximo;
  }

  atual->proximo = novoParticipante;
  novoParticipante->anterior = atual;
  novoParticipante->proximo = NULL;

  return 1;
}

void liberarListaParticipantes(ListaParticipante** lista){
    ListaParticipante* atual = *lista;
    while (atual != NULL){
        ListaParticipante* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}

int removerParticipante(ListaParticipante** lista, char matricula[], PilhaParticipante* pilha, FilaCheckIn** fila) {
    if (*lista == NULL){
        printf("Não há participantes para serem removidos!\n");
        return 0;
    }

    ListaParticipante* atual = *lista;

    while (atual != NULL && strcmp(atual->info.matricula, matricula) != 0){
        atual = atual->proximo;
    }

    if (atual == NULL){
        printf("Participante não encontrado!\n");
        return 0;
    }

    if (atual->anterior != NULL){
        atual->anterior->proximo = atual->proximo;
    } else{
        *lista = atual->proximo;
    }

    if (atual->proximo != NULL){
        atual->proximo->anterior = atual->anterior;
    }

    Participante temp;
    strcpy(temp.matricula, atual->info.matricula);
    strcpy(temp.nome, atual->info.nome);
    strcpy(temp.email, atual->info.email);

    if (!empilharParticipante(pilha, temp)){
        printf("Não foi possível remover o participante! (pilha não suporta)\n");
        return 0;
    }

    if (existeNaFila(*fila, matricula)){
        removerFila(*fila, matricula);
    }
    

    free(atual);

    printf("Participante removido com sucesso!\n");

    return 1;
}

int desfazerRemocaoParticipante(ListaParticipante** lista, PilhaParticipante* pilha){
    if (pilha->topo == NULL){
        printf("Não há nada para desfazer!\n");
        return 0;
    }

    Participante p;

    if (!desempilharParticipante(pilha, &p)){
        printf("Não foi possível desfazer a remoção do participante!\n");
        return 0;
    }

    ListaParticipante* novoParticipante = (ListaParticipante*)malloc(sizeof(ListaParticipante));
    if (novoParticipante == NULL){
        printf("Não foi possível desfazer a remoção do participante!\n");
        return 0;
    }

    strcpy(novoParticipante->info.matricula, p.matricula);
    strcpy(novoParticipante->info.nome, p.nome);
    strcpy(novoParticipante->info.email, p.email);
    novoParticipante->anterior = NULL;
    novoParticipante->proximo = NULL;

    return inserirParticipante(lista, novoParticipante);
}

ListaParticipante *copiarListaParticipante(ListaParticipante *lista) {
    if (lista == NULL) {
        return NULL;
    }

    ListaParticipante *copia = NULL;
    ListaParticipante *ultimo = NULL;

    ListaParticipante *atual = lista;
    while (atual != NULL) {
        ListaParticipante* novoNo = malloc(sizeof(ListaParticipante));
        if (novoNo == NULL) {
            perror("Erro ao alocar na memoria");
            exit(1);
        }

        novoNo->info = atual->info;
        novoNo->proximo = NULL;
        novoNo->anterior = ultimo;

        if (ultimo == NULL) {
            copia = novoNo;
        } else {
            ultimo->proximo = novoNo;
        }
        ultimo = novoNo;

        atual = atual->proximo;
    }

    return copia;
}

ListaParticipante* ordernarListaParticipantesPeloNome(ListaParticipante* lista){
    if (lista == NULL || lista->proximo == NULL){
        return lista;
    }
    ListaParticipante* lento = lista;
    ListaParticipante* rapido = lista;

    while (rapido->proximo != NULL && rapido->proximo->proximo){
        lento = lento->proximo;
        rapido = rapido->proximo->proximo;
    }

    ListaParticipante* meio = lento->proximo;
    lento->proximo = NULL;
    if (meio != NULL){
        meio->anterior = NULL;
    }

    ListaParticipante* esquerda = ordernarListaParticipantesPeloNome(lista);
    ListaParticipante* direita = ordernarListaParticipantesPeloNome(meio);

    ListaParticipante* resultado = NULL;
    ListaParticipante** ponteiroAtual = &resultado;

    while (esquerda != NULL && direita != NULL){
        if (strcmp(esquerda->info.nome, direita->info.nome) <= 0){
            *ponteiroAtual = esquerda;
            esquerda->anterior = NULL;
            esquerda = esquerda->proximo;
        } else{
            *ponteiroAtual = direita;
            direita->anterior = NULL;
            direita = direita->proximo;
        }
        ponteiroAtual = &((*ponteiroAtual)->proximo);
    }

    if (esquerda != NULL){
        *ponteiroAtual = esquerda;
    } else{
        *ponteiroAtual = direita;
    }

    ListaParticipante* atual = resultado;
    ListaParticipante* anterior = NULL;
    while (atual != NULL){
        atual->anterior = anterior;
        anterior = atual;
        atual = atual->proximo;
    }
    
    return resultado;
}

void imprimirListaParticipantesOrdenada(ListaParticipante *lista) {
    ListaParticipante *copia = copiarListaParticipante(lista);
    ListaParticipante *resultado = ordernarListaParticipantesPeloNome(copia);
    ListaParticipante *atual = resultado;
    printf("\n=== Lista Participantes [A-Z] ===\n\n");
    while (atual != NULL) {
        printf("Nome: %s | Matricula: %s | E-mail: %s\n", atual->info.nome, atual->info.matricula, atual->info.email);
        atual = atual->proximo;
    }
    printf("\n");
    liberarListaParticipantes(&copia);
}