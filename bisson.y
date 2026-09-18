%code requires {
  #include "enums.h"
}

%{ 
    #include <stdio.h>
    #include "enums.h"
 
    int yylex(void);
    void yyerror(const char *s);

%}
%define parse.error detailed
%locations

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
// TODO: resolver conflicto: si hay un metodo declarado sin variables declaradas lo trata de leer como la declaracion de un variable
// solucion pensada: separar las declaraciones en parte izq y derecha: izq -> tipo id, der-> resto_decl_var | resto_decl_metodo
%%

Program:  Var_declaraciones Metodo_declaraciones;

Var_declaraciones: Var_decl Var_declaraciones
                 | %empty
                 ;

Var_decl: Tipo_dato Id_list PUNTO_COMA;

Id_list: Id COMA Id_list
       | Id
       ;

Metodo_declaraciones: Metodo_declaracion Metodo_declaraciones
                    | %empty
                    ;

Metodo_declaracion: Tipo_Retorno Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque;

Tipo_Retorno: VOID
            | Tipo_dato
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
      | Bloque // TODO: Porque bloque?
      ;

Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER PUNTO_COMA;

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
            "Error sintáctico en línea %d, columna %d: %s\n",
            yylloc.first_line,
            yylloc.first_column,
            s);
}
