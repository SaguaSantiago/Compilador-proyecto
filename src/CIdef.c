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
ListaOffsets *offsets;

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
    fprintf(stderr, "Agrego un global %s y de tipo %d\n", var->nombre, var->tipoDato);
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
    // TODO Crear flag
    //no optimizado
    offsetsCant += 8;
    return offsetsCant;
    //optimizado
    if(offsets == NULL){ 
        offsets = (ListaOffsets*)malloc(sizeof(ListaOffsets));
        offsetsCant += 8;
        offsets->offset = offsetsCant;
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

void mostrarCodigo(FILE* out) {
    FILE* f = out == NULL ? stdout : out;
    for (size_t i = 0; i < codigoCantidad; i++) {
        Instruccion inst = codigoIntermedio[i];

        // fprintf(stderr, "op %d\n", inst.op);
        // fprintf(stderr, "codigo ok \n");

        Simbolo *arg1 = inst.arg1; 
        Simbolo *arg2 = inst.arg2; 

        char *strValor1 = (char*)malloc(64 * sizeof(char)); 
        char *strValor2 = (char*)malloc(64 * sizeof(char));
        
        if (arg1 != NULL){
            if (arg1->tipoSimbolo == SIMBOLO_VAR_LOCAL || arg1->tipoSimbolo == SIMBOLO_VAR_GLOBAL){
                strValor1 = strdup(arg1->nombre);
            }
            else if (arg1->tipoDato == TIPO_INTEGER || arg1->tipoDato == TIPO_BOOLEAN){
                sprintf(strValor1,"%d",arg1->valor);
            } 
            else if(arg1->tipoDato == TIPO_FLOAT){
                sprintf(strValor1,"%.2f",arg1->valor_float);
            } 
        }

        if (arg2 != NULL){
            if (arg2->tipoSimbolo == SIMBOLO_VAR_LOCAL || arg2->tipoSimbolo == SIMBOLO_VAR_GLOBAL){
                strValor2 = strdup(arg2->nombre);
            }
            else if (arg2->tipoDato == TIPO_INTEGER || arg2->tipoDato == TIPO_BOOLEAN){
                sprintf(strValor2,"%d",arg2->valor);
            } 
            else if(arg2->tipoDato == TIPO_FLOAT){
                sprintf(strValor2,"%.2f",arg2->valor_float);
            }
        }
        
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
                    inst.resultado->nombre,  arg1->nombre, strValor2);
                break;
            case GT: 
                fprintf(f,"%s = %s > %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case EQ:
                fprintf(f,"%s = %s == %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case LABEL:
                    
                fprintf(f,"%s:\n", inst.label);
                break;
            case GOTO:
                fprintf(f,"goto %s\n", inst.label);
                break;
            case IF_FALSE:
                fprintf(f,"ifFalse %s goto %s\n", inst.arg1->nombre, inst.label);
                break;
            case RETURN:
                fprintf(f,"return %s\n", strValor1);
                break;
            case FIN_METODO:
                fprintf(f,"ret\n");
                break;
            case PUSH:
                fprintf(f,"push %d\n", arg1->valor);
                break;
            case CALL:
                fprintf(f,"%s = call %s\n", inst.resultado->nombre, inst.arg1->nombre);
                break;
            case VAR_LOCAL:
                fprintf(f,"local %s\n", arg1->nombre);
                break;
            case VAR_GLOBAL:
                fprintf(f,"global %s\n", arg1->nombre);
                break;
            default:
                break;
        }
    }
}