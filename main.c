#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes/funcoes.h"
#include "estruturas/struct_evento.h"
#include "listas/lista_circular_eventos.h"
#include "listas/lista_encadeada_atividade.h"

void limparTerminal();
void pausarTerminal();
void menuParticipantesAtividade();
void menuVerAtividade();
void menuEditarEvento(Evento *e);
void menuAdministracao(ListaEventos **listaEventos);
void menuCheckIn();
void menuPrincipal(ListaEventos **listaEventos);

int main() {
  ListaEventos *listaEventos = inicializarListaEventos();
  menuPrincipal(&listaEventos);
  return 0;
}

void menuPrincipal(ListaEventos **listaEventos) {
  char opcao = '\0';
  while (opcao != '0') {
    fflush(stdin);
    limparTerminal();

    printf("Seja bem-vindo ao Sistema PicaDuraMole Gerenciador de Eventos\n");
    printf("Escolha uma das opcoes abaixo:\n");
    printf("1 » Administracao\n");
    printf("2 » Realizar Check-In\n");
    printf("0 » Sair\n");
    printf("➜ ");
    
    scanf("%c", &opcao);

    switch(opcao) {
      case '1':
        menuAdministracao(listaEventos);
        getchar();
        break;
      case '2':
        menuCheckIn();
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
    fflush(stdin);
    getchar();
    limparTerminal();
    printf("Seja bem-vindo ao painel administrativo!\n\n");
    printf("1 » Criar Evento\n");
    printf("2 » Listar Eventos\n");
    printf("3 » Excluir Evento\n");
    printf("4 » Editar Evento\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf(" %c", &opcaoAdmin);

    switch(opcaoAdmin) {
      case '1':
        getchar();
        fflush(stdin);
        char *nome_inserir = digitarNomeEvento();
        fflush(stdin);
        getchar();
        char *data_inserir = digitarDataEvento();
        *listaEventos = inserir_evento(*listaEventos, nome_inserir, data_inserir);
        free(nome_inserir);
        free(data_inserir);
        pausarTerminal();
        break;
      case '2':
        imprimir_lista_circular(*listaEventos);
        pausarTerminal();
        break;
      case '3':
        getchar();
        char *nome_remover = digitarNomeEvento();
        *listaEventos = remover_evento(*listaEventos, nome_remover);
        free(nome_remover);
        pausarTerminal();
        break;
      case '4':
        getchar();
        char *nome_evento = digitarNomeEvento();
        ListaEventos *eventos = buscar_evento(*listaEventos, nome_evento);
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
    fflush(stdin);
    getchar();
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

    switch(opcaoMenuEditarEvento) {
      case '1':
        getchar();
        char *nome_atividade = digitarNomeAtividade();
        fflush(stdin);
        getchar();
        char *horario_atividade = digitarHorarioAtividade();
        fflush(stdin);

        e->atividades = inserirAtividade(e->atividades, nome_atividade, horario_atividade);
        free(nome_atividade);
        free(horario_atividade);
        break;
      case '2':
        limparTerminal();
        exibirAtividades(e->atividades);
        pausarTerminal();
        break;
      case '3':
        getchar();
        fflush(stdin);
        char *nome_remover = digitarNomeAtividade();
        e->atividades = removerAtividade(e->atividades, nome_remover);
        free(nome_remover);
        pausarTerminal();
        break;
      case '4':
        getchar();
        fflush(stdin);
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
    fflush(stdin);
    limparTerminal();
    getchar();

    printf("Titulo: %s\n", atividade->titulo);
    printf("Horario: %s\n\n", atividade->horario);
    printf("1 » Gerenciar Participantes\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf("%c", &opcaoMenuVerAtividade);
    
    switch(opcaoMenuVerAtividade) {
      case '1':
        menuParticipantesAtividade();
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

void menuParticipantesAtividade() {
  char opcaoMenuParticipantesAtividade = '\0';
  while (opcaoMenuParticipantesAtividade != '0') {
    fflush(stdin);
    limparTerminal();
    getchar();

    printf("Voce esta gerenciando os participantes da ativiade \"%s\"\n\n", "MiniCurso MySQL");
    printf("1 » Cadastrar participante\n");
    printf("2 » Listar participantes\n");
    printf("3 » Remover participante\n");
    printf("Z » Desfazer a ultima remocao\n");
    printf("0 » Voltar\n");
    printf("➜ ");

    scanf("%c", &opcaoMenuParticipantesAtividade);

    switch(opcaoMenuParticipantesAtividade) {
      case '1':
        break;
      case '2':
        break;
      case '3':
        break;
      case 'Z':
      case 'z':
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

void menuCheckIn() {
  fflush(stdin);
  getchar();
  limparTerminal();

  char matricula[50];
  char nomeEvento[100];

  printf("Digite o nome do evento: ");
  scanf("%100[^\n]", nomeEvento);
  getchar();
  printf("Digite a sua matricula: ");
  scanf("%s", matricula);

  int resultado = 1;

  if (resultado) {
    printf("Check-In realizado com sucesso!");
  } else {
    printf("Nao foi possivel realizar o check-in");
  }

  pausarTerminal();
}

void limparTerminal() {
  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #else
    printf("\033[H\033[2J");
    fflush(stdout);
  #endif
}

void pausarTerminal() {
  printf("\nPressione ENTER para continuar...\n");
  char c;
  while((c = getchar()) != '\n' && c != EOF) {}
  getchar();
}