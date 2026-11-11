#include <stdio.h>
#include <stdlib.h>
#include "generacionAssembly.h"
#include "CIdef.h"

extern FILE *yyout; //lex.yy.c
extern ListaGlobales* listaGlobales;
int calcularEspacio(Instruccion *codigoIntermedio, int cant, int inicial);
void movArg(Simbolo* arg, char* dest_arg);

void construirCodigoAssembly(Instruccion* codigoIntermedio, int codigoCantidad){
    FILE* f = stdout;

    if(f == NULL){
        perror("Error al crear el archivo assembly");
        return;
    }
    
    fputs("section .bss\n\n", f);

    listaGlobales = listaGlobales->sig;
    //cosntruimos la seccion de variables globales
    while(listaGlobales != NULL){
        switch(listaGlobales->variableGlobal->tipoDato){
            case TIPO_INTEGER:
                fprintf(f, "  %s: resd 1 \n", listaGlobales->variableGlobal->nombre);
                break;
            case TIPO_FLOAT: 
                fprintf(f, "  %s: resd 1 \n", listaGlobales->variableGlobal->nombre);
            case TIPO_BOOLEAN:
                fprintf(f, "  %s: resb 1 \n", listaGlobales->variableGlobal->nombre);
                break;
            default: 
                fprintf(stderr, "error: tipo de dato no procesado\n");

        }
        listaGlobales = listaGlobales->sig; 
    }

    fputs("\nsection .data\n\n", f); 

    fputs("section .text\n\n", f);

    for (int indiceActual = 0; indiceActual<codigoCantidad; indiceActual++){
        Instruccion instruccionActual = codigoIntermedio[indiceActual]; 

        Simbolo* arg1 = instruccionActual.arg1;
        Simbolo* arg2 = instruccionActual.arg2;
        
        switch(instruccionActual.op){
            case INICIO_METODO:
                int espaciosLocales = calcularEspacio(codigoIntermedio, codigoCantidad, indiceActual);
                if(espaciosLocales == -1) return;
                fprintf(f, "%s:\n", instruccionActual.label);
                fprintf(f, "enter $(8 * %d), $0\n", espaciosLocales);
                break;    
            case FIN_METODO: 
                fputs("ret \n", f);
                break;
            case ADD:
            case SUB:
            case MUL:
                //ARG1
                movArg(arg1, "%r10");
                //ARG2
                movArg(arg2, "%r11");

                if(instruccionActual.op == ADD) fprintf(f,"add %%r10, %%r11\n");
                else if(instruccionActual.op == SUB) fprintf(f,"sub %%r10, %%r11\n");
                else if(instruccionActual.op == MUL) fprintf(f,"imul %%r10, %%r11\n");
                fprintf(f,"mov %%r11, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case MOD:
            case DIV:
                //ARG1
                movArg(arg1, "%rdx");

                //ARG2
                movArg(arg2, "%r10");

                fprintf(f,"idiv %%r10\n");
                
                if(instruccionActual.op == DIV) fprintf(f,"mov %%rax, -%d(%%rbp)\n", instruccionActual.resultado->offset);
                else fprintf(f,"mov %%rdx, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case ASSIGN:
                // primero determinamos el destino de la asignacion
                char* id;
                if(instruccionActual.resultado->tipoSimbolo == SIMBOLO_VAR_LOCAL){
                    id = malloc(sizeof(char)*30);
                    sprintf(id, "-%d(%%rbp)", instruccionActual.resultado->offset);
                } else {
                    id = malloc(sizeof(char)*30);
                    sprintf(id, "[%s]", instruccionActual.resultado->nombre);
                }

                // dependiendo la expresion a asignar determinamos el tratamiento
                if(arg1->tipoSimbolo == SIMBOLO_INTEGER_LITERAL){
                    fprintf(f,"mov $%d, %s\n", arg1->valor, id);
                }
                else if(arg1->tipoSimbolo == SIMBOLO_FLOAT_LITERAL){
                    // TODO consultar como se hace
                }
                else if (arg1->tipoSimbolo == SIMBOLO_TEMPORAL || arg1->tipoSimbolo == SIMBOLO_VAR_LOCAL){
                    fprintf(f,"mov -%d(%%rbp), %%r11\n", arg1->offset);
                    fprintf(f,"mov %%r11, %s\n", id);
                }
                else if(arg1->tipoSimbolo == SIMBOLO_VAR_GLOBAL){
                    fprintf(f,"mov [%s], %%r11\n", arg1->nombre);
                    fprintf(f,"mov %%r11, %s\n", id);
                }

                
            break;
            // case PUSH:
            // break;
            case CALL:
                fprintf(f, "call %s\n", arg1->nombre);
                fprintf(f, "mov %%eax, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case LT:
            case GT:
            case EQ:
                movArg(arg1, "%r10");
                
                movArg(arg2, "%r11");

                fprintf(f, "cmp %%r10, %%r11\n");
                fprintf(f, "mov $0, %%r11");
                fprintf(f, "mov $1, %%r10");

                if(instruccionActual.op == LT) fprintf(f,"cmovl %%r10, %%r11");
                else if(instruccionActual.op == GT) fprintf(f,"cmovg %%r10, %%r11");
                else fprintf(f,"cmove %%r10, %%r11");

                fprintf(f, "mov %%r11, -%d(%%rbp)", instruccionActual.resultado->offset);
            break;
            // case NOT:
            // break;
            // case AND:
            // break;
            // case OR:
            // break;
            case LABEL:
                fprintf(f, "%s:\n", instruccionActual.label);
            break;
            case GOTO:
                fprintf(f, "jmp %s\n", instruccionActual.label);
            break;
            // case IF_FALSE:
            // break;
            // case RETURN:
            // break;
            default:
                fprintf(f,"instruccion no procesada: %d\n", instruccionActual.op);
        }
    }
    
    fclose(f);
}

void movArg(Simbolo* arg, char* dest_arg){
    FILE* f = stdout;
    //ARG
    if(arg == NULL) return;
    
    if(arg->tipoSimbolo == SIMBOLO_INTEGER_LITERAL){
        fprintf(f, "mov $%d, %s\n", arg->valor, dest_arg);
    }
    else if(arg->tipoSimbolo == SIMBOLO_FLOAT_LITERAL){
        // TODO consultar como se hace
    }
    else if (arg->tipoSimbolo == SIMBOLO_TEMPORAL || arg->tipoSimbolo == SIMBOLO_VAR_LOCAL){
        fprintf(f, "mov -%d(%%rbp), %s\n", arg->offset, dest_arg);
    }
    else if(arg->tipoSimbolo == SIMBOLO_VAR_GLOBAL){
        fprintf(f,"mov [%s], %s\n", arg->nombre, dest_arg);
    }
}

int calcularEspacio(Instruccion *codigoIntermedio, int cant, int inicial){
    int espacioReservado = 0;
    bool finMetodo = false; 
    for (int i=inicial; i<cant ; i++){ 
        Instruccion instActual = codigoIntermedio[i]; 

        if (instActual.op == VAR_LOCAL || (instActual.resultado != NULL && instActual.resultado->tipoSimbolo == SIMBOLO_TEMPORAL)){
            espacioReservado++;
        }
        else if(instActual.op == FIN_METODO){
            finMetodo = true;
            break;
        }
    }

    if (!finMetodo){
        fprintf(stderr, "error al construir assembly: No se encontro el fin de metodo");
        return -1;
    }

    return espacioReservado; 
}