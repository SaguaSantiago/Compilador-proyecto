#include "TSdef.h"
#include <stdlib.h>

void agregarSimboloALista(Simbolo *simbolo, NodoSimbolo *lista) {
  NodoSimbolo *nuevoNodo = (NodoSimbolo *)malloc(sizeof(NodoSimbolo));
  nuevoNodo->simbolo = simbolo;
  nuevoNodo->sig = lista;

  lista = nuevoNodo;
}

Simbolo *crearSimbolo() {
  Simbolo *nuevoSimbolo = (Simbolo *)malloc(sizeof(Simbolo));
  nuevoSimbolo->nombre = NULL;
  nuevoSimbolo->parametros = NULL;
  nuevoSimbolo->valor = 0;

  return nuevoSimbolo;
}
