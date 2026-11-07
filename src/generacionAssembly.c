#include <stdio.h>
#include "generacionAssembly.h"
#include "CIdef.h"

extern FILE *yyout; //lex.yy.c

void construirCodigoAssembly(Instruccion* codigoIntermedio){
    int f = fopen(yyout, "w");

    if(f == NULL){
        perror("Error al crear el archivo assembly");
        return;
    }
    
    fputs("section .bss\n\n", f);
    
    while(listaGlobales->sig != NULL){
        switch(listaGlobales->variableGlobal->tipoDato){
            case TIPO_INTEGER:
                fprintf(f, "  %s: resd 1 ", listaGlobales->variableGlobal->nombre);
                break;
            case TIPO_FLOAT: 
                fprintf(f, "  %s: resd 1 ", listaGlobales->variableGlobal->nombre);
            case TIPO_BOOLEAN:
                fprintf(f, "  %s: resb 1 ", listaGlobales->variableGlobal->nombre);
                break;
        }
    }

    fputs("section .text",f);
    
    fclose(f);
}