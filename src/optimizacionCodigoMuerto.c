#include <stdlib.h>
#include "optimizacionCodigoMuerto.h"

extern TablaSimbolos *tabla;
TablaSimbolos* tablaUsados; 

void limpiarArbol(ASTNodo *raiz){
    inicializarTs(&tablaUsados);

    ASTNodo *izq = raiz->izq;
    ASTNodo *der = raiz->der;

    limpiarSentencias(der);
    limpiarDeclaraciones(&izq);
}

void limpiarSentencias(ASTNodo *nodo){
    if (nodo == NULL) return;

    ASTNodo *izq = nodo->izq;
    ASTNodo *der = nodo->der;

    switch (nodo->tipo)
    {
    //optimizacion codigo muerto post return
    case NODO_SENTENCIAS:
        if (izq->tipo == NODO_RETORNO){
            nodo->der = NULL;
        }
        break;
    //optimizacion contradicciones en condiciones 
    case NODO_IF:
    case NODO_IF_ELSE:
    case NODO_WHILE:
        if (condicionFalsa(izq)){
            nodo = NULL;
            return;
        }
        break;
    //optimizacion var o metoodo no utilizado
    case  NODO_IDENTIFICADOR:
        agregarSimbolo(nodo->simbolo, tablaUsados);
        break;
    default:
        break;
    }

    limpiarSentencias(izq);
    limpiarSentencias(der);
}

void limpiarDeclaraciones(ASTNodo **nodo){
    if (*nodo == NULL) return;

    ASTNodo *declaracion = (*nodo)->izq;
    ASTNodo *declaraciones = (*nodo)->der;

    Simbolo *simboloDeclaracion = declaracion->simbolo;

    if ((*nodo)->tipo == NODO_DECL_MET){
        ASTNodo *bloque = declaracion->der;
        limpiarSentencias(bloque);//analizo el bloque
        limpiarDeclaracionesBloque(bloque);
    }

    if (!existeSimboloEnNivel(simboloDeclaracion->nombre, tablaUsados)){
        *nodo = declaraciones; 
        limpiarDeclaraciones(*nodo);
    }
    else{
        limpiarDeclaraciones(declaraciones);
    }
}

void limpiarDeclaracionesBloque(ASTNodo **nodo){
    if (*nodo == NULL) return;

    if ((*nodo)->tipo = NODO_DECL_VAR){
        Simbolo *simboloVar = (*nodo)->simbolo;

        if (!existeSimboloEnNivel(simboloVar, tablaUsados)){
            (*nodo) = NULL;
            return; 
        }
    }

    limpiarDeclaracionesBloque((*nodo)->izq);
    limpiarDeclaracionesBloque((*nodo)->der);
}