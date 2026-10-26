#include "CIdef.h"
#include <stdio.h>

int contadorTemp = 0; 
int contadorLabel = 0; 

static Instruccion *codigo = NULL; 
static int codigoCantidad = 0;
static int codigoCapacidad = 10; 

char* nuevoTemporal() {
    char *temp = (char*)malloc(10 * sizeof(char));
    sprintf(temp, "t%d", contadorTemp++);
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

    codigo[codigoCantidad] = instruccion;
    codigoCantidad++;
}

void mostrarCodigo(void) {
    for (size_t i = 0; i < codigoCantidad; i++) {
        Instruccion inst = codigo[i];

        switch (inst.op) {
            case ADD:
                printf("%s = %s + %s\n",
                       inst.resultado, inst.arg1, inst.arg2);
                break;
            case SUB:
                printf("%s = %s - %s\n",
                       inst.resultado, inst.arg1, inst.arg2);
                break;
            case MUL:
                printf("%s = %s * %s\n",
                       inst.resultado, inst.arg1, inst.arg2);
                break;
            case DIV:
                printf("%s = %s / %s\n",
                       inst.resultado, inst.arg1, inst.arg2);
                break;

            case ASSIGN:
                printf("%s = %s\n",
                       inst.resultado, inst.arg1);
                break;
            case LT:
                printf("%s = %s < %s\n",
                    inst.resultado, inst.arg1, inst.arg2);
                break;
            case GT: 
                printf("%s = %s > %s\n",
                    inst.resultado, inst.arg1, inst.arg2);
                break;
            case EQ:
                printf("%s = %s == %s\n",
                    inst.resultado, inst.arg1, inst.arg2);
                break;
            case LABEL:
                printf("%s:\n", inst.label);
                break;
            case GOTO:
                printf("goto %s\n", inst.label);
                break;
            case IF_FALSE:
                printf("ifFalse %s goto %s\n", inst.arg1, inst.label);
                break;
            case RETURN:
                printf("return %s\n", inst.arg1);
                break;
            default:
                break;
        }
    }
}