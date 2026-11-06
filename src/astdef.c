
#include "ASTdef.h"
#include "Logging.h"
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

  if(simbolo != NULL) log_debug("-[PARSER]- ASTNodo de tipo %s creado --> Simbolo de tipo %s", tipo_nodo_string(tipo), tipo_simbolo_string(nodo->simbolo->tipoSimbolo));
  else log_debug("-[PARSER]- ASTNodo de tipo %s creado", tipo_nodo_string(tipo));
  
  return nodo;
}
