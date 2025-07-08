#ifndef FILA_CHECK_IN_H
#define FILA_CHECK_IN_H

// Estrutura do nó da fila
typedef struct NoFilaCheckIn {
  char matriculaParticipante[26];
  struct NoFilaCheckIn *proximo;
} NoFilaCheckIn;

// Estrutura da fila
typedef struct FilaCheckIn {
  NoFilaCheckIn *inicio;
  NoFilaCheckIn *fim;
} FilaCheckIn;

// Protótipos das funções vinculadas a manipulação da fila
FilaCheckIn *criarFila();
void liberarFila(FilaCheckIn *fila);
int filaVazia(FilaCheckIn *fila);
void inserirFila(FilaCheckIn *fila, char matriculaParticipante[]);
int existeNaFila(FilaCheckIn *fila, char matriculaParticipante[]);
int posicaoNaFila(FilaCheckIn *fila, char matriculaParticipante[]);
void imprimirFila(FilaCheckIn *fila);
int removerFila(FilaCheckIn* fila, char matriculaParticipante[]);

#endif
