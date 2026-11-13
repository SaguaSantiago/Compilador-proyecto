#include <stdio.h>
#include <stdlib.h>
#include "generacionAssembly.h"
#include "CIdef.h"

extern FILE *yyout; //lex.yy.c
extern ListaGlobales* listaGlobales;
int calcularEspacio(Instruccion *codigoIntermedio, int cant, int inicial);
void movArg(FILE* f, Simbolo* arg, char* dest_arg);

int contadorParametros = 6; 
int parametrosSobrantes = 0;

void construirCodigoAssembly(FILE* out, Instruccion* codigoIntermedio, int codigoCantidad){
    FILE* f = out;

    if(f == NULL){
        perror("Error al crear el archivo assembly");
        return;
    }
    
    fputs(".section .bss\n\n", f);

    listaGlobales = listaGlobales->sig;
    //cosntruimos la seccion de variables globales
    while(listaGlobales != NULL){
        // switch(listaGlobales->variableGlobal->tipoDato){
        //     case TIPO_INTEGER:
        //         fprintf(f, "  %s: resd 1 \n", listaGlobales->variableGlobal->nombre);
        //         break;
        //     case TIPO_FLOAT: 
        //         fprintf(f, "  %s: resd 1 \n", listaGlobales->variableGlobal->nombre);
        //         break;
        //     case TIPO_BOOLEAN:
        //         fprintf(f, "  %s: resb 1 \n", listaGlobales->variableGlobal->nombre);
        //         break;
        //     default: 
        //         fprintf(stderr, "error: tipo de dato no procesado\n");
        fprintf(f, "%s: .zero 8\n", listaGlobales->variableGlobal->nombre);
        listaGlobales = listaGlobales->sig; 
    }

    fputs("\n.section .data\n\n", f); 

    fputs(".text\n\n", f);

    for (int indiceActual = 0; indiceActual<codigoCantidad; indiceActual++){
        Instruccion instruccionActual = codigoIntermedio[indiceActual]; 

        Simbolo* arg1 = instruccionActual.arg1;
        Simbolo* arg2 = instruccionActual.arg2;
        
        switch(instruccionActual.op){
            case INICIO_METODO:
                int espaciosLocales = calcularEspacio(codigoIntermedio, codigoCantidad, indiceActual);
                // int espaciosLocales = calcularEspacioOptimizado(codigoIntermedio, codigoCantidad, indiceActual);
                if(espaciosLocales == -1) return;
                fprintf(f, ".globl %s:\n%s\n", instruccionActual.label, instruccionActual.label);
                fprintf(f, "enter $(8 * %d), $0\n", espaciosLocales);
                break;    
            case FIN_METODO: 
                fprintf(f,"leave \n");
                fprintf(f,"ret \n");
                break;
            case ADD:
            case SUB:
            case MUL:
                //ARG1
                movArg(f, arg1, "%r10");
                //ARG2
                movArg(f, arg2, "%r11");

                if(instruccionActual.op == ADD) fprintf(f,"add %%r10, %%r11\n");
                else if(instruccionActual.op == SUB) fprintf(f,"sub %%r10, %%r11\n");
                else if(instruccionActual.op == MUL) fprintf(f,"imul %%r10, %%r11\n");
                fprintf(f,"mov %%r11, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case MOD:
            case DIV:
                movArg(f, arg1, "%rax");
                movArg(f, arg2, "%r10");

                fprintf(f, "cqo\n");
                fprintf(f, "idiv %%r10\n");

                if (instruccionActual.op == DIV)
                    fprintf(f, "mov %%rax, -%d(%%rbp)\n", instruccionActual.resultado->offset);
                else
                    fprintf(f, "mov %%rdx, -%d(%%rbp)\n", instruccionActual.resultado->offset);
                break;
            case ASSIGN:
                // primero determinamos el destino de la asignacion
                char* id;
                if(instruccionActual.resultado->tipoSimbolo == SIMBOLO_VAR_LOCAL){
                    id = malloc(sizeof(char)*30);
                    sprintf(id, "-%d(%%rbp)", instruccionActual.resultado->offset);
                } else {
                    id = malloc(sizeof(char)*30);
                    sprintf(id, "%s(%%rip)", instruccionActual.resultado->nombre);
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
                    fprintf(f,"mov %s(%%rip), %%r11\n", arg1->nombre);
                    fprintf(f,"mov %%r11, %s\n", id);
                }

                
            break;
            case PUSH:
                movArg(f, arg1, "%r10");

                switch (contadorParametros)
                {
                case 6:
                    fprintf(f,"mov %%r10, %%rdi");
                break;
                case 5:
                    fprintf(f,"mov %%r10, %%rsi");
                break;
                case 4:
                    fprintf(f,"mov %%r10, %%rdx");
                break;
                case 3:
                    fprintf(f,"mov %%r10, %%rcx");
                break;
                case 2:
                    fprintf(f,"mov %%r10, %%r8");
                break;
                case 1:
                    fprintf(f,"mov %%r10, %%r9");
                break;
                default:
                    fprintf(f,"push %%r10");
                    parametrosSobrantes++;
                    break;
                }

                contadorParametros--; 
            break;
            case CALL: 
                fprintf(f, "call %s\n", arg1->nombre);
                fprintf(f, "mov %%eax, -%d(%%rbp)\n", instruccionActual.resultado->offset);

                for(int i = 0 ; i < parametrosSobrantes ; i++){
                    fprintf(f, "pop %%r10\n");
                }

                contadorParametros = 6;
                parametrosSobrantes = 0; 
            break;
            case LT:
            case GT:
            case EQ:
                movArg(f, arg1, "%r10");
                
                movArg(f, arg2, "%r11");

                fprintf(f, "cmp %%r10, %%r11\n");
                fprintf(f, "mov $0, %%r11\n");
                fprintf(f, "mov $1, %%r10\n");

                if(instruccionActual.op == LT) fprintf(f,"cmovl %%r10, %%r11\n");
                else if(instruccionActual.op == GT) fprintf(f,"cmovg %%r10, %%r11\n");
                else fprintf(f,"cmove %%r10, %%r11\n");

                fprintf(f, "mov %%r11, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case NOT:
                movArg(f, arg1, "%r11");
                fprintf(f , "mov $1, %%r10\n"); 

                fprintf(f, "sub %%r10, %%r11\n");
                fprintf(f, "mov %%r11, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case AND:
                movArg(f, arg1, "%r10");
                movArg(f, arg2, "%r11");

                fprintf(f, "add %%r10, %%r11\n");
                fprintf(f, "mov $2, %%r10\n");
                fprintf(f, "cmp %%r11, %%r10\n");
                fprintf(f, "mov $1, %%r10\n");
                fprintf(f, "mov $0, %%r11\n");

                fprintf(f, "cmove %%r10, %%r11\n"); 

                fprintf(f, "mov %%r11, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            break;
            case OR:
                movArg(f, arg1, "%r10");
                
                movArg(f, arg2, "%r11");
                
                fprintf(f, "add %%r10, %%r11\n");
                fprintf(f, "mov $2, %%r10\n");
                fprintf(f, "cmp %%r11, %%r10\n");
                fprintf(f, "mov $0, %%r10\n");
                fprintf(f, "cmp $1, %%r11\n");
                fprintf(f, "cmovne %%r11, %%r10\n");
                fprintf(f, "cmp %%r10, -%d(%%rbp)\n", instruccionActual.resultado->offset);
            
            break;
            case LABEL:
                fprintf(f, "%s:\n", instruccionActual.label);
            break;
            case GOTO:
                fprintf(f, "jmp %s\n", instruccionActual.label);
            break;
            
            case IF_FALSE:
                movArg(f, arg1, "%r11");
                fprintf(f, "mov $0, %%r10\n");
                fprintf(f, "cmp %%r11, %%r10\n");
                fprintf(f,"je %s\n",instruccionActual.label);
            break;
            case RETURN:
                movArg(f, arg1, "%r10");
                fprintf(f, "mov %%r10, %%rax\n");
            break;
            case VAR_GLOBAL:
            case VAR_LOCAL:
            break;
            default:
                fprintf(f,"instruccion no procesada: %d\n", instruccionActual.op);
        }
        fprintf(f, "\n");
    }
    
}

void movArg(FILE* f, Simbolo* arg, char* dest_arg){
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
        fprintf(f,"mov %s(%%rip), %s\n", arg->nombre, dest_arg);
    }
}

int calcularEspacio(Instruccion *codigoIntermedio, int cant, int inicial){
    int espacioReservado = 0;
    int finMetodo = 0; 

    for (int i=inicial; i<cant ; i++){ 
        Instruccion instActual = codigoIntermedio[i]; 

        if (instActual.op == VAR_LOCAL || (instActual.resultado != NULL && instActual.resultado->tipoSimbolo == SIMBOLO_TEMPORAL)){
            espacioReservado++;
        }
        else if(instActual.op == FIN_METODO){
            finMetodo = 1;
            break;
        }
    }

    if (!finMetodo){
        fprintf(stderr, "error al construir assembly: No se encontro el fin de metodo");
        return -1;
    }

    return espacioReservado; 
}

int calcularEspacioOptimizado(Instruccion *codigoIntermedio, int cant, int inicial){
    int espacioReservado = 0;
    int finMetodo = 0; 

    int maxOffset = 0; 

    for (int i=inicial; i<cant ; i++){ 
        Instruccion instActual = codigoIntermedio[i]; 

        if (instActual.op == VAR_LOCAL || (instActual.resultado != NULL && instActual.resultado->tipoSimbolo == SIMBOLO_TEMPORAL)){
            int offsetActual = (instActual.op == VAR_LOCAL) ? instActual.arg1->offset : instActual.resultado->offset;
            
            if (maxOffset < offsetActual){
                maxOffset = offsetActual;
                espacioReservado = maxOffset / 8;
                // fprintf(stderr, "se guardo %d espacios, debido al offset %d\n", espacioReservado, offsetActual);
            }
        }
        else if(instActual.op == FIN_METODO){
            finMetodo = 1;
            break;
        }
    }

    if (!finMetodo){
        fprintf(stderr, "error al construir assembly: No se encontro el fin de metodo");
        return -1;
    }
    // fprintf(stderr, "retorna espacio: %d\n", espacioReservado);
    return espacioReservado; 
}