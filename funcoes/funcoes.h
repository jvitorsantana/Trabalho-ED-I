#ifndef FUNCOES_H
#define FUNCOES_H

// Protótipos das funções auxiliares
void limparTerminal();
void pausarTerminal();
void limparBuffer();
char *digitarNomeEvento();
char *digitarDataEvento();
char *digitarNomeAtividade();
char *digitarHorarioAtividade();
char *digitarNomeParticipante();
char *digitarEmailParticipante();
char *digitarMatriculaParticipante();
int validarHorario(char *horario);
int validarData(char *data);

#endif