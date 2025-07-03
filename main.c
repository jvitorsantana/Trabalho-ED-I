#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas/struct_evento.h"


void limparTerminal();
void pausarTerminal();
void menuParticipantesAtividade();
void menuVerAtividade();
void menuEditarEvento(Evento e);
void menuAdministracao();
void menuCheckIn();
void menuPrincipal();

int main() {
  menuPrincipal();
  return 0;
}

void menuPrincipal() {
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
        menuAdministracao();
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

void menuAdministracao() {
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
        printf("Opção de criar evento");
        break;
      case '2':
        printf("Opção de listar os eventos");
        break;
      case '3':
        printf("Opção de excluir evento");
        break;
      case '4':
        Evento evento = {"EventoTeste", "22-03"};
        fflush(stdin);
        menuEditarEvento(evento);
        break;
      case '0':
        break;
      }
  }
}

void menuEditarEvento(Evento e) {
  char opcaoMenuEditarEvento = '\0';
  while (opcaoMenuEditarEvento != '0') {
    // fflush(stdin);
    // getchar();
    limparTerminal();
    printf("Você está editando o evento \"%s\"\n\n", e.nome);
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
        printf("Funcao de adicionar atividade aq");
        break;
      case '2':
        printf("Funcao de listar atividade aq");
        break;
      case '3':
        printf("Funcao de remover atividade aq");
        break;
      case '4':
        fflush(stdin);
        menuVerAtividade();
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

void menuVerAtividade() {
  char opcaoMenuVerAtividade = '\0';
  while (opcaoMenuVerAtividade != '0') {
    fflush(stdin);
    limparTerminal();
    getchar();

    printf("Titulo: %s", "MiniCurso MySQL\n");
    printf("Horario: %s", "22:31 as 22:49\n\n");
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
  printf("\nPressione ENTER para continuar...");
  char c;
  while((c = getchar()) != '\n' && c != EOF) {}
  getchar();
}