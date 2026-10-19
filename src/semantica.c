#include "ASTdef.h"
#include "TSdef.h"
#include "semantica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

TablaSimbolos* tabla;

void analisisSemantico(ASTNodo* nodo){
    
    if(tabla == NULL) {
        inicializarTs(&tabla);
    }
    
    NodoNivel *nivelActual = obtenerNivelActual(tabla);


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
        agregarNivel(tabla);

        nivelActual=obtenerNivelActual(tabla);
        nivelActual->retornoEsperado = nodo->simbolo->tipoDato; 

        analisisSemantico(nodo->izq); //parametros -> NODO_DECL_VAR
        analisisSemantico(nodo->der); //bloque
        
        sacarNivel(tabla);
        
        Simbolo* simbolo_met =  nodo->simbolo;
        agregarSimbolo(simbolo_met, tabla);
        
        break;
    
    case NODO_ASIGNACION:
        analisisSemantico(nodo->izq); 

        encontrado = buscarSimbolo(nodo->izq->simbolo->nombre, tabla);

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

        nivelActual=obtenerNivelActual(tabla);
        TipoDato retornoHeredado = nivelActual->retornoEsperado;

        agregarNivel(tabla);

        nivelActual=obtenerNivelActual(tabla);
        nivelActual->retornoEsperado = retornoHeredado;

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

        nivelActual=obtenerNivelActual(tabla);
        TipoDato retornoEsperado = nivelActual->retornoEsperado;
        
        if(nodo->simbolo->tipoDato != retornoEsperado){
            lanzarError(nodo, "tipo de retorno incompatible: se esperaba %s, se encontró %s",
                        nombreTipo(retornoEsperado),
                        nombreTipo(nodo->simbolo->tipoDato));
        }

        break;
        
    case NODO_INVOCACION:
        analisisSemantico(nodo->izq); //id 
        Simbolo* metodo = nodo->izq->simbolo; 
        if (metodo->tipoSimbolo != SIMBOLO_MET_DECL){
            lanzarError(nodo, "'%s no es un metodo", nodo->izq->simbolo->nombre);
        }

        nodo->simbolo->tipoDato = metodo->tipoDato;

        NodoSimbolo* param = metodo->parametros;
        ASTNodo* arg = nodo->der;

        while (arg != NULL && param != NULL) {
            ASTNodo* expr = (arg->tipo == NODO_EXPRESIONES) ? arg->izq : arg;
            analisisSemantico(expr);
            if (expr->simbolo->tipoDato != param->simbolo->tipoDato)
                lanzarError(nodo, "tipo de parámetro incorrecto en la invocación a '%s' (%s vs %s)",
                            metodo->nombre, nombreTipo(expr->simbolo->tipoDato),
                            nombreTipo(param->simbolo->tipoDato));
            param = param->sig;
            arg   = (arg->tipo == NODO_EXPRESIONES) ? arg->der : NULL;
        }
        if (arg != NULL || param != NULL)
            lanzarError(nodo, "cantidad de parámetros incompatible en la invocación a '%s'", metodo->nombre);
        break;

    
    case NODO_IDENTIFICADOR:
        encontrado = buscarSimbolo(nodo->simbolo->nombre, tabla);
        
        if(encontrado == NULL){
            lanzarError(nodo, "el identificador '%s' no está declarado", nodo->simbolo->nombre);
        }

        nodo->simbolo = encontrado;
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