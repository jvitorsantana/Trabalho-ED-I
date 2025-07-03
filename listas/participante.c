#include "lista_duplamente_encadeada_participante.h"
#include "pilha_participante.h"
#include "../estruturas/struct_participante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manipulação de pilha

PilhaParticipante *inicializarPilhaParticipantes(){
    PilhaParticipante *p = (PilhaParticipante *)malloc(sizeof(PilhaParticipante));
    p->topo = NULL;
    return p;
}

int empilharParticipante(PilhaParticipante* pilha, Participante participante){
    NoParticipante* novoParticipante = (NoParticipante*)malloc(sizeof(NoParticipante));
    if(novoParticipante == NULL){
        printf("Erro ao criar participante\n");
        return 0;
    }
    novoParticipante->info = participante;
    novoParticipante->proximo = pilha->topo;
    pilha->topo = novoParticipante;
    return 1;
}

int desempilharParticipante(PilhaParticipante* pilha, Participante* destino){
    if(pilha->topo == NULL){
        printf("Pilha vazia\n");
        return 0;
    }
    NoParticipante* temp = pilha->topo;
    *destino = temp->info; 
    pilha->topo = temp->proximo;
    free(temp);
    return 1;
}

void liberarPilha(PilhaParticipante* pilha){
    Participante p;
    while(desempilharParticipante(pilha, &p));
}


// Manipulação de participantes na lista duplamente encadeada

ListaParticipante* inicializarListaDuplamenteEncadeada(){
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

int inserirParticipante(ListaParticipante** lista, ListaParticipante* novoParticipante){
  if (*lista == NULL){
    *lista = novoParticipante;
    printf("Participante inserido:\n");
    printf("Matrícula: %s\n", novoParticipante->info.matricula);
    printf("Nome: %s\n", novoParticipante->info.nome);
    printf("Email: %s\n\n", novoParticipante->info.email);
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

  printf("Participante inserido:\n");
  printf("Matrícula: %s\n", novoParticipante->info.matricula);
  printf("Nome: %s\n", novoParticipante->info.nome);
  printf("Email: %s\n\n", novoParticipante->info.email);

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

int removerParticipante(ListaParticipante** lista, char matricula[], PilhaParticipante* pilha){
    if (*lista == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    ListaParticipante* atual = *lista;

    while (atual != NULL && strcmp(atual->info.matricula, matricula) != 0){
        atual = atual->proximo;
    }

    if (atual == NULL){
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
        return 0;
    }
    
    free(atual);

    return 1;
}

int desfazerRemocaoParticipante(ListaParticipante** lista, PilhaParticipante* pilha){
    if (pilha->topo == NULL){
        printf("Pilha vazia\n");
        return 0;
    }

    Participante p;

    if (!desempilharParticipante(pilha, &p)){
        return 0;
    }

    ListaParticipante* novoParticipante = (ListaParticipante*)malloc(sizeof(ListaParticipante));
    if (novoParticipante == NULL){
        return 0;
    }

    strcpy(novoParticipante->info.matricula, p.matricula);
    strcpy(novoParticipante->info.nome, p.nome);
    strcpy(novoParticipante->info.email, p.email);
    novoParticipante->anterior = NULL;
    novoParticipante->proximo = NULL;

    return inserirParticipante(lista, novoParticipante);
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
    
    /*
        ----------------------------------------------------------------------------------------
        Não printar pq ele vai mostrar mais de uma vez no terminal (lado esquerdo e dps os dois)
        ----------------------------------------------------------------------------------------
    */

    // atual = resultado;
    // printf("\n Lista de Participantes Ordenada por Nome: \n");
    // while (atual != NULL){
    //     printf("Nome: %s | Matrícula: %s | E-mail: %s\n", atual->info.nome, atual->info.matricula, atual->info.email);
    //     atual = atual->proximo;
    // }
    
    // antes que me perguntem, tem que retornar se não a cabeça ainda vai apontar pro antiga cabeça 
    return resultado;
}

void imprimirListaParticipantesOrdenada(ListaParticipante *lista) {
    ListaParticipante *resultado = ordernarListaParticipantesPeloNome(lista);
    ListaParticipante *atual = resultado;
    printf("Lista dos Participantes Ordenada Pelo Nome\n");
    while (atual != NULL) {
        printf("Nome: %s | Matricula: %s | E-mail: %s\n", atual->info.nome, atual->info.matricula, atual->info.email);
        atual = atual->proximo;
    }
    printf("\n");
}






