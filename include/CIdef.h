#ifndef CIDEF_H
#define CIDEF_H

#include "TSdef.h"

typedef enum Op{
    ADD,//0
    SUB,//1
    MUL,//2
    DIV,//3
    MOD,//4
    ASSIGN,//5
    PUSH,//6
    CALL,//7
    LT,//8
    GT,//9
    EQ,//10
    NOT,//11
    AND,//12
    OR,//13
    LABEL,//14
    GOTO,//15
    IF_FALSE,//16
    VAR_GLOBAL,//17
    VAR_LOCAL,//18
    RETURN,//19
    INICIO_METODO,//20
    FIN_METODO//21
}Op;

typedef struct instruccion{
    Op op; 
    Simbolo *arg1;
    Simbolo *arg2;
    Simbolo *resultado;
    char *label; 
}Instruccion;

typedef struct Lista_globales { 
    Simbolo *variableGlobal; 
    struct Lista_globales *sig;
}ListaGlobales; 

typedef struct Lista_offsets{
    int offset;
    struct Lista_offsets *sig;
}ListaOffsets;

Simbolo* nuevoTemporal();

char* nuevoLabel();

void emitir(Instruccion instruccion);

void mostrarCodigo(void);

void agregarGlobal(Simbolo *var); 

int obtenerOffset();

#endif