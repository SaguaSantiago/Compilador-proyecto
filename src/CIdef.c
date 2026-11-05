#include "CIdef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contadorTemp = 0; 
int contadorLabel = 0; 

static Instruccion *codigo = NULL; 
static int codigoCantidad = 0;
static int codigoCapacidad = 10; 

Simbolo* nuevoTemporal() {
    char *tempChar = (char*)malloc(10 * sizeof(char));
    sprintf(tempChar, "t%d", contadorTemp++);

    Simbolo *temp = crearSimbolo(); 
    temp->nombre = tempChar; 
    temp->tipoSimbolo = SIMBOLO_TEMPORAL;

    return temp;
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
            realloc(codigo, nuevaCapacidad * sizeof(Instruccion));

        if (nuevoCodigo == NULL) {
            fprintf(stderr, "Error al reservar memoria para el codigo");
        }

        codigo = nuevoCodigo;
        codigoCapacidad = nuevaCapacidad;
    }
    if (codigo == NULL) codigo = (Instruccion*)malloc(codigoCapacidad * sizeof(Instruccion));

    codigo[codigoCantidad] = instruccion;
    codigoCantidad++;
}

void mostrarCodigo(void) {
    for (size_t i = 0; i < codigoCantidad; i++) {
        Instruccion inst = codigo[i];

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
                printf("%s = %s + %s\n",
                       inst.resultado->nombre, strValor1, strValor2);
                break;
            case SUB:
                printf("%s = %s - %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;
            case MUL:
                printf("%s = %s * %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;
            case DIV:
                printf("%s = %s / %s\n",
                       inst.resultado->nombre,  strValor1, strValor2);
                break;

            case ASSIGN:
                printf("%s = %s\n",
                       inst.resultado->nombre, strValor1);
                break;
            case LT:
                printf("%s = %s < %s\n",
                    inst.resultado->nombre,  arg1->nombre, strValor2);
                break;
            case GT: 
                printf("%s = %s > %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case EQ:
                printf("%s = %s == %s\n",
                    inst.resultado->nombre,  strValor1, strValor2);
                break;
            case LABEL:
                    
                printf("%s:\n", inst.label);
                break;
            case GOTO:
                printf("goto %s\n", inst.label);
                break;
            case IF_FALSE:
                printf("ifFalse %s goto %s\n", inst.arg1->nombre, inst.label);
                break;
            case RETURN:
                printf("return %s\n", strValor1);
                break;
            case FIN_METODO:
                printf("ret\n");
                break;
            case PUSH:
                printf("push %s\n", inst.arg1);
                break;
            case CALL:
                printf("%s = call %s\n", inst.resultado->nombre, inst.arg1->nombre);
                break;
            default:
                break;
        }
    }
}