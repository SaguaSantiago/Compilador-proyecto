%code requires {
  #include "enums.h"
}

%{ 
    #include <stdio.h>
    #include "enums.h"
    #include "ASTdef.h"
    extern int yylineno;

    int yylex(void);
    void yyerror(const char *s);
    Nodo *raiz;
%}
%define parse.error detailed

%union {
  ASTNodo nodo;
  int valor_int;
  float valor_float;
  char* nombre;
  Nodo_Id lista_nombres;
}

%token MAIN BOOLEAN VOID RETURN SUMA MULTIPLICACION ASIGNACION INT FLOAT PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA COMA IF ELSE WHILE AND OR NOT MAYOR MENOR IGUALDAD MOD RESTA DIV
%token<valor_float> FLOAT_LITERAl
%token<valor_int> INT_LITERAL TRUE FALSE // Podriamos poner BOOLEAN_LITERAL pero tendriamos que comparar strings en Flex. 
%token<nombre> Id

%type<nodo> Program Declaraciones Declaracion 
%type<lista_nombres> Id_list
%start Program
%%

Program: Declaraciones
       {
        root = crearNodo(NODO_ROOT, NULL, $1, NULL);
       }
       ;

Declaraciones: Declaracion Declaraciones 
              {
                $$ = crearNodo(NODO_DECLS, NULL, $1, $2);
              }
              |
              ; 

Declaracion: Tipo_dato Id_list PUNTO_COMA 
           {
           // TODO: guardar tipo de datos en el simbolos
            Nodo_id* nombres = $2;
            ASTNodo* decl_raiz = crearNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            ASTNodo* aux = decl_raiz;

            while(nombres.sig != NULL){
              char* id = nombres.id;
              // TODO: guardar id en el simbolo
              ASTNodo* nuevoNodo = crearNodo(NODO_DECL_VAR, NULL, NULL, NULL);
              aux->izq = nuevoNodo;
              aux = nuevoNodo;
              nombres = nombres.sig;
              free(nuevoNodo);
            }
            free(aux);
            $$ = decl_raiz;
           }
           | Tipo_dato Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            $$ = crearNodo(NODO_DECL_MET, NULL, $4, NULL);
           }
           | VOID Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            $$ = crearNodo(NODO_DECL_MET, NULL, $4, NULL);
           }
           ;

Id_list: Id COMA Id_list // TODO: sacar creacion del nodo a otro file en una funcion
       {
         Nodo_id* nodo_nombre = (Nodo_id*) malloc(sizeof(Nodo_id));
         nodo_nombre->id = strcpy($1.nombre);
         nodo_nombre->sig = $3;
         $$ = nodo_nombre;
       }
       | Id
        {
          Nodo_id* nodo_nombre = (Nodo_id*) malloc(sizeof(Nodo_id));
          nodo_nombre->id = strcpy($1.nombre);
          nodo_nombre->sig = NULL;
          $$ = nodo_nombre;
        }
       ;

Tipo_dato: INT 
          {
            $$ = TIPO_INTEGER;
          }
          | FLOAT 
          {
            $$ = TIPO_FLOAT;
          }
          | BOOLEAN
          {
            $$ = TIPO_BOOLEAN;
          }
          ;

Params_decl: Tipo_dato Id COMA Params_decl 
           {
            ASTNodo nodo = crearNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            
            $$ = crearNodo(NODO_PARAM_DECL, NULL, nodo, $4);
           }
           | Tipo_dato Id
           {
            ASTNodo nodo = crearNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            $$ = crearNodo(NODO_PARAM_DECL, NULL, nodo, NULL);
           }
           | %empty
           {
            $$ = NULL;
           }
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
