#include <stdlib.h>
#include "TSdef.h"

void agregarSimbolo(Simbolo *nuevoSimbolo, TablaSimbolo *ts){
    int nivelActual = ts->nivelActual;
    NodoNivel* nodoActual = ts->niveles[nivelActual].sig;

    while(nodoActual != NULL){
        if (nodoActual->sim != NULL && 
            nodoActual->sim->tipoSimbolo == SIMBOLO_IDENTIFICADOR &&
            nuevoSimbolo->tipoSimbolo == SIMBOLO_IDENTIFICADOR &&
            strcmp(nodoActual->sim->nombre, nuevoSimbolo->nombre) == 0){
                return 0;
        }

        nodoActual = nodoActual->sig; 
    }

    NodoNivel* nuevoNodo = malloc(sizeof(NodoNivel));
    nuevoNodo->sim = nuevoSimbolo; 
    nuevoNodo->sig = ts->niveles[nivelActual].sig;
    ts->niveles[nivelActual].sig = nuevoNodo; 

    return 1;
}

void inicializarTs(TablaSimbolo *ts){
    ts = (TablaSimbolo*) malloc(sizeof(TablaSimbolo));

    ts->niveles = (NodoNivel*) malloc(sizeof(NodoNivel) * DEFAULT_NIVELES_CANT);
    for(int i = 0; i < DEFAULT_NIVELES_CANT; i++){
        ts->niveles[i].sim = NULL;
        ts->niveles[i].sig = NULL;
    }

    ts->nivelActual = 0; 

    return ts;
}

void agregarNivel(TablaSimbolo *ts){
    ts->nivelActual++;

    NodoNivel* nuevoNodo = malloc(sizeof(NodoNivel)); 
    nuevoNodo->sim = NULL;
    nuevoNodo->sig = NULL;

    NodoNivel *nivelActual = ts->niveles[ts->nivelActual].sig;

    nivelActual->sig = nuevoNodo;   
}

void sacarNivel(TablaSimbolo *ts){
    ts->nivelActual--; 
}

Simbolo* buscarSimbolo(char* nombre, TipoSimbolo tipoSimbolo, TablaSimbolo *tabla){
    int nivel = tabla->nivelActual;
    NodoNivel* nodoActual = tabla->niveles[nivel].sig;

    while (nodoActual != NULL) {
        if (nodoActual->sim != NULL &&
            nodoActual->sim->nombre != NULL &&
            strcmp(nodoActual->sim->nombre, nombre) == 0) {
            return nodoActual->sim;
        }

        nodoActual = nodoActual->sig;
    }

    free(nodoActual);
    return NULL;
}