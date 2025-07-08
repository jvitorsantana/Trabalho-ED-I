#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha_participante.h"


// Inicializa uma nova pilha de participantes, com topo igual a NULL.
PilhaParticipante *inicializarPilhaParticipantes(){
    PilhaParticipante *p = (PilhaParticipante *)malloc(sizeof(PilhaParticipante));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha de participantes.\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

// Empilha um novo participante no topo da pilha.
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

// Desempilha o participante do topo e armazena seus dados no destino.
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

// Libera toda a memória alocada para a pilha e seus elementos.
void liberarPilhaParticipante(PilhaParticipante* pilha){
    Participante p;
    while(desempilharParticipante(pilha, &p));
    free(pilha);
}