#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Verificações de caracteres: isdigit
#include <time.h> // Funções relacionadas a data e hora: time, localtime

#include "funcoes.h"

// Função pra limpar terminal
void limparTerminal() {
  #if defined(_WIN32) || defined(_WIN64)
    system("cls"); //Limpa no Windows
  #else
    system("clear"); //Limpa no Linux/Mac
  #endif
}

// Pausa até o usuario digitar enter
void pausarTerminal() {
  printf("\nPressione ENTER para continuar...\n");
  char c;
  while((c = getchar()) != '\n' && c != EOF) {}
  // getchar();
}

// Limpa buffer do teclado para evitar problemas
void limparBuffer() {
  fflush(stdin);
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

// Solicita ao usuario o nome do evento
char *digitarNomeEvento() {
  char *nome = (char*) malloc(sizeof(char) * 51); // Aloca espaço para uma string de até 50 caracteres
  
  while(1) {
    printf("Digite o nome do evento: ");
    scanf(" %50[^\n]", nome);
    limparBuffer();

    if (strlen(nome) < 3) { //Valida se tem pelomenos 3 caracteres
      printf("ERRO: Preencha o campo corretamente");
      pausarTerminal();
      limparTerminal();
    } else {
      break;
    }
  }

  return nome;
}

// Solicita ao usuario a data do evento
char *digitarDataEvento() {
  char *data = (char *)malloc(sizeof(char) * 11);
  if (data == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite a data do evento: ");
  scanf(" %10s", data);
  limparBuffer();

  return data;
}

// Solicita ao usuario o nome da atividade
char *digitarNomeAtividade() {
  char *nome = (char *)malloc(sizeof(char) * 51); // Aloca espaço para uma string de até 50 caracteres
  if (nome == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  while(1) {
    printf("Digite o nome da atividade: ");
    scanf(" %50[^\n]", nome);
    limparBuffer();
    if (strlen(nome) < 3) { //Valida se tem pelomenos 3 caracteres
      printf("ERRO: Preencha o campo corretamente");
      pausarTerminal();
      limparTerminal();
    } else {
      break;
    }
  }

  return nome;
}

// Solicita ao usuario o horario da atividade
char *digitarHorarioAtividade() {
  char *horario = (char *)malloc(sizeof(char) * 10); // Aloca espaço para uma string de até 10 caracteres
  if (horario == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite o horario da atividade: ");
  scanf(" %9s", horario);
  limparBuffer();

  return horario;
}

// Solicita ao usuario o nome do participante
char *digitarNomeParticipante() {
  char *nome = (char *)malloc(sizeof(char) * 51); // Aloca espaço para uma string de até 50 caracteres
  if (nome == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  while(1) {
    printf("Digite o nome do participante: ");
    scanf(" %50[^\n]", nome);
    limparBuffer();

    if (strlen(nome) < 3) { //Valida se tem pelomenos 3 caracteres
      printf("ERRO: Preencha o campo corretamente");
      pausarTerminal();
      limparTerminal();
    } else {
      break;
    }
  }
  return nome;
}

// Solicita ao usuario o email do participante
char *digitarEmailParticipante() {
  char *email = (char *)malloc(sizeof(char) * 51); // Aloca espaço para uma string de até 50 caracteres
  if (email == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  while(1) {
    printf("Digite o email do participante: ");
    scanf(" %50[^\n]", email);
    limparBuffer();
    
    if (strlen(email) < 6) { //Valida se tem pelomenos 6 caracteres
      printf("ERRO: Preencha o campo corretamente");
      pausarTerminal();
      limparTerminal();
    } else {
      break;
    }
  }

  return email;
}

// Solicita ao usuario a matricula do participante
char *digitarMatriculaParticipante() {
  char *matricula = (char *)malloc(sizeof(char) * 26); // Aloca espaço para uma string de até 25 caracteres
  if (matricula == NULL) {
    printf("Erro ao alocar na memoria");
    exit(1);
    return NULL;
  }

  printf("Digite a matricula do participante: ");
  scanf(" %25s", matricula);
  limparBuffer();

  return matricula;
}

// Valida horario inserido pelo usuario
int validarHorario(char *horario) {
  if(strlen(horario) != 5 || horario[2] != ':') { // Se o tamanho não for 5 ou o terceiro caractere não for ':'
    return 0; 
  }
  // Verifica se os demais caracteres são dígitos
  if(isdigit(horario[0]) && isdigit(horario[1]) && isdigit(horario[3]) && isdigit(horario[4])) { // "HH:MM"
    
    int horas = (horario[0] - '0') * 10 + (horario[1] - '0'); 
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');
    // Converte os caracteres para inteiros com ASCII, 
    // Onde '0' é subtraído para obter o valor numérico, pois '0' tem o valor ASCII 48, '1' tem 49, '2' tem 50...

    // Verifica se a hora está entre 0–23 e os minutos entre 0–59
    if(horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60) {
      return 1; // Horário válido
    }
  }
  return 0; 
}

//Valida data inserida pelo usuario
int validarData(char *data){
  if (strlen(data) != 10 || data[2] != '/' || data[5] != '/'){ // Verifica o formato "dd/mm/aaaa" (10 caracteres)
    return 0;
  }

  char dia[3], mes[3], ano[5]; // Quebra a string data em 3 partes: dia, mês e ano
  strncpy(dia, data, 2);
  dia[2] = '\0';
  strncpy(mes, data + 3, 2);
  mes[2] = '\0';
  strncpy(ano, data + 6, 4);
  ano[4] = '\0';

  for (int i = 0; i < 2; i++){ // Verifica se os caracteres são todos dígitos
    if (!isdigit(dia[i]) || !isdigit(mes[i])){
      return 0;
    }
  }

  for (int i = 0; i < 4; i++){
    if (!isdigit(ano[i])){
      return 0;
    }
  }
  
  // Converte os campos para inteiros
  int diaInt = atoi(dia);
  int mesInt = atoi(mes);
  int anoInt = atoi(ano);

  // Verifica se estão em intervalos válidos
  if (anoInt < 1900 || anoInt > 9999 || mesInt < 1 || mesInt > 12 || diaInt < 1 || diaInt > 31){
    return 0;
  }

  // Dias máximos por mês
  int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Verifica ano bissexto
  if ((anoInt % 4 == 0 && anoInt % 100 !=0) || anoInt % 400 == 0){
    diasNoMes[1] = 29;
  }

  // Verifica se o dia não ultrapassa os dias do mês
  if (diaInt > diasNoMes[mesInt - 1]){
    return 0;
  }

  // Verifica se a data não está no passado
  time_t t = time(NULL);
  struct tm *dataAtual = localtime(&t);

  int diaAtual = dataAtual->tm_mday;
  int mesAtual = dataAtual->tm_mon + 1;
  int anoAtual = dataAtual->tm_year + 1900;

  if (anoInt < anoAtual){
    return 0;
  }

  if (anoInt == anoAtual && mesInt < mesAtual){
    return 0;
  }

  if (anoInt == anoAtual && mesInt == mesAtual && diaInt < diaAtual){
    return 0;
  }

  return 1;
}