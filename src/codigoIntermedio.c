#include "CIdef.h"
#include <stdio.h>
#include "codigoIntermedio.h"
#include "TSdef.h"
#include <string.h>

//procesa los nodos que representan instrucciones del programa que no generan nuevos valores: if, while, etc. 
void construirCodigoIntermedio(ASTNodo *nodo){
    if(nodo == NULL) return;

    switch (nodo->tipo)
    {
    case NODO_DECL_VAR: 
        if (nodo->simbolo->esGlobal){
            Instruccion globalVarDecl = {
                .op = VAR_GLOBAL,
                .arg1 = nodo->simbolo,
                .arg2 = NULL,
                .resultado = NULL,
                .label = NULL
            };

            emitir(globalVarDecl);
        }
        else{
            Instruccion localVarDecl = {
                .op = VAR_LOCAL,
                .arg1 = nodo->simbolo,
                .arg2 = NULL,
                .resultado = NULL,
                .label = NULL
            };

            emitir(localVarDecl);
        }
        
        break;
    case NODO_DECL_MET:
        ASTNodo *parametros = nodo->izq;
        ASTNodo *bloqueMetodo = nodo->der;

        construirCodigoIntermedio(parametros);

        Instruccion inicioMetodo = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL, 
            .label = strdup(nodo->simbolo->nombre)
        };

        emitir(inicioMetodo);

        construirCodigoIntermedio(bloqueMetodo);

        char* etiquetaFinMetodo = nuevoLabel(); 
        Instruccion finMetodo = {
            .op = LABEL,
            .arg1 = NULL, 
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaFinMetodo)
        };

        emitir(finMetodo); 
        
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
        ASTNodo *condicionIf = nodo->izq;
  
        char *etiquetaFinIf = nuevoLabel();

        Simbolo *expresionCondicionIf = generarExpresion(condicionIf);

        Instruccion saltoFinIf = {
            .op = IF_FALSE,
            .arg1 = expresionCondicionIf,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaFinIf)
        };

        emitir(saltoFinIf);

        construirCodigoIntermedio(nodo->der);

        Instruccion finIf = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaFinIf)
        };

        emitir(finIf);

        break;
    case NODO_IF_ELSE:
        ASTNodo *condicionIfElse = nodo->izq;
        ASTNodo *bloquesIf = nodo->der;

        ASTNodo *bloqueIf = bloquesIf->izq;
        ASTNodo *bloqueElse = bloquesIf->der;

        char *etiquetaElse = nuevoLabel();
        char *etiquetaFinIfElse = nuevoLabel();

        Simbolo *expresionCondicionIfElse = generarExpresion(condicionIfElse);

        Instruccion saltoElse = {
            .op = IF_FALSE,
            .arg1 = expresionCondicionIfElse,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaElse)
        };

        emitir(saltoElse);

        construirCodigoIntermedio(bloqueIf);

        Instruccion saltoFinIfElse = {
            .op = GOTO,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaFinIfElse)
        };

        emitir(saltoFinIfElse);

        Instruccion inicioElse = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaElse)
        };

        emitir(inicioElse);

        construirCodigoIntermedio(bloqueElse);

        Instruccion finIfElse = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(etiquetaFinIfElse)
        };

        emitir(finIfElse);

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
            .label = strdup(inicioWhileLabel)
        };
        emitir(inicioWhile);

        Simbolo *expresionCondicionWhile = generarExpresion(condicionWhile);

        Instruccion saltoFinWhile = {
            .op = IF_FALSE,
            .arg1 = expresionCondicionWhile,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(finWhileLabel)
        };
        emitir(saltoFinWhile);

        construirCodigoIntermedio(bloqueWhile);

        Instruccion saltoInicioWhile = {
            .op = GOTO,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(inicioWhileLabel)
        };
        emitir(saltoInicioWhile);

        Instruccion finWhile = {
            .op = LABEL,
            .arg1 = NULL,
            .arg2 = NULL,
            .resultado = NULL,
            .label = strdup(finWhileLabel)
        };
        emitir(finWhile);
        break;

    case NODO_RETORNO:
        
        Simbolo *expresionRetorno = generarExpresion(nodo->izq);

        Instruccion instRetorno = {
            .op = RETURN,
            .arg1 = expresionRetorno,
            .arg2 = NULL,
            .resultado = NULL,
            .label = NULL,
        };

        emitir(instRetorno); 
        break;
        
    case NODO_INVOCACION:
        //pusheamos los argumentos
        ASTNodo *argumentos = nodo->der;
        while (argumentos != NULL){
            Simbolo *expresionActual = generarExpresion(argumentos->izq);

            Instruccion argumentoPush = { 
                .op = PUSH, 
                .arg1 = expresionActual,
                .arg2 = NULL,
                .resultado = NULL, 
                .label = NULL
            };

            emitir(argumentoPush);

            argumentos = argumentos->der; 
        }

        //call al label del metodo 
        Instruccion callMetodo = {
            .op = CALL,
            .arg1 = nodo->simbolo,
            .arg2 = NULL,
            .resultado = NULL,
            .label = NULL
        };

        emitir(callMetodo); 
        
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
    case NODO_INT:
    case NODO_BOOLEAN:
    case NODO_FLOAT:
        return nodo->simbolo;

        break;    
    case NODO_SUMA:
        Simbolo *expresionSumaIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionSumaDerecha = generarExpresion(nodo->der);

        Simbolo *sumTemp = nuevoTemporal(); 
        sumTemp->tipoDato = nodo->simbolo->tipoDato;

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
        restaTemp->tipoDato = nodo->simbolo->tipoDato;

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
        multTemp->tipoDato = nodo->simbolo->tipoDato;

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
        divTemp->tipoDato = nodo->simbolo->tipoDato;

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
        modTemp->tipoDato = nodo->simbolo->tipoDato;

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
        notTemp->tipoDato = nodo->simbolo->tipoDato;

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
        andTemp->tipoDato = nodo->simbolo->tipoDato;

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
        Simbolo *expresionOrIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionOrDerecha = generarExpresion(nodo->der);

        Simbolo *orTemp = nuevoTemporal(); 
        orTemp->tipoDato = nodo->simbolo->tipoDato;

        Instruccion orInst = { 
            .op = OR,
            .arg1 = expresionOrIzquierda,
            .arg2 = expresionOrDerecha,
            .resultado = orTemp,
            .label = NULL,
        };

        emitir(orInst);

        return orTemp;
        break;
    case NODO_IGUALDAD:
        Simbolo *expresionEqIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionEqDerecha = generarExpresion(nodo->der);

        Simbolo *eqTemp = nuevoTempeqal(); 
        eqTemp->tipoDato = nodo->simbolo->tipoDato;

        Instruccion eqInst = { 
            .op = EQ,
            .arg1 = expresionEqIzquierda,
            .arg2 = expresionEqDerecha,
            .resultado = eqTemp,
            .label = NULL,
        };

        emitir(eqInst);

        return eqTemp;
        break;
    case NODO_MENOR:
        Simbolo *expresionLtIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionLtDerecha = generarExpresion(nodo->der);

        Simbolo *ltTemp = nuevoTemporal(); 
        ltTemp->tipoDato = nodo->simbolo->tipoDato;

        Instruccion ltInst = { 
            .op = LT,
            .arg1 = expresionLtIzquierda,
            .arg2 = expresionLtDerecha,
            .resultado = ltTemp,
            .label = NULL,
        };

        emitir(ltInst);

        return ltTemp;
        break;
    case NODO_MAYOR:
        Simbolo *expresionGtIzquierda = generarExpresion(nodo->izq);
        Simbolo *expresionGtDerecha = generarExpresion(nodo->der);

        Simbolo *gtTemp = nuevoTemporal(); 
        gtTemp->tipoDato = nodo->simbolo->tipoDato;

        Instruccion gtInst = { 
            .op = GT,
            .arg1 = expresionGtIzquierda,
            .arg2 = expresionGtDerecha,
            .resultado = gtTemp,
            .label = NULL,
        };

        emitir(gtInst);

        return gtTemp;       
        break;
    default:
        break;
    }
}