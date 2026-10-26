#include "CIdef.h"
#include <stdio.h>
#include "codigoIntermedio.h"
#include "TSdef.h"

void construirCodigoIntermedio(ASTNodo *nodo){
    if(nodo == NULL) return;

    switch (nodo->tipo)
    {
    case NODO_ASIGNACION:
        char *valor = generarExpresion(nodo->izq);
        char *destino = nodo->izq->simbolo->nombre;

        Instruccion inst = {
            .op = ASSIGN,
            .arg1 = valor, 
            .arg2 = NULL,
            .resultado = destino,
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

        char *resultadoCondicion = generarExpresion(condicion);

        char *etiquetaElse = nuevoLabel();
        char *etiquetaFin = nuevoLabel();

        Instruccion saltoElse = {
            .op = IF_FALSE,
            .arg1 = resultadoCondicion,
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

        char resCondicionWhile = generarExpresion(condicionWhile);
        
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
            .arg1 = resCondicionWhile,
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
        break;
        
    case NODO_INVOCACION:
        break;

    
    case NODO_IDENTIFICADOR:
    
        break;
        
    case NODO_RESTA:
    
        break;
    case NODO_NOT:

        break;

    case NODO_SUMA:
    case NODO_MULTIPLICACION:
    case NODO_DIVISION:
    case NODO_MOD:
        
        break;
    case NODO_AND:
    case NODO_OR:
        
        break;
    case NODO_IGUALDAD:
       
        break;
    case NODO_MENOR:
    case NODO_MAYOR:
        
        break;
    default:
        construirCodigoIntermedio(nodo->izq);
        construirCodigoIntermedio(nodo->der);
        break;

    }
}