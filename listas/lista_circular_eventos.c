#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas/struct_evento.h"
#include "fila_check_in.h"
#include "lista_circular_eventos.h"
#include "lista_duplamente_encadeada_participante.h"
#include "pilha_atividade.h"

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
    novo_evento->info.pilhaAtividades = inicializarPilhaAtividades();
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
    if (atual->info.atividades != NULL) {
        liberarAtividades(atual->info.atividades);
    }
    if (atual->info.pilhaAtividades != NULL) {
        liberarPilhaAtividades(atual->info.pilhaAtividades);
    }
    if (atual->info.filaCheckIn != NULL) {
        liberarFila(atual->info.filaCheckIn);
    }

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
        if (lista->info.atividades != NULL) {
            liberarAtividades(lista->info.atividades);
        }
        if (lista->info.pilhaAtividades != NULL) {
            liberarPilhaAtividades(lista->info.pilhaAtividades);
        }
        if (lista->info.filaCheckIn != NULL) {
            liberarFila(lista->info.filaCheckIn);
        }
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
        printf("Nome do evento: %s | Data do evento: %s \n", atual->info.nome, atual->info.data);
        atual = atual->prox;
    }while(atual != lista->prox);
}

void liberarListaCircularEventos(ListaEventos *lista) {
    if (lista == NULL) {
        return;
    }

    if (lista->prox == lista) {
        if (lista->info.atividades != NULL) {
            liberarAtividades(lista->info.atividades);
        }
        if (lista->info.pilhaAtividades != NULL) {
            liberarPilhaAtividades(lista->info.pilhaAtividades);
        }
        if (lista->info.filaCheckIn != NULL) {
            liberarFila(lista->info.filaCheckIn);
        }
        free(lista);
        return;
    }

    ListaEventos *auxiliar = lista->prox;
    ListaEventos *a_remover = NULL;

    while (auxiliar != lista) {
        if (auxiliar->info.atividades != NULL) {
            liberarAtividades(auxiliar->info.atividades);
        }
        if (auxiliar->info.pilhaAtividades != NULL) {
            liberarPilhaAtividades(auxiliar->info.pilhaAtividades);
        }
        if (auxiliar->info.filaCheckIn != NULL) {
            liberarFila(auxiliar->info.filaCheckIn);
        }
        a_remover = auxiliar;
        auxiliar = auxiliar->prox;
        free(a_remover);
    }

    free(lista);
}

<<<<<<< HEAD
ListaEventos* buscar_evento(ListaEventos *lista, char nome[]) {
=======
ListaEventos* buscarEvento(ListaEventos *lista, char nome[]) {
>>>>>>> main
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
        int participanteExiste = existeParticipante(atividades->info.participantes, matriculaParticipante);
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
    int posicao = posicaoNaFila(evento->filaCheckIn, matriculaParticipante);
    printf("\nCheck-In realizado com sucesso!\nVoce esta na posicao: %d", posicao);
}

void imprimirParticipantesEvento(Evento evento) {
    ListaParticipante *l = inicializarListaParticipantes();
    ListaAtividade *atv = evento.atividades;

    while (atv != NULL) {
        ListaParticipante *part = atv->info.participantes;
        while (part != NULL) {
            if (!existeParticipante(l, part->info.matricula)) {
                ListaParticipante *lPart = criarParticipante(part->info.matricula, part->info.nome, part->info.email);
                inserirParticipante(&l, lPart);
            }
            part = part->proximo;
        }
        atv = atv->prox;
    }

    if (l == NULL) {
        printf("Nenhum participante foi adicionado ainda!\n");
        return;
    }

    ListaParticipante *listaOrdenada = ordernarListaParticipantesPeloNome(l);

    ListaParticipante *atual = listaOrdenada;
    while (atual != NULL) {
        printf("- %s [%s]\n", atual->info.nome, atual->info.matricula);
        atual = atual->proximo;
    }

    free(l);
}