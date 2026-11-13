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


int condicionFalsa(ASTNodo *nodo){
    if (nodo == NULL) return 0; 

    //si las hojas de la condicion son literales entonces el valor tiene que estar cargado en el simbolo del nodo padre
    if (hojasLiterales(nodo)) return 1 - (nodo->simbolo->valor);
    //si no lo son entonces no se puede resolver la condicion en este punto
    else return 0;    
}

int hojasLiterales(ASTNodo *nodo){
    if (nodo == NULL) return 0;

    //si el nodo es una hoja devolvemos true si es literal
    if (esHoja(nodo)){
        return esLiteral(nodo);
    }
    //si el nodo no es una hoja buscamos las hojas 
    else{
        int *hojaIzq = (esHoja(nodo->izq)) ? esLiteral(nodo->izq) : hojasLiterales(nodo->izq);
        int *hojaDer = (esHoja(nodo->der)) ? esLiteral(nodo->der) : hojasLiterales(nodo->der);

        return hojaIzq && hojaDer;
    }
}

int esHoja(ASTNodo *nodo){
    return nodo->izq == NULL && nodo->der == NULL;
}

int esLiteral(ASTNodo *nodo){
    switch (nodo->tipo)
    {
    case NODO_FLOAT:
    case NODO_INT:
    case NODO_BOOLEAN:
        return 1;
    default:
        return 0;
    }
}