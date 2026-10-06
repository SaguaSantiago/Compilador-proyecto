#include "ASTdef.h"
#include "TSdef.h"

extern ASTNodo* raiz;

TablaSimbolos* tabla;
TipoDato retornoEsperado;
NodoSimbolo* listaExpresiones;

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
            // lanzamos el error
        }
        Simbolo* simbolo_var =  nodo->simbolo;

        agregarSimbolo(simbolo_var, tabla);

        analisisSemantico(nodo->izq);
        break;
    
    case NODO_DECL_MET:
        if(existeSimboloEnNivel(nodo->simbolo->nombre, tabla)){
            //lanzar errorovich
        }

        Simbolo* simbolo_met =  nodo->simbolo;

        agregarNivel(tabla);
        retornoEsperado = nodo->simbolo->tipoDato; 
        
        agregarSimbolo(simbolo_met, tabla);

        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        break;
    
    case NODO_ASIGNACION:
        encontrado = buscarSimbolo(nodo->izq->simbolo->nombre, tabla);
        if (encontrado == NULL){
            //lanzar error no encontrado
        }

        Simbolo* simboloExpresion = nodo->der->simbolo;

        if (encontrado->tipoDato != simboloExpresion->tipoDato){
            //lanzar error simbolos incompatibles 
        }
        
        analisisSemantico(nodo->der); 
        break;
    
    case NODO_IF:
    case NODO_IF_ELSE:
    case NODO_WHILE:
        if(nodo->izq->simbolo->tipoDato != TIPO_BOOLEAN){
            // lanzar error
        }
        agregarNivel(tabla);
        retornoEsperado = TIPO_VOID;
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);
        break;

    case NODO_BLOQUE:
        analisisSemantico(nodo->izq);
        analisisSemantico(nodo->der);

        sacarNivel(tabla);
        break;
    
    case NODO_RETORNO:
        if(nodo->simbolo->tipoDato != retornoEsperado){
            // lanzar error de retorno inesperado
        }
        retornoEsperado = TIPO_VOID;
        break;
        
    case NODO_INVOCACION:
        if(nodo->simbolo == NULL){
            // lanzar error de identificador undefined
        } 

        if(nodo->simbolo->tipoSimbolo != SIMBOLO_MET_DECL){
            // lanzar error de "no es una funcion"
        }

        analisisSemantico(nodo->izq);//TODO actualizar listaExpresiones en cada expresion recorrida
        
        NodoSimbolo* expresiones = listaExpresiones;
        free(listaExpresiones);
        listaExpresiones = NULL;

        NodoSimbolo* nodoSimboloActual = expresiones;
        Simbolo* parametroActual = nodo->simbolo->parametros;

        while (nodoSimboloActual != NULL) {
            if(nodoSimboloActual->simbolo->tipoDato != parametroActual->tipoDato){
                //lanzar error parametro incorrecto
            }

            nodoSimboloActual = nodoSimboloActual->sig;
            parametroActual = parametroActual->sig;

            if((nodoSimboloActual == NULL && parametroActual != NULL) 
            || nodoSimboloActual != NULL && parametroActual == NULL){
                //lanzar error cantidad de parametros incompatible  
            }
        }

        break;
    
    case NODO_IDENTIFICADOR:
        encontrado = buscarSimbolo(nodo->simbolo->nombre, tabla);
        
        if(encontrado == NULL){
            // lanzar error de identificador undefined
        }
        break;
    case NODO_RESTA:
        if(nodo->der == NULL){
            // operador unario de la resta
            if(nodo->izq->simbolo->tipoDato == TIPO_FLOAT) nodo->simbolo->valor_float = -nodo->simbolo->valor_float; 
            else if (nodo->izq->simbolo->tipoDato == TIPO_INTEGER) nodo->simbolo->valor = -nodo->simbolo->valor; 
            else {
                // lanzar error de tipo no numerico
            }
        } else {
            // operador binario
            
        }
        break;
    default:
    break;
}
}