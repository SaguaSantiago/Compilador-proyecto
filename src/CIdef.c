#include "CIdef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Instruccion* codigoIntermedio;

int contadorTemp = 0;
int contadorLabel = 0;

int codigoCantidad = 0;
int codigoCapacidad = 10;

int offsetsCant;
ListaOffsets *offsets = NULL;

ListaGlobales *listaGlobales;

void agregarGlobal(Simbolo* var){
    if(var->tipoSimbolo != SIMBOLO_VAR_GLOBAL) return;
    if (listaGlobales == NULL) {
        listaGlobales = (ListaGlobales*) malloc(sizeof(ListaGlobales));
        listaGlobales->sig = NULL;
    }
    ListaGlobales *nuevaVar = (ListaGlobales*) malloc(sizeof(ListaGlobales));
    nuevaVar->variableGlobal = var; 
    nuevaVar->sig = listaGlobales->sig;
    listaGlobales->sig = nuevaVar; 
}

Simbolo* nuevoTemporal() {
    char *tempChar = (char*)malloc(10 * sizeof(char));
    sprintf(tempChar, "t%d", contadorTemp++);

    Simbolo *temp = crearSimbolo(); 
    temp->nombre = tempChar; 
    temp->tipoSimbolo = SIMBOLO_TEMPORAL;
    temp->offset = obtenerOffset();
    return temp;
}

int obtenerOffset(){
    // // TODO Crear flag
    // //no optimizado
    // offsetsCant += 8;
    // return offsetsCant;
    // //optimizado
    if(offsets == NULL){ 
        offsets = (ListaOffsets*)malloc(sizeof(ListaOffsets));
        offsetsCant += 8;
        offsets->offset = offsetsCant;
        offsets->sig = NULL;
    };
    int result = offsets->offset;
    offsets = offsets->sig;

    return result;
}

void soltarOffset(int offset){
    ListaOffsets* nuevo = (ListaOffsets*)malloc(sizeof(ListaOffsets));
    nuevo->offset = offset;
    nuevo->sig = offsets;
    offsets = nuevo;
}

void reiniciarOffset(){
    offsets = NULL;
    offsetsCant = 0; 
}

void soltarTemporal(Simbolo* temp){
    if(temp == NULL || temp->tipoSimbolo != SIMBOLO_TEMPORAL) return;
    soltarOffset(temp->offset);
}

char* nuevoLabel() {
    char *label = (char*)malloc(10 * sizeof(char));
    sprintf(label, "L%d", contadorLabel++);
    return label;
}

void emitir(Instruccion instruccion) {
    if (codigoCantidad == codigoCapacidad) {
        size_t nuevaCapacidad = codigoCapacidad * 2;

        Instruccion *nuevoCodigo =
            realloc(codigoIntermedio, nuevaCapacidad * sizeof(Instruccion));

        if (nuevoCodigo == NULL) {
            fprintf(stderr, "Error al reservar memoria para el codigo");
        }

        codigoIntermedio = nuevoCodigo;
        codigoCapacidad = nuevaCapacidad;
    }
    if (codigoIntermedio == NULL) codigoIntermedio = (Instruccion*)malloc(codigoCapacidad * sizeof(Instruccion));

    codigoIntermedio[codigoCantidad] = instruccion;
    codigoCantidad++;
    soltarTemporal(instruccion.arg1);
    soltarTemporal(instruccion.arg2);
}

char* arg_string(Simbolo* arg);

void mostrarCodigo(FILE* out) {
    FILE* f = out == NULL ? stdout : out;
    for (size_t i = 0; i < codigoCantidad; i++) {
        Instruccion inst = codigoIntermedio[i];

        Simbolo *arg1 = inst.arg1; 
        Simbolo *arg2 = inst.arg2; 

        char *strValor1 = arg_string(arg1);

        char *strValor2 = arg_string(arg2);

        switch (inst.op) {
            case ADD:
                fprintf(f,"%s = %s + %s\n",
                       inst.resultado->nombre, strValor1, strValor2);
                break;
            case SUB:
                fprintf(f,"%s = %s - %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;
            case MUL:
                fprintf(f,"%s = %s * %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;
            case DIV:
                fprintf(f,"%s = %s / %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;

            case ASSIGN:
                fprintf(f,"%s = %s\n",
                       inst.resultado->nombre, strValor1);
                break;
            case LT:
                fprintf(f,"%s = %s < %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case GT: 
                fprintf(f,"%s = %s > %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case EQ:
                fprintf(f,"%s = %s == %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case OR:
                fprintf(f, "%s OR %s", strValor1, strValor2);
                break;
            case AND:
                fprintf(f, "%s AND %s", strValor1, strValor2);
                break;
            case NOT:
                fprintf(f, "NOT %s", strValor1, strValor2);
                break;
            case LABEL:
                fprintf(f,"%s:\n", inst.label);
                break;
            case GOTO:
                fprintf(f,"goto %s\n", inst.label);
                break;
            case IF_FALSE:
                fprintf(f,"if_false %s goto %s\n", strValor1, inst.label);
                break;
            case RETURN:
                fprintf(f,"return %s\n", strValor1);
                break;
            case FIN_METODO:
                fprintf(f,"fin_metodo\n");
                break;
            case PUSH:
                fprintf(f,"push %d\n", arg1->valor);
                break;
            case CALL:
                fprintf(f,"%s = call %s\n", inst.resultado->nombre, arg1->nombre);
                break;
            case VAR_LOCAL:
                fprintf(f,"local %s\n", strValor1);
                break;
            case VAR_GLOBAL:
                fprintf(f,"global %s\n", strValor1);
                break;
            case INICIO_METODO:
                fprintf(f, "inicio_metodo %s\n", inst.label);
            break;
            default:
                fprintf(f, "operacion no reconocida %d\n", inst.op);
            break;
        }
    }
}

char* arg_string(Simbolo* arg){
    if(arg == NULL) return NULL;
    char* result = malloc(sizeof(char)*20);
    if (arg != NULL){
        if (arg->tipoSimbolo == SIMBOLO_VAR_LOCAL || arg->tipoSimbolo == SIMBOLO_VAR_GLOBAL){
            result = strdup(arg->nombre);
        } 
        else if (arg->tipoSimbolo == SIMBOLO_INTEGER_LITERAL){
            sprintf(result,"%d",arg->valor);
        }
        else if(arg->tipoSimbolo == SIMBOLO_FLOAT_LITERAL){
            sprintf(result,"%.2f",arg->valor_float);
        }
        else if(arg->tipoSimbolo == SIMBOLO_BOOLEAN_LITERAL){
            sprintf(result,"%s", arg->valor == 1 ? "true" : "false");
        }
        else if (arg->tipoSimbolo == SIMBOLO_TEMPORAL){
            fprintf(stderr, "%s\n", arg->nombre);
            sprintf(result,"%s",arg->nombre);
        }
    }

    return result;
}