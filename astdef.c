
#include "ASTdef.h"
#include <stdlib.h>

ASTNodo *crearNodo(TipoNodo tipo, Simbolo *simbolo, ASTNodo *izq, ASTNodo *der) {
  ASTNodo *nodo = (ASTNodo *)malloc(sizeof(ASTNodo));

  nodo->tipo = tipo;
  nodo->simbolo = simbolo;
  nodo->izq = izq;
  nodo->der = der;

  return nodo;
}
