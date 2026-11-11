#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include "enums.h"

typedef struct Opciones {
  const char *entrada;       /* archivo .ctds                          */
  char *salida;              /* base de salida sin extension (strdup)   */
  EtapaCompilacion target;
  Optimizacion opt;
  int debug;
} Opciones;

void imprimirUso(FILE *salida);

int parsearOpciones(int argc, char *argv[], Opciones *op);

void liberarOpciones(Opciones *op);

#endif
