#include "ASTdef.h"
#include "TSdef.h"
#include "semantica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

TablaSimbolos* tabla;
TipoDato retornoEsperado;
NodoSimbolo* listaExpresiones;

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

void analisisSemantico(ASTNodo* nodo){
    if(tabla == NULL) {
        inicializarTs(&tabla);
        retornoEsperado = TIPO_VOID;
    }

    if(nodo == NULL) return;

    Simbolo* encontrado;

    switch (nodo->tipo)
    {
    case NODO_DECL_VAR:
        if(existeSimboloEnNivel(nodo->simbolo->nombre, tabla)){
            lanzarError(nodo, "el símbolo '%s' ya está declarado en este nivel", nodo->simbolo->nombre);
        }
        Simbolo* simbolo_var =  nodo->simbolo;
        
        agregarSimbolo(simbolo_var, tabla);
        
        analisisSemantico(nodo->izq);
        break;
    
    case NODO_DECL_MET:
        if(existeSimboloEnNivel(nodo->simbolo->nombre, tabla)){
            lanzarError(nodo, "el método '%s' ya está declarado en este nivel", nodo->simbolo->nombre);
        }
        retornoEsperado = nodo->simbolo->tipoDato; 

        agregarNivel(tabla);

        analisisSemantico(nodo->izq); //parametros -> NODO_DECL_VAR
        analisisSemantico(nodo->der); //bloque
        
        sacarNivel(tabla);
        
        Simbolo* simbolo_met =  nodo->simbolo;
        agregarSimbolo(simbolo_met, tabla);
        
        break;
    
    case NODO_ASIGNACION:
        analisisSemantico(nodo->izq); 

        encontrado = buscarSimbolo(nodo->izq->simbolo->nombre, tabla);
        fprintf(stderr, "encontrado %s \n", encontrado->nombre); //debugg

        if (encontrado == NULL){
            lanzarError(nodo, "el identificador '%s' no está declarado", nodo->izq->simbolo->nombre);
        }
        
        analisisSemantico(nodo->der); 
        Simbolo* simboloExpresion = nodo->der->simbolo;
        if (encontrado->tipoDato != simboloExpresion->tipoDato){
            lanzarError(nodo, "tipos incompatibles en la asignación a '%s' (%s vs %s)",
                        nodo->izq->simbolo->nombre,
                        nombreTipo(encontrado->tipoDato),
                        nombreTipo(simboloExpresion->tipoDato));
        }
        
        break;
    
    case NODO_IF: 
    case NODO_IF_ELSE:
    case NODO_WHILE:
        if(nodo->izq->simbolo->tipoDato != TIPO_BOOLEAN){
            lanzarError(nodo, "la condición de control debe ser de tipo boolean");
        }
        agregarNivel(tabla);
        retornoEsperado = TIPO_VOID;
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        sacarNivel(tabla);
        break;

    case NODO_BLOQUE:

        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);

        break;
    
    case NODO_RETORNO:
        if (nodo->izq != NULL){
            analisisSemantico(nodo->izq);
            nodo->simbolo->tipoDato = nodo->izq->simbolo->tipoDato;
        }
        
        if(nodo->simbolo->tipoDato != retornoEsperado){
            lanzarError(nodo, "tipo de retorno incompatible: se esperaba %s, se encontró %s",
                        nombreTipo(retornoEsperado),
                        nombreTipo(nodo->simbolo->tipoDato));
        }
        retornoEsperado = TIPO_VOID;
        break;
        
    case NODO_INVOCACION:
        fprintf(stderr, "llegue a invocacion \n"); //debugg
        analisisSemantico(nodo->izq); //id 
        
        if(nodo->izq->simbolo->tipoSimbolo != SIMBOLO_MET_DECL){
            lanzarError(nodo, "'%s' no es un método", nodo->izq->simbolo->nombre);
        }

        NodoSimbolo* expresiones = listaExpresiones;
        free(listaExpresiones);
        listaExpresiones = NULL;

        NodoSimbolo* nodoSimboloActual = expresiones;
        NodoSimbolo* nodoParametroActual = nodo->simbolo->parametros;
        fprintf(stderr, "llegue nodo abajo \n"); //debugg
        
        while (nodoSimboloActual != NULL && nodoParametroActual != NULL) {
            if(nodoSimboloActual->simbolo->tipoDato != nodoParametroActual->simbolo->tipoDato){
                lanzarError(nodo, "tipo de parámetro incorrecto en la invocación a '%s' (%s vs %s)",
                            nodo->izq->simbolo->nombre,
                            nombreTipo(nodoSimboloActual->simbolo->tipoDato),
                            nombreTipo(nodoParametroActual->simbolo->tipoDato));
            }

            nodoSimboloActual = nodoSimboloActual->sig;
            nodoParametroActual = nodoParametroActual->sig;

            if((nodoSimboloActual == NULL && nodoParametroActual != NULL) 
            || nodoSimboloActual != NULL && nodoParametroActual == NULL){
                //lanzar error cantidad de parametros incompatible  
            }

        if(nodoSimboloActual != NULL || nodoParametroActual != NULL){
            lanzarError(nodo, "cantidad de parámetros incompatible en la invocación a '%s'",
                        nodo->izq->simbolo->nombre);
        }


        break;
    
    case NODO_IDENTIFICADOR:
        encontrado = buscarSimbolo(nodo->simbolo->nombre, tabla);
        
        if(encontrado == NULL){
            lanzarError(nodo, "el identificador '%s' no está declarado", nodo->simbolo->nombre);
        }

        nodo->simbolo = encontrado;
        break;

    case NODO_EXPRESIONES:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        
        agregarSimboloALista(nodo->izq->simbolo, &listaExpresiones);
        break;
        
    case NODO_RESTA:
        analisisSemantico(nodo->izq);
        if(nodo->der == NULL){
            // operador unario de la resta
            TipoDato tipo = nodo->izq->simbolo->tipoDato;
            
            if(tipo == TIPO_FLOAT) nodo->simbolo->valor_float = -nodo->simbolo->valor_float; 
            else if (tipo == TIPO_INTEGER) nodo->simbolo->valor = -nodo->simbolo->valor; 
            else {
                lanzarError(nodo, "el operador '-' requiere un tipo numérico");
            }
        } else {
            analisisSemantico(nodo->der);
            if (!procesarOpNumerica(nodo)) {
                lanzarError(nodo, "tipos incompatibles o división por cero en la operación");
            }
        }
        break;
    case NODO_NOT:
        analisisSemantico(nodo->izq);
        if(nodo->izq->simbolo->tipoDato != TIPO_BOOLEAN){
            lanzarError(nodo, "el operador NOT requiere un operando de tipo boolean");
        }
        int valorIzq = nodo->izq->simbolo->valor;
        if(valorIzq == 0) nodo->simbolo->valor = 1;
        else if (valorIzq == 1) nodo->simbolo->valor=0;
        break;

    case NODO_SUMA:
    case NODO_MULTIPLICACION:
    case NODO_DIVISION:
    case NODO_MOD:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);

        if (!procesarOpNumerica(nodo)) {
            lanzarError(nodo, "tipos incompatibles o división por cero en la operación");
        }
        break;
    case NODO_AND:
    case NODO_OR:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        if (!procesarOpBooleano(nodo)) {
            lanzarError(nodo, "los operandos de la operación lógica deben ser boolean");
        }
        break;
    case NODO_IGUALDAD:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        TipoDato tipoIzq = nodo->izq->simbolo->tipoDato;
        TipoDato tipoDer = nodo->der->simbolo->tipoDato;

        if(chequearTipos(TIPO_FLOAT,tipoIzq,tipoDer)){
            nodo->simbolo->valor_float = (nodo->izq->simbolo->valor_float == nodo->der->simbolo->valor_float);
        } else if (chequearTipos(TIPO_INTEGER,tipoIzq,tipoDer)){
            nodo->simbolo->valor = (nodo->izq->simbolo->valor == nodo->der->simbolo->valor);
        } else if(chequearTipos(TIPO_BOOLEAN,tipoIzq,tipoDer)){
            nodo->simbolo->valor = (nodo->izq->simbolo->valor == nodo->der->simbolo->valor);
        }else if(esTipoNumerico(tipoIzq) && esTipoNumerico(tipoDer)){
            float valorIzq = tipoIzq == TIPO_FLOAT
            ? nodo->izq->simbolo->valor_float
            : (float)nodo->izq->simbolo->valor;

            float valorDer = tipoDer == TIPO_FLOAT
                ? nodo->der->simbolo->valor_float
                : (float)nodo->der->simbolo->valor;

            nodo->simbolo->valor = valorIzq == valorDer;
        } else{
            lanzarError(nodo, "los operandos de la igualdad tienen tipos incompatibles (%s vs %s)",
                        nombreTipo(tipoIzq), nombreTipo(tipoDer));
        }
        nodo->simbolo->tipoDato = TIPO_BOOLEAN;
        break;
    case NODO_MENOR:
    case NODO_MAYOR:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        if (!procesarComparacion(nodo)) {
            lanzarError(nodo, "los operandos de la comparación deben ser numéricos");
        }

        break;
    default:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        break;
}
}
}