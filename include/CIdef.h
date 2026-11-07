#ifndef CIDEF_H
#define CIDEF_H

#include "TSdef.h"

Instruccion *codigoIntermedio;
int contadorTemp;
int contadorLabel;

typedef struct ListaGlobales { 
    Simbolo *variableGlobal; 
    struct ListaGlobales *sig;
}ListaGlobales; 

ListaGlobales *listaGlobales;

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
    FIN_METODO
}Op;

typedef struct Instruccion{
    Op op; 
    Simbolo *arg1;
    Simbolo *arg2;
    Simbolo *resultado;
    char *label; 
}Instruccion;

Simbolo* nuevoTemporal();

char* nuevoLabel();

void emitir(Instruccion instruccion);

void mostrarCodigo(void);

void agregarGlobal(Simbolo *var); 

#endif