#ifndef STRUCT_PARTICIPANTE_H
#define STRUCT_PARTICIPANTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Participante {
  char matricula[25];
  char nome[50];
  char email[50];
} Participante;

#endif