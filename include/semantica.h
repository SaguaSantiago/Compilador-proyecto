#ifndef SEMANTICA_H
#define SEMANTICA_H
#include "ASTdef.h"
#include "TSdef.h"
#include <stdio.h>

extern TablaSimbolos* tabla;

void analisisSemantico(ASTNodo* nodo);
#endif
