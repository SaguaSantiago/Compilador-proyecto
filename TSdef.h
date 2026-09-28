#ifndef TSDEF_H
#define TSDEF_H
#include "enums.h"

#define DEFAULT_NIVELES_CANT 10
// TODO: documentar funciones y tipos
typedef struct Simbolo {
  TipoSimbolo tipoSimbolo;
  char *nombre;
  TipoDato tipoDato;
  int valor;
  Simbolo *parametros;
} Simbolo;

typedef struct Nivel {
  Simbolo *sim;
  struct Nivel *sig;
} NodoNivel;

typedef struct TablaSimbolo {
  NodoNivel *niveles;
  int nivelActual;
} TablaSimbolo;

void agregarSimbolo(Simbolo *nuevoSimbolo, TablaSimbolo *ts);

void inicializarTs(TablaSimbolo *ts);

void agregarNivel(TablaSimbolo *ts);

void sacarNivel(TablaSimbolo *ts);
#endif
