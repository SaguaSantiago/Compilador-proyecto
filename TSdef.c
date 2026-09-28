#include "TSdef.h"
#include <stdlib.h>

void agregarSimboloALista(Simbolo *simbolo, NodoSimbolo *lista) {
  NodoSimbolo *nuevoNodo = (NodoSimbolo *)malloc(sizeof(NodoSimbolo));
  nuevoNodo->simbolo = simbolo;
  nuevoNodo->sig = lista;

  lista = nuevoNodo;
}
