#ifndef CODIGO_INTERMEDIO_H
#define CODIGO_INTERMEDIO_H

#include "ASTdef.h"

void construirCodigoIntermedio(ASTNodo *nodo);
Simbolo *generarExpresion(ASTNodo *nodo);

#endif