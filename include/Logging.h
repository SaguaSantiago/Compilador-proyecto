#ifndef LOGGING_H
#define LOGGING_H

#include "TSdef.h"
#include "ASTdef.h"

void logging_set_enabled(int enabled);
void log_debug(const char *format, ...);

char* tipo_nodo_string(TipoNodo tipo);

char* tipo_simbolo_string(TipoSimbolo tipo);

#endif