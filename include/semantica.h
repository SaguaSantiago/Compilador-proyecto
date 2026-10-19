#ifndef SEMANTICA_H
#define SEMANTICA_H
#include "ASTdef.h"
#include "TSdef.h"
#include <stdio.h>

extern TablaSimbolos* tabla;
extern TipoDato retornoEsperado;

void analisisSemantico(ASTNodo* nodo);
#endif
