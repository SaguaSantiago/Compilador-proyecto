%code requires {
  #include "enums.h"
}

%{ 
    #include <stdio.h>
    #include "enums.h"
    extern int yylineno;

    int yylex(void);
    void yyerror(const char *s);

%}
%define parse.error detailed

%union {
  ASTNodo nodo;
  float valor; // Los tipo INT seran tratados como FLOAT internamente.
  char* nombre;
}

%token MAIN BOOLEAN VOID RETURN SUMA MULTIPLICACION ASIGNACION INT FLOAT PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA COMA IF ELSE WHILE AND OR NOT MAYOR MENOR IGUALDAD MOD RESTA DIV
%token<valor> INT_LITERAL FLOAT_LITERAL TRUE FALSE // Podriamos poner BOOLEAN_LITERAL pero tendriamos que comparar strings en Flex. 
%token<nombre> Id

//%type<nodo> Program Var_declaraciones Var_declaracion Metodo_declaraciones Metodo_declaracion Tipo_Retorno Tipo_dato Params_decl Bloque Sentencias_list Sentencia Metodo_invocacion Expresiones Expr Op_binario Op_arit Op_cond Op_rel

%start Program
%%

Program: Declaraciones;

Declaraciones: Declaracion Declaraciones
              |
              ; 

Declaracion: Tipo_dato Id_list PUNTO_COMA
           | Tipo_dato Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           | VOID Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           ;

Var_declaraciones: Var_decl Var_declaraciones
                  |
                  ;
                  
Var_decl: Tipo_dato Id_list PUNTO_COMA;

Id_list: Id COMA Id_list
       | Id
       ;

Tipo_dato: INT | FLOAT | BOOLEAN;

Params_decl: Tipo_dato Id COMA Params_decl 
           | Tipo_dato Id
           | %empty
           ;

Bloque: LLAVE_IZQ Var_declaraciones Sentencias_list LLAVE_DER;

Sentencias_list: Sentencia Sentencias_list
               | %empty
               ;

Sentencia: Id ASIGNACION Expr PUNTO_COMA
      | Metodo_invocacion PUNTO_COMA
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque ELSE Bloque
      | WHILE Expr Bloque
      | RETURN Expr PUNTO_COMA
      | RETURN PUNTO_COMA
      ;

Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER;

Expresiones: Expr Expresiones
          | Expr
          ;
Expr: Id
    | Metodo_invocacion
    | Literal
    | Expr Op_binario Expr
    | RESTA Expr
    | NOT Expr
    | PARENTESIS_IZQ Expr PARENTESIS_DER
    ;

Op_binario: Op_arit
          | Op_rel
          | Op_cond
          ;

Op_arit: SUMA | MULTIPLICACION | RESTA | DIV | MOD;

Op_cond: AND | OR;

Op_rel: IGUALDAD | MENOR | MAYOR;

Literal: INT_LITERAL | FLOAT_LITERAL | FALSE | TRUE;
%%

void yyerror(const char *s)
{
    fprintf(stderr,
            "Error sintáctico en la línea %d: %s\n",
            yylineno,
            s);
}
