#include "CIdef.h"
#include <stdio.h>
#include "codigoIntermedio.h"
#include "TSdef.h"

//procesa los nodos que representan instrucciones del programa que no generan nuevos valores: if, while, etc. 
void construirCodigoIntermedio(ASTNodo *nodo){
    if(nodo == NULL) return;

    switch (nodo->tipo)
    {
    case NODO_DECL_MET:
        
        break; 
    case NODO_ASIGNACION:
        ASTNodo *expresion = nodo->der;
        
        Simbolo *expresionAsignacion = generarExpresion(expresion);

        Instruccion inst = {
            .op = ASSIGN,
            .arg1 = expresionAsignacion, 
            .arg2 = NULL,
            .resultado = nodo->izq->simbolo,
            .label = NULL
        };

        emitir(inst);
        break;
    
    case NODO_IF: 
    case NODO_IF_ELSE:
        ASTNodo *condicion = nodo->izq;
        ASTNodo *bloquesIf = nodo->der;

        ASTNodo *bloqueIf = bloquesIf->izq;
        ASTNodo *bloqueElse = bloquesIf->der;

        char *etiquetaElse = nuevoLabel();
        char *etiquetaFin = nuevoLabel();

        Instruccion saltoElse = {
            .op = IF_FALSE,
            .arg1 = condicion->simbolo,
            .arg2 = NULL,
            .resultado = NULL,
            .label = etiquetaElse
        };

        emitir(saltoElse);

        construirCodigoIntermedio(bloqueIf);

        Instruccion saltoFin = {
            .op = GOTO,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = etiquetaFin
        };

        emitir(saltoFin);

        Instruccion inicioElse = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = etiquetaElse
        };

        emitir(inicioElse);

        construirCodigoIntermedio(bloqueElse);

        Instruccion fin = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = etiquetaFin
        };

        emitir(fin);

        break; 
    case NODO_WHILE:
        ASTNodo* condicionWhile = nodo->izq;
        ASTNodo* bloqueWhile = nodo->der;

        
        char *inicioWhileLabel = nuevoLabel();
        char *finWhileLabel = nuevoLabel();

        Instruccion inicioWhile = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = inicioWhileLabel
        };
        emitir(inicioWhile);

        Instruccion saltoFinWhile = {
            .op = IF_FALSE,
            .arg1 = condicionWhile->simbolo,
            .arg2 = NULL,
            .resultado = NULL,
            .label = finWhileLabel
        };
        emitir(saltoFinWhile);

        construirCodigoIntermedio(bloqueWhile);

        Instruccion saltoInicioWhile = {
            .op = GOTO,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = inicioWhileLabel
        };
        emitir(saltoInicioWhile);

        Instruccion finWhile = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = finWhileLabel
        };
        emitir(finWhile);
        break;

    case NODO_BLOQUE:

        break;
    
    case NODO_RETORNO:
        
        Simbolo *expresionRetorno = generarExpresion(nodo->izq);

        Instruccion instRetorno = {
            .op = RETURN,
            .arg1 = expresionRetorno,
            .arg2 = NULL,
            .resultado = nodo->simbolo,
            .label = NULL,
        };

        emitir(instRetorno); 
        break;
        
    case NODO_INVOCACION:
        
        break;

    
    default:
        construirCodigoIntermedio(nodo->izq);
        construirCodigoIntermedio(nodo->der);
        break;

    }
}

//procesa los nodos que generan un nuevo valor, en general, los que generar nuevos temporales 
Simbolo *generarExpresion(ASTNodo *nodo){
    if (nodo == NULL) return NULL; 

    switch (nodo->tipo)
    {
    case NODO_IDENTIFICADOR:
        return nodo->simbolo;
        break;
    
    case NODO_SUMA:
        Simbolo *expresionSumaIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionSumaDerecha = generarExpresion(nodo->der);

        Simbolo *sumTemp = nuevoTemporal(); 
        sumTemp->tipoDato = nodo->tipo; 

        Instruccion sumInst = { 
            .op = ADD,
            .arg1 = expresionSumaIzquierda,
            .arg2 = expresionSumaDerecha,
            .resultado = sumTemp,
            .label = NULL,
        };

        emitir(sumInst);

        return sumTemp;
        break;
    case NODO_RESTA:
        Simbolo *expresionRestaIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionRestaDerecha = generarExpresion(nodo->der);

        Simbolo *restaTemp = nuevoTemporal(); 
        restaTemp->tipoDato = nodo->tipo; 

        Instruccion restaInst = { 
            .op = SUB,
            .arg1 = expresionRestaIzquierda,
            .arg2 = expresionRestaDerecha,
            .resultado = restaTemp,
            .label = NULL,
        };

        emitir(restaInst);

        return restaTemp;
        break;
    case NODO_MULTIPLICACION:
        Simbolo *expresionMultIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionMultDerecha = generarExpresion(nodo->der);

        Simbolo *multTemp = nuevoTemporal(); 
        multTemp->tipoDato = nodo->tipo; 

        Instruccion multInst = { 
            .op = MUL,
            .arg1 = expresionMultIzquierda,
            .arg2 = expresionMultDerecha,
            .resultado = multTemp,
            .label = NULL,
        };

        emitir(multInst);

        return multTemp;
        break;
    case NODO_DIVISION:
        Simbolo *expresionDivIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionDivDerecha = generarExpresion(nodo->der);

        Simbolo *divTemp = nuevoTemporal(); 
        divTemp->tipoDato = nodo->tipo; 

        Instruccion divInst = { 
            .op = DIV,
            .arg1 = expresionDivIzquierda,
            .arg2 = expresionDivDerecha,
            .resultado = divTemp,
            .label = NULL,
        };

        emitir(divInst);

        return divTemp;
        break;
    case NODO_MOD:
        Simbolo *expresionModIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionModDerecha = generarExpresion(nodo->der);

        Simbolo *modTemp = nuevoTemporal(); 
        modTemp->tipoDato = nodo->tipo; 

        Instruccion modInst = { 
            .op = MOD,
            .arg1 = expresionModIzquierda,
            .arg2 = expresionModDerecha,
            .resultado = modTemp,
            .label = NULL,
        };

        emitir(modInst);

        return modTemp;
        break;
        
    case NODO_NOT:
        Simbolo *expresionNotIzquierda = generarExpresion(nodo->izq);

        Simbolo *notTemp = nuevoTemporal(); 
        notTemp->tipoDato = nodo->tipo; 

        Instruccion notInst = { 
            .op = NOT,
            .arg1 = expresionNotIzquierda,
            .arg2 = NULL,
            .resultado = notTemp,
            .label = NULL,
        };

        emitir(notInst);

        return notTemp;
        break;
    case NODO_AND:
        Simbolo *expresionAndIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionAndDerecha = generarExpresion(nodo->der);

        Simbolo *andTemp = nuevoTemporal(); 
        andTemp->tipoDato = nodo->tipo; 

        Instruccion andInst = { 
            .op = AND,
            .arg1 = expresionAndIzquierda,
            .arg2 = expresionAndDerecha,
            .resultado = andTemp,
            .label = NULL,
        };

        emitir(andInst);

        return andTemp;
        break;
    case NODO_OR:
    case NODO_IGUALDAD:
    case NODO_MENOR:
    case NODO_MAYOR:
        
        break;
    default:


        break;
    }
}