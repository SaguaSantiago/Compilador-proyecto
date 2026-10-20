#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TSdef.h"
#include "ASTdef.h"


const char* nombreTipo(TipoDato tipo){
    switch (tipo) {
    case TIPO_INTEGER: return "int";
    case TIPO_FLOAT:   return "float";
    case TIPO_BOOLEAN: return "boolean";
    case TIPO_VOID:    return "void";
    default:           return "desconocido";
    }
}
void lanzarError(ASTNodo *nodo, const char *formato, ...){
    va_list args;

    fprintf(stderr, "Error semántico en la línea %d: ", nodo->linea);

    va_start(args, formato);
    vfprintf(stderr, formato, args);
    va_end(args);

    fprintf(stderr, "\n");
    exit(1);
}

int chequearTipos(TipoDato tipoEsperado, int cantidadTipos,...){
    va_list tipos;

    va_start(tipos, cantidadTipos);
    
    for(int i = 0; i<cantidadTipos; i++){
        TipoDato tipoActual = va_arg(tipos, TipoDato);
        if(tipoActual != tipoEsperado) {
            return 0;
        }
    }
    va_end(tipos);
    return 1;
}

int esTipoNumerico(TipoDato tipo){
    return (tipo == TIPO_INTEGER || tipo == TIPO_FLOAT);
}

int procesarOpBooleano(ASTNodo *nodo){
    if (nodo == NULL || nodo->simbolo == NULL ||
        nodo->izq == NULL || nodo->der == NULL ||
        nodo->izq->simbolo == NULL || nodo->der->simbolo == NULL) {
        return 0;
    }

    Simbolo *izquierdo = nodo->izq->simbolo;
    Simbolo *derecho = nodo->der->simbolo;
    TipoDato tipoIzq = izquierdo->tipoDato;
    TipoDato tipoDer = derecho->tipoDato;

    if (tipoIzq != TIPO_BOOLEAN || tipoDer != TIPO_BOOLEAN) {
        return 0;
    }

    int valorIzq = izquierdo->valor;
    int valorDer = derecho->valor;
    int resultado;

    switch (nodo->tipo) {
    case NODO_AND:
        if (valorIzq == 1 && valorDer == 1) {
            resultado = 1;
        } else {
            resultado = 0;
        }
        break;

    case NODO_OR:
        if (valorIzq == 0 && valorDer == 0) {
            resultado = 0;
        } else {
            resultado = 1;
        }
        break;

    default:
        return 0;
    }
    nodo->simbolo->tipoDato = TIPO_BOOLEAN;
    nodo->simbolo->valor = resultado;

    return 1;
}
int procesarComparacion(ASTNodo *nodo){
    if (nodo == NULL || nodo->simbolo == NULL ||
        nodo->izq == NULL || nodo->der == NULL ||
        nodo->izq->simbolo == NULL || nodo->der->simbolo == NULL) {
        return 0;
    }
    Simbolo *izquierdo = nodo->izq->simbolo;
    Simbolo *derecho = nodo->der->simbolo;
    TipoDato tipoIzq = izquierdo->tipoDato;
    TipoDato tipoDer = derecho->tipoDato;

    if (!esTipoNumerico(tipoIzq) || !esTipoNumerico(tipoDer)) {
        return 0;
    }

    int usaFloat = tipoIzq == TIPO_FLOAT || tipoDer == TIPO_FLOAT;
    if (usaFloat) {
        float valorIzq = tipoIzq == TIPO_FLOAT
            ? izquierdo->valor_float : (float)izquierdo->valor;
        float valorDer = tipoDer == TIPO_FLOAT
            ? derecho->valor_float : (float)derecho->valor;
        int resultado = 0;

        switch (nodo->tipo) {
        case NODO_MENOR:
            resultado = valorIzq < valorDer;
            break;
        case NODO_MAYOR:
            resultado = valorIzq > valorDer;
            break;
        default:
            return 0;
        }

        nodo->simbolo->tipoDato = TIPO_INTEGER;
        nodo->simbolo->valor = resultado;
    } else {
        int valorIzq = izquierdo->valor;
        int valorDer = derecho->valor;
        int resultado = 0;

        switch (nodo->tipo) {
        case NODO_MENOR:
            resultado = valorIzq < valorDer;
            break;
        case NODO_MAYOR:
            resultado = valorIzq > valorDer;
            break;
        default:
            return 0;
        }

        nodo->simbolo->tipoDato = TIPO_INTEGER;
        nodo->simbolo->valor = resultado;
    }

    return 1;
}

int procesarOpNumerica(ASTNodo *nodo) {
    if (nodo == NULL || nodo->simbolo == NULL ||
        nodo->izq == NULL || nodo->der == NULL ||
        nodo->izq->simbolo == NULL || nodo->der->simbolo == NULL) {
        return 0;
    }

    Simbolo *izquierdo = nodo->izq->simbolo;
    Simbolo *derecho = nodo->der->simbolo;
    TipoDato tipoIzq = izquierdo->tipoDato;
    TipoDato tipoDer = derecho->tipoDato;

    if (!esTipoNumerico(tipoIzq) || !esTipoNumerico(tipoDer)) {
        return 0;
    }

    int tiposMixtos = tipoIzq != tipoDer;

    if (tiposMixtos &&
        (nodo->tipo == NODO_DIVISION || nodo->tipo == NODO_MOD)) {
        return 0;
    }

    int usaFloat = tipoIzq == TIPO_FLOAT || tipoDer == TIPO_FLOAT;

    if (usaFloat) {
        float valorIzq = tipoIzq == TIPO_FLOAT
            ? izquierdo->valor_float : (float)izquierdo->valor;
        float valorDer = tipoDer == TIPO_FLOAT
            ? derecho->valor_float : (float)derecho->valor;
        float resultado;

        switch (nodo->tipo) {
        case NODO_SUMA:
            resultado = valorIzq + valorDer;
            break;
        case NODO_RESTA:
            resultado = valorIzq - valorDer;
            break;
        case NODO_MULTIPLICACION:
            resultado = valorIzq * valorDer;
            break;
        case NODO_DIVISION:
            if (valorDer == 0.0f) return 0;
            resultado = valorIzq / valorDer;
            break;
        case NODO_MOD:
            if (valorDer == 0.0f) return 0;
            resultado = fmodf(valorIzq, valorDer);
            break;
        default:
            return 0;
        }

        nodo->simbolo->tipoDato = TIPO_FLOAT;
        nodo->simbolo->valor_float = resultado;
    } else {
        int valorIzq = izquierdo->valor;
        int valorDer = derecho->valor;
        int resultado;

        switch (nodo->tipo) {
        case NODO_SUMA:
            resultado = valorIzq + valorDer;
            break;
        case NODO_RESTA:
            resultado = valorIzq - valorDer;
            break;
        case NODO_MULTIPLICACION:
            resultado = valorIzq * valorDer;
            break;
        case NODO_DIVISION:
            if (valorDer == 0) return 0;
            resultado = valorIzq / valorDer;
            break;
        case NODO_MOD:
            if (valorDer == 0) return 0;
            resultado = valorIzq % valorDer;
            break;
        default:
            return 0;
        }

        nodo->simbolo->tipoDato = TIPO_INTEGER;
        nodo->simbolo->valor = resultado;
    }

    return 1;
}