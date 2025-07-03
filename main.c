#include <stdio.h>
#include <stdlib.h>

#include "listas/lista_duplamente_encadeada_participante.h"
#include "listas/pilha_participante.h"

int main() {
  ListaParticipante *lista = inicializarListaDuplamenteEncadeada();
  PilhaParticipante *pilha = inicializarPilhaParticipantes();

  ListaParticipante *part1 = criarParticipante("20257005498", "Brasil", "brasil@email.com");
  ListaParticipante *part2 = criarParticipante("20257005412", "Japao", "japao@email.com");
  ListaParticipante *part3 = criarParticipante("20257001498", "Europa", "europa@email.com");

  inserirParticipante(&lista, part1);
  inserirParticipante(&lista, part2);
  inserirParticipante(&lista, part3);

  removerParticipante(&lista, "20257005412", pilha);
  removerParticipante(&lista, "20257001498", pilha);

  imprimirListaParticipantesOrdenada(lista);

  desfazerRemocaoParticipante(&lista, pilha);

  imprimirListaParticipantesOrdenada(lista);

  desfazerRemocaoParticipante(&lista, pilha);

  imprimirListaParticipantesOrdenada(lista);

  liberarPilha(pilha);
  liberarListaParticipantes(&lista);

  return 0;
}