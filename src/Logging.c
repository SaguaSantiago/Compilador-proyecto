#include "Logging.h"

#include <stdarg.h>
#include <stdio.h>

static int logging_enabled = 0;

void logging_set_enabled(int enabled) {
    logging_enabled = enabled != 0;
}

void log_debug(const char *format, ...) {
    va_list args;

    if (!logging_enabled) {
        return;
    }

    printf("[debug] ");
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    putchar('\n');
}

char* tipo_nodo_string(TipoNodo tipo){
    switch (tipo)
    {
        case NODO_ROOT: return "NODO_ROOT";
        case NODO_DECL_VAR: return "NODO_DECL_VAR";
        case NODO_DECL_MET: return "NODO_DECL_MET";
        case NODO_DECLS: return "NODO_DECLS";
        case NODO_PARAM_DECL: return "NODO_PARAM_DECL";
        case NODO_EXPRESIONES: return "NODO_EXPRESIONES";
        case NODO_INVOCACION: return "NODO_INVOCACION";
        case NODO_SENTENCIAS: return "NODO_SENTENCIAS";
        case NODO_ASIGNACION: return "NODO_ASIGNACION";
        case NODO_IF: return "NODO_IF";
        case NODO_IF_ELSE: return "NODO_IF_ELSE";
        case NODO_BLOQUES_IF: return "NODO_BLOQUES_IF";
        case NODO_WHILE: return "NODO_WHILE";
        case NODO_BLOQUE: return "NODO_BLOQUE";
        case NODO_RETORNO: return "NODO_RETORNO";
        case NODO_SUMA: return "NODO_SUMA";
        case NODO_MULTIPLICACION: return "NODO_MULTIPLICACION";
        case NODO_IDENTIFICADOR: return "NODO_IDENTIFICADOR";
        case NODO_RESTA: return "NODO_RESTA";
        case NODO_DIVISION: return "NODO_DIVISION";
        case NODO_MOD: return "NODO_MOD";
        case NODO_AND: return "NODO_AND";
        case NODO_OR: return "NODO_OR";
        case NODO_NOT: return "NODO_NOT";
        case NODO_IGUALDAD: return "NODO_IGUALDAD";
        case NODO_MAYOR: return "NODO_MAYOR";
        case NODO_MENOR: return "NODO_MENOR";
        case NODO_FLOAT: return "NODO_FLOAT";
        case NODO_INT: return "NODO_INT";
        case NODO_BOOLEAN: return "NODO_BOOLEAN";
        case NODO_PROGRAMA: return "NODO_PROGRAMA";
        default: return NULL;
    }
}

char* tipo_simbolo_string(TipoSimbolo tipo){
    switch(tipo){
        case SIMBOLO_TEMPORAL: return "TEMPORAL";
        case SIMBOLO_INVOCACION: return "INVOCACION";
        case SIMBOLO_INTEGER_LITERAL: return "LITERAL INTEGER";
        case SIMBOLO_FLOAT_LITERAL: return "LITERAL FLOAT";
        case SIMBOLO_BOOLEAN_LITERAL: return "LITERAL BOOLEAN";
        case SIMBOLO_IDENTIFICADOR: return "IDENTIFICADOR";
        case SIMBOLO_VAR_GLOBAL: return "VARIABLE GLOBAL";
        case SIMBOLO_VAR_LOCAL: return "VARIABLE LOCAL"; 
        case SIMBOLO_METODO: return "METODO";
        case SIMBOLO_MAIN: return "MAIN";
        case SIMBOLO_VOID: return "VOID";
        case SIMBOLO_RETURN: return "RETURN";
        case SIMBOLO_SUMA: return "SUMA";
        case SIMBOLO_MULTIPLICACION: return "MULTIPLICACION";
        case SIMBOLO_MOD: return "MOD";
        case SIMBOLO_RESTA: return "RESTA";
        case SIMBOLO_DIV: return "DIV";
        case SIMBOLO_ASIGNACION: return "ASIGNACION";
        case SIMBOLO_IF: return "IF";
        case SIMBOLO_IF_ELSE: return "IF_ELSE";
        case SIMBOLO_WHILE: return "WHILE";
        case SIMBOLO_AND: return "AND";
        case SIMBOLO_OR: return "OR";
        case SIMBOLO_NOT: return "NOT";
        case SIMBOLO_MAYOR: return "MAYOR";
        case SIMBOLO_MENOR: return "MENOR";
        case SIMBOLO_IGUALDAD: return "IGUALDAD";
        case SIMBOLO_VAR_DECL: return "DECLARACION DE VARIABLE";
        case SIMBOLO_MET_DECL: return "DECLARACION DE METODO";
        default: return NULL;
    }
}
