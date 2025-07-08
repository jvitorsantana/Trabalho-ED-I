#include "../estruturas/struct_participante.h" 

// Diretiva de compilação condicional para evitar múltiplas inclusões deste cabeçalho
#ifndef PILHA_PARTICIPANTE_H
#define PILHA_PARTICIPANTE_H

// Estrutura de um nó da pilha, que armazena um Participante e aponta para o próximo nó
typedef struct NoParticipante{
    Participante info;
    struct NoParticipante *proximo;
} NoParticipante;

// Estrutura da pilha de participantes
typedef struct PilhaParticipante{
    struct NoParticipante *topo; // Inicializa uma pilha vazia de participantes
} PilhaParticipante;

// Inicializa uma pilha vazia de participantes
PilhaParticipante *inicializarPilhaParticipantes();
// Empilha um novo participante na pilha
int empilharParticipante(PilhaParticipante *pilha, Participante Participante);
// Desempilha o participante do topo e armazena seus dados no ponteiro destino
int desempilharParticipante(PilhaParticipante *pilha, Participante *destino);
// Libera toda a memória alocada pela pilha de participantes
void liberarPilhaParticipante(PilhaParticipante *pilha);

// Fim da diretiva de compilação condicional
#endif