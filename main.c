#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes/funcoes.h"
#include "estruturas/struct_evento.h"
#include "listas/lista_circular_eventos.h"
#include "listas/lista_encadeada_atividade.h"
#include "listas/fila_check_in.h"

void menuParticipantesAtividade(Atividade *atividade, FilaCheckIn* fila);
void menuVerAtividade(Atividade *atividade, FilaCheckIn* filaCheckIn);
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

    printf("Seja bem-vindo ao Sistema Gerenciador de Eventos\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("1 » Administracao\n");
    printf("2 » Realizar Check-In\n");
    printf("0 » Sair\n");
    printf("➜ ");

    scanf(" %c", &opcao);
    limparTerminal();
    limparBuffer();

    switch(opcao) {
      case '1':
        menuAdministracao(listaEventos);
        break;
      case '2':
        menuCheckIn(*listaEventos);
        break;
      case '0':
        liberarListaCircularEventos(*listaEventos);
        printf("Saindo...\n");
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
    printf("5 » Ver Evento\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoAdmin);
    limparTerminal();
    limparBuffer();

    switch(opcaoAdmin) {
      char *nomeEvento;
      ListaEventos *eventos;
      case '1':
        nomeEvento = digitarNomeEvento();
        char *dataEvento = digitarDataEvento();
        if (!validarData(dataEvento)){
          printf("ERRO: Voce digitou a data inválida!\nUse: DD/MM/AAAA");
        } else{
          *listaEventos = inserirEvento(*listaEventos, nomeEvento, dataEvento);
        }
        free(nomeEvento);
        free(dataEvento);
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
        nomeEvento = digitarNomeEvento();
        *listaEventos = removerEvento(*listaEventos, nomeEvento);
        free(nomeEvento);
        pausarTerminal();
        break;
      case '4':
        nomeEvento = digitarNomeEvento();
        eventos = buscarEvento(*listaEventos, nomeEvento);
        if (eventos == NULL) {
          printf("ERRO: Evento nao encontrado!");
          pausarTerminal();
        } else {
          menuEditarEvento(&eventos->info); // OU &((*eventos).info)
        }
        // pausarTerminal();
        free(nomeEvento);
        break;
      case '5':
        nomeEvento = digitarNomeEvento();
        eventos = buscarEvento(*listaEventos, nomeEvento);
        free(nomeEvento);
        if (eventos == NULL) {
          printf("ERRO: Evento nao encontrado!");
          pausarTerminal();
        } else {
          limparTerminal();
          printf("Informacoes do evento '%s'\n", eventos->info.nome);
          printf("Data: %s\n\n", eventos->info.data);
          printf("Atividades:\n");
          exibirNomeAtividades(eventos->info.atividades);
          printf("\nParticipantes:\n");
          imprimirParticipantesEvento(eventos->info);
          printf("\nFila de Check-In:\n");
          imprimirFila(eventos->info.filaCheckIn);
          pausarTerminal();
        }
        break;
      case '0':
        break;
      default:
        printf("Opcao invalida!");
        pausarTerminal();
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
    limparTerminal();
    limparBuffer();

    switch(opcaoMenuEditarEvento) {
      case '1':
        char *nome_atividade = digitarNomeAtividade();
        char *horario_atividade = digitarHorarioAtividade();
        if (!validarHorario(horario_atividade)) {
          printf("ERRO: Voce digitou o horario no formato invalido!\nUse: HH:mm");
        } else {
          e->atividades = inserirAtividade(e->atividades, nome_atividade, horario_atividade);
        }
        free(nome_atividade);
        free(horario_atividade);
        pausarTerminal();
        break;
      case '2':
        limparTerminal();
        exibirAtividades(e->atividades);
        pausarTerminal();
        break;
      case '3':
        char *nome_remover = digitarNomeAtividade();
        e->atividades = removerAtividade(e->atividades, nome_remover, e->pilhaAtividades);
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
          menuVerAtividade(&atividades->info, e->filaCheckIn);
        }
        free(atividade);
        break;
      case 'Z':
      case 'z':
        int resultado = desfazerRemocaoAtividade(&e->atividades, e->pilhaAtividades);
        if (resultado) {
          printf("Ultima remocao de atividade foi desfeita!\n");
        } else {
          printf("ERRO: Nao foi possivel desfazer a ultima remocao da atividade!");
        }
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

void menuVerAtividade(Atividade *atividade, FilaCheckIn* filaCheckIn) {
  char opcaoMenuVerAtividade = '\0';
  while (opcaoMenuVerAtividade != '0') {
    limparTerminal();

    printf("Titulo: %s\n", atividade->titulo);
    printf("Horario: %s\n\n", atividade->horario);
    printf("1 » Gerenciar Participantes\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoMenuVerAtividade);
    limparTerminal();
    limparBuffer();

    switch(opcaoMenuVerAtividade) {
      case '1':
        menuParticipantesAtividade(atividade, filaCheckIn);
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

void menuParticipantesAtividade(Atividade *atividade, FilaCheckIn* filaCheckIn) {
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
    limparTerminal();
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
        int resultado = inserirParticipante(&atividade->participantes, novoParticipante);
        if (resultado) {
          printf("Participante inserido com sucesso!");
        } else {
          printf("ERRO: Este participante ja foi adicionado");
        }

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
        removerParticipante(&atividade->participantes, matriculaParticipante, atividade->pilhaParticipantes, &filaCheckIn);
        free(matriculaParticipante);
        pausarTerminal();
        break;
      case 'Z':
      case 'z':
        int result = desfazerRemocaoParticipante(&atividade->participantes, atividade->pilhaParticipantes);
        if (result) {
          printf("Participante restaurado com sucesso!");
        }
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
