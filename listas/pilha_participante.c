#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha_participante.h"


PilhaParticipante *inicializarPilhaParticipantes(){
    PilhaParticipante *p = (PilhaParticipante *)malloc(sizeof(PilhaParticipante));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha de participantes.\n");
        exit(1);
    }
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
        // printf("Pilha vazia\n");
        return 0;
    }
    NoParticipante* temp = pilha->topo;
    *destino = temp->info; 
    pilha->topo = temp->proximo;
    free(temp);
    return 1;
}

void liberarPilhaParticipante(PilhaParticipante* pilha){
    Participante p;
    while(desempilharParticipante(pilha, &p));
    free(pilha);
}