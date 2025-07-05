#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes/funcoes.h"
#include "estruturas/struct_evento.h"
#include "listas/lista_circular_eventos.h"
#include "listas/lista_encadeada_atividade.h"


void menuParticipantesAtividade(Atividade *atividade);
void menuVerAtividade(Atividade *atividade);
void menuEditarEvento(Evento *e);
void menuAdministracao(ListaEventos **listaEventos);
void menuCheckIn(ListaEventos *listaEventos);
void menuPrincipal(ListaEventos **listaEventos);

int main() {
  ListaEventos *listaEventos = inicializarListaEventos();
  menuPrincipal(&listaEventos);
  return 0;
}

void menuPrincipal(ListaEventos **listaEventos) {
  char opcao = '\0';
  while (opcao != '0') {
    limparTerminal();

    printf("Seja bem-vindo ao Sistema PicaDuraMole Gerenciador de Eventos\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("1 » Administracao\n");
    printf("2 » Realizar Check-In\n");
    printf("0 » Sair\n");
    printf("➜ ");

    scanf(" %c", &opcao);
    limparBuffer();

    switch(opcao) {
      case '1':
        menuAdministracao(listaEventos);
        break;
      case '2':
        menuCheckIn(*listaEventos);
        break;
      case '0':
        break;
      default:
        printf("Opcao invalida!");
        pausarTerminal();
        break;
      }
  }
}

void menuAdministracao(ListaEventos **listaEventos) {
  char opcaoAdmin = '\0';
  while (opcaoAdmin != '0') {
    limparTerminal();
    printf("Seja bem-vindo ao painel administrativo!\n\n");
    printf("1 » Criar Evento\n");
    printf("2 » Listar Eventos\n");
    printf("3 » Excluir Evento\n");
    printf("4 » Editar Evento\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoAdmin);
    limparBuffer();

    switch(opcaoAdmin) {
      case '1':
        char *nome_inserir = digitarNomeEvento();
        char *data_inserir = digitarDataEvento();
        *listaEventos = inserirEvento(*listaEventos, nome_inserir, data_inserir);
        free(nome_inserir);
        free(data_inserir);
        pausarTerminal();
        break;
      case '2':
        if (*listaEventos == NULL) {
          printf("ERRO: Nao foi cadastrado nenhum evento!");
        } else {
          imprimirEventos(*listaEventos);
        }
        pausarTerminal();
        break;
      case '3':
        char *nome_remover = digitarNomeEvento();
        *listaEventos = removerEvento(*listaEventos, nome_remover);
        free(nome_remover);
        pausarTerminal();
        break;
      case '4':
        char *nome_evento = digitarNomeEvento();
        ListaEventos *eventos = buscarEvento(*listaEventos, nome_evento);
        if (eventos == NULL) {
          printf("ERRO: Evento nao encontrado!");
          pausarTerminal();
        } else {
          menuEditarEvento(&eventos->info); // OU &((*eventos).info)
        }
        break;
      case '0':
        break;
      }
  }
}

void menuEditarEvento(Evento *e) {
  char opcaoMenuEditarEvento = '\0';
  while (opcaoMenuEditarEvento != '0') {
    limparTerminal();
    printf("Você está editando o evento \"%s\"\n\n", e->nome);
    printf("1 » Adicionar atividade\n");
    printf("2 » Listar atividades\n");
    printf("3 » Remover atividade\n");
    printf("4 » Ver atividade\n");
    printf("Z » Desfazer a ultima remocao\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoMenuEditarEvento);
    limparBuffer();

    switch(opcaoMenuEditarEvento) {
      case '1':
        char *nome_atividade = digitarNomeAtividade();
        char *horario_atividade = digitarHorarioAtividade();
        if (!validarHorario(horario_atividade)) {
          printf("ERRO: Voce digitou o horario no formato invalido!\nUse: HH:mm");
          pausarTerminal();
        } else {
          e->atividades = inserirAtividade(e->atividades, nome_atividade, horario_atividade);
        }
        free(nome_atividade);
        free(horario_atividade);
        break;
      case '2':
        limparTerminal();
        exibirAtividades(e->atividades);
        pausarTerminal();
        break;
      case '3':
        char *nome_remover = digitarNomeAtividade();
        e->atividades = removerAtividade(e->atividades, nome_remover);
        free(nome_remover);
        pausarTerminal();
        break;
      case '4':
        char *atividade = digitarNomeAtividade();
        ListaAtividade *atividades = buscarAtividade(e->atividades, atividade);
        if (atividades == NULL) {
          printf("ERRO: Atividade '%s' nao encontrada!\n", atividade);
          pausarTerminal();
        } else {
          menuVerAtividade(&atividades->info);
        }
        free(atividade);
        break;
      case 'Z':
      case 'z':
        printf("Desfazer a pilha aq");
        break;
      case '0':
        break;
      default:
        printf("Opcao invalida!");
        pausarTerminal();
        break;
      }
  }
}

void menuVerAtividade(Atividade *atividade) {
  char opcaoMenuVerAtividade = '\0';
  while (opcaoMenuVerAtividade != '0') {
    limparTerminal();

    printf("Titulo: %s\n", atividade->titulo);
    printf("Horario: %s\n\n", atividade->horario);
    printf("1 » Gerenciar Participantes\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoMenuVerAtividade);
    limparBuffer();

    switch(opcaoMenuVerAtividade) {
      case '1':
        menuParticipantesAtividade(atividade);
        break;
      case '0':
        break;
      default:
        printf("Opcao invalida!");
        pausarTerminal();
        break;
      }
  }
}

void menuParticipantesAtividade(Atividade *atividade) {
  char opcaoMenuParticipantesAtividade = '\0';
  while (opcaoMenuParticipantesAtividade != '0') {
    limparTerminal();

    printf("Voce esta gerenciando os participantes da atividade \"%s\"\n\n", atividade->titulo);
    printf("1 » Cadastrar participante\n");
    printf("2 » Listar participantes\n");
    printf("3 » Remover participante\n");
    printf("Z » Desfazer a ultima remocao\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoMenuParticipantesAtividade);
    limparBuffer();

    switch(opcaoMenuParticipantesAtividade) {
      char *nomeParticipante;
      char *matriculaParticipante;
      char *emailParticipante;
      case '1':
        nomeParticipante = digitarNomeParticipante();
        matriculaParticipante = digitarMatriculaParticipante();
        emailParticipante = digitarEmailParticipante();

        ListaParticipante *novoParticipante = criarParticipante(matriculaParticipante, nomeParticipante, emailParticipante);
        inserirParticipante(&atividade->participantes, novoParticipante);

        free(nomeParticipante);
        free(matriculaParticipante);
        free(emailParticipante);
        pausarTerminal();
        break;
      case '2':
        if (atividade->participantes == NULL) {
          printf("ERRO: Nao foi cadastrado nenhum participante");
        } else {
          imprimirListaParticipantesOrdenada(atividade->participantes);
        }
        pausarTerminal();
        break;
      case '3':
        matriculaParticipante = digitarMatriculaParticipante();
        removerParticipante(&atividade->participantes, matriculaParticipante, atividade->pilhaParticipantes);
        free(matriculaParticipante);
        pausarTerminal();
        break;
      case 'Z':
      case 'z':
        desfazerRemocaoParticipante(&atividade->participantes, atividade->pilhaParticipantes);
        pausarTerminal();
        break;
      case '0':
        break;
      default:
        printf("Opcao invalida!");
        pausarTerminal();
        break;
      }
  }
}

void menuCheckIn(ListaEventos *listaEventos) {
  limparTerminal();

  char *nomeEvento = digitarNomeEvento();
  ListaEventos *eventos = buscarEvento(listaEventos, nomeEvento);
  if (eventos == NULL) {
    printf("\nERRO: Nao foi encontrado um evento com este nome!\n");
    free(nomeEvento);
    pausarTerminal();
    return;
  }
  char *matriculaParticipante = digitarMatriculaParticipante();

  realizarCheckIn(&eventos->info, matriculaParticipante);

  free(nomeEvento);
  free(matriculaParticipante);
  pausarTerminal();
}
