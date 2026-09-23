
#include "ASTdef.h"
#include <stdlib.h>

Nodo *crearNodo(TipoNodo tipo, Simbolo *simbolo, Nodo *izq, Nodo *der) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));

  nodo->tipo = tipo;
  nodo->simbolo = simbolo;
  nodo->izq = izq;
  nodo->der = der;

  return nodo;
}
