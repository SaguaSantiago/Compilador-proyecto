#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TSdef.h"

int agregarSimbolo(Simbolo *nuevoSimbolo, TablaSimbolos *ts){
    int nivelActual = ts->nivelActual;
    // fprintf(stderr, "Llegue a agregar simbolo\n");
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

void inicializarTs(TablaSimbolos **ts){
    *ts = (TablaSimbolos*) malloc(sizeof(TablaSimbolos));

    (*ts)->niveles = (NodoNivel*) malloc(sizeof(NodoNivel) * DEFAULT_NIVELES_CANT);
    for(int i = 0; i < DEFAULT_NIVELES_CANT; i++){
        (*ts)->niveles[i].sim = NULL;
        (*ts)->niveles[i].sig = NULL;
    }

    (*ts)->nivelActual = 0;
}

void agregarNivel(TablaSimbolos *ts){
    ts->nivelActual++;

    NodoNivel* nuevoNodo = malloc(sizeof(NodoNivel)); 
    nuevoNodo->sim = NULL;
    nuevoNodo->sig = NULL;

    NodoNivel *nivelActual = ts->niveles[ts->nivelActual].sig;

    nivelActual->sig = nuevoNodo;   
}

void sacarNivel(TablaSimbolos *ts){
    ts->nivelActual--; 
}

Simbolo* buscarSimbolo(char* nombre, TipoSimbolo tipoSimbolo, TablaSimbolos *tabla){
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

    return NULL;
}

void agregarSimboloALista(Simbolo *simbolo, NodoSimbolo **lista) {
  NodoSimbolo *nuevoNodo = (NodoSimbolo *)malloc(sizeof(NodoSimbolo));
  nuevoNodo->simbolo = simbolo;
  nuevoNodo->sig = *lista;

  *lista = nuevoNodo;
}

Simbolo *crearSimbolo(void) {
  Simbolo *nuevoSimbolo = (Simbolo *)malloc(sizeof(Simbolo));
  nuevoSimbolo->nombre = NULL;
  nuevoSimbolo->parametros = NULL;
  nuevoSimbolo->nodoBloque = NULL;
  nuevoSimbolo->tipoDato = 0;
  nuevoSimbolo->tipoSimbolo = 0;
  nuevoSimbolo->valor = 0;

  return nuevoSimbolo;
}
