#ifndef CIDEF_H
#define CIDEF_H

#include <stdio.h>

extern int contadorTemp;
extern int contadorLabel;

typedef enum Op{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    ASSIGN,
    LT,
    GT,
    EQ,
    NE,
    LABEL,
    GOTO,
    IF_FALSE,
    RETURN
}Op;

typedef struct Instruccion{
    Op op; 
    char *arg1;
    char *arg2;
    char *resultado;
    char *label; 
}Instruccion;

char* nuevoTemporal();

char* nuevoLabel();

void emitir(Instruccion instruccion);

void mostrarCodigo(void);

#endif