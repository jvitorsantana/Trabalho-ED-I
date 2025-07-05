#ifndef STRUCT_PARTICIPANTE_H
#define STRUCT_PARTICIPANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Participante {
  char matricula[26];
  char nome[51];
  char email[51];
} Participante;

#endif