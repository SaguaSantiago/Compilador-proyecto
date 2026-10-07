
#include "ASTdef.h"
#include <stdlib.h>

extern int yylineno;

ASTNodo *crearASTNodo(TipoNodo tipo, Simbolo *simbolo, ASTNodo *izq,
                   ASTNodo *der) {
  ASTNodo *nodo = (ASTNodo *)malloc(sizeof(ASTNodo));

  nodo->tipo = tipo;
  nodo->simbolo = simbolo;
  nodo->linea = yylineno;
  nodo->izq = izq;
  nodo->der = der;

  return nodo;
}
