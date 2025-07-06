#ifndef FILA_CHECK_IN_H
#define FILA_CHECK_IN_H

typedef struct NoFilaCheckIn {
  char matriculaParticipante[26];
  struct NoFilaCheckIn *proximo;
} NoFilaCheckIn;

typedef struct FilaCheckIn {
  NoFilaCheckIn *inicio;
  NoFilaCheckIn *fim;
} FilaCheckIn;

FilaCheckIn *criarFila();
void liberarFila(FilaCheckIn *fila);
int filaVazia(FilaCheckIn *fila);
void inserirFila(FilaCheckIn *fila, char matriculaParticipante[]);
int existeNaFila(FilaCheckIn *fila, char matriculaParticipante[]);
int posicaoNaFila(FilaCheckIn *fila, char matriculaParticipante[]);
void imprimirFila(FilaCheckIn *fila);

#endif
