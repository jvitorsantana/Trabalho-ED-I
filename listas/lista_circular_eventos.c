#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../estruturas/struct_evento.h"
#include "lista_circular_eventos.h"
#include "lista_encadeada_atividade.h"





ListaEventos* inicializar(){
    return NULL;
}


ListaEventos* inserirEvento(ListaEventos *lista, char nome[], char data[]){
    ListaEventos *busca = buscarEvento(lista, nome);
    if(busca != NULL){
        printf("Evento com nome '%s' já existe.\n", nome);
        return lista;
    }
    ListaEventos *novo_evento = (ListaEventos*)malloc(sizeof(ListaEventos));
    if(novo_evento == NULL){
        printf("Erro ao alocar a memoria.");
        return lista;
    }

    strncpy(novo_evento->info.nome, nome, sizeof(novo_evento->info.nome) - 1);
    novo_evento->info.nome[sizeof(novo_evento->info.nome) - 1] = '\0';

    strncpy(novo_evento->info.data, data, sizeof(novo_evento->info.data) - 1);
    novo_evento->info.data[sizeof(novo_evento->info.data) - 1] = '\0';

    if(lista == NULL){
        novo_evento->prox = novo_evento;
        printf("Evento foi inserido: \n");
        printf("Nome: %s \n", novo_evento->info.nome);
        printf("Data: %s \n", novo_evento->info.data);
        return novo_evento;
    }

    novo_evento->prox = lista->prox;
    lista->prox = novo_evento;
    printf("Evento foi inserido: \n");
    printf("Nome: %s \n", novo_evento->info.nome);
    printf("Data: %s \n", novo_evento->info.data);
    return novo_evento;
}

void removeAux(ListaEventos **lista, ListaEventos *anterior, ListaEventos *atual){
    anterior->prox = atual->prox;
    if(atual == *lista){
        *lista = anterior;
    }
    // free(atual->info.nome);
    // free(atual->info.data);
    free(atual);
}


ListaEventos* removerEvento(ListaEventos *lista, char nome[]){
    if(!lista){
        return NULL;
    }

    if(strcmp(lista->info.nome, nome)==0 && lista->prox == lista){
        free(lista);
        return NULL;
    }
    ListaEventos *atual = lista->prox;
    ListaEventos *anterior = lista;
    do{
        if(strcmp(atual->info.nome, nome)==0){
            remove_aux(&lista, anterior, atual);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }while(atual != lista->prox);

    return lista;
}


void imprimirListaCircular(ListaEventos *lista){
    if(lista == NULL){
        return;
    }
    ListaEventos *atual = lista->prox;
    do{
        printf("Nome do evento: %s  | Data do evento: %s \n", atual->info.nome, atual->info.data);
        atual = atual->prox;
    }while(atual != lista->prox);
}

void liberarListaCircular(ListaEventos *lista) {
    if (lista == NULL) {
        return;
    }

    if (lista->prox == lista) {
        // free(lista->info.nome);
        // free(lista->info.data);
        free(lista);
        return;
    }

    ListaEventos *auxiliar = lista->prox;
    ListaEventos *a_remover = NULL;

    while (auxiliar != lista) {
        a_remover = auxiliar;
        auxiliar = auxiliar->prox;
        // free(a_remover->info.nome);
        // free(a_remover->info.data);
        free(a_remover);
    }

    // free(lista->info.nome);
    // free(lista->info.data);
    free(lista);
}

ListaEventos* buscarEvento(ListaEventos *lista, char nome[]) {
    if (lista == NULL){
        return NULL;
    }
    ListaEventos *atual = lista->prox;
    do{
        if(strcmp(atual->info.nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }while(atual != lista->prox);

  return NULL;
}