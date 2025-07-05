#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas/struct_evento.h"
#include "fila_check_in.h"
#include "lista_circular_eventos.h"
#include "lista_duplamente_encadeada_participante.h"

ListaEventos* inicializarListaEventos(){
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

    novo_evento->info.atividades = NULL;
    novo_evento->info.filaCheckIn = criarFila();

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

void removerAux(ListaEventos **lista, ListaEventos *anterior, ListaEventos *atual){
    anterior->prox = atual->prox;
    if(atual == *lista){
        *lista = anterior;
    }
    
    free(atual);
}


ListaEventos* removerEvento(ListaEventos *lista, const char *nome){
    if(!lista){
        printf("ERRO: Nao foi cadastrado nenhum evento!");
        return NULL;
    }

    if(strcasecmp(lista->info.nome, nome) == 0 && lista->prox == lista){
        free(lista);
        printf("Evento removido com sucesso!");
        return NULL;
    }
    ListaEventos *atual = lista->prox;
    ListaEventos *anterior = lista;
    do{
        if(strcmp(atual->info.nome, nome)==0){
            removerAux(&lista, anterior, atual);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }while(atual != lista->prox);
    printf("Evento removido com sucesso!");
    return lista;
}


void imprimirEventos(ListaEventos *lista){
    if(lista == NULL){
        return;
    }
    ListaEventos *atual = lista->prox;
    do{
        printf("Nome do evento: %s  | Data do evento: %s \n", atual->info.nome, atual->info.data);
        atual = atual->prox;
    }while(atual != lista->prox);
}

void liberarListaCircularEventos(ListaEventos *lista) {
    if (lista == NULL) {
        return;
    }

    if (lista->prox == lista) {
        free(lista);
        return;
    }

    ListaEventos *auxiliar = lista->prox;
    ListaEventos *a_remover = NULL;

    while (auxiliar != lista) {
        a_remover = auxiliar;
        auxiliar = auxiliar->prox;
        free(a_remover);
    }

    free(lista);
}

ListaEventos* buscarEvento(ListaEventos *lista, char nome[]) {
    if (lista == NULL){
        return NULL;
    }
    ListaEventos *atual = lista->prox;
    do{
        if(strcasecmp(atual->info.nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }while(atual != lista->prox);

  return NULL;
}

int participanteCadastradoNoEvento(Evento *evento, char matriculaParticipante[]) {
    int existe = 0;
    ListaAtividade *atividades = evento->atividades;
    while (atividades != NULL) {
        int participanteExiste = buscarParticipante(atividades->info.participantes, matriculaParticipante);
        if (participanteExiste) {
            existe = 1;
            return existe;
        }
        atividades = atividades->prox;
    }
    return existe;
}

void realizarCheckIn(Evento *evento, char matriculaParticipante[]) {
    int existe = existeNaFila(evento->filaCheckIn, matriculaParticipante);
    if (existe) {
        printf("\nERRO: Voce ja realizou o check-in neste evento!\n");
        return;
    }

    int participanteCadastrado = participanteCadastradoNoEvento(evento, matriculaParticipante);
    
    if (!participanteCadastrado) {
        printf("\nERRO: Este participante nao esta cadastrado em nenhuma das atividades deste evento!");
        return;
    }

    inserirFila(evento->filaCheckIn, matriculaParticipante);
    int posicao = existeNaFila(evento->filaCheckIn, matriculaParticipante);
    printf("\nCheck-In realizado com sucesso!\nVoce esta na posicao: %d", posicao);
}