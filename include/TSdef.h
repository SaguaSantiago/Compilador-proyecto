#ifndef TSDEF_H
#define TSDEF_H
#include "enums.h"
#include "tipos.h"

#define DEFAULT_NIVELES_CANT 10
// TODO: documentar funciones y tipos
typedef struct Simbolo {
  TipoSimbolo tipoSimbolo;
  char *nombre;
  TipoDato tipoDato;
  int valor;
  Simbolo *parametros;
  ASTNodo *nodoBloque;
} Simbolo;

typedef struct Nivel {
  Simbolo *sim;
  struct Nivel *sig;
} NodoNivel;

typedef struct TablaSimbolos {
  NodoNivel *niveles;
  int nivelActual;
} TablaSimbolos;

int agregarSimbolo(Simbolo *nuevoSimbolo, TablaSimbolos *ts);

void inicializarTs(TablaSimbolos **ts);

void agregarNivel(TablaSimbolos *ts);

void sacarNivel(TablaSimbolos *ts);

Simbolo *crearSimbolo(void);

Simbolo *buscarSimbolo(char* nombre, TipoSimbolo tipo, TablaSimbolos *TablaSimbolos);
/**
 * nodo necesario para crear una lista de simbolos
 * (se usa en la creacion del nodo expresiones)
 * */
typedef struct nodo_simbolo {
  Simbolo *simbolo;
  struct nodo_simbolo *sig;
} NodoSimbolo;

void agregarSimboloALista(Simbolo *simbolo, NodoSimbolo **lista);
#endif
