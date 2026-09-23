%code requires {
  #include "enums.h"
}

%{ 
    #include <stdio.h>
    #include <stdlib.h>
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
  NodoId lista_nombres;
}

%token MAIN BOOLEAN VOID RETURN SUMA MULTIPLICACION ASIGNACION INT FLOAT PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA COMA IF ELSE WHILE AND OR NOT MAYOR MENOR IGUALDAD MOD RESTA DIV
%token<valor_float> FLOAT_LITERAl
%token<valor_int> INT_LITERAL TRUE FALSE // Podriamos poner BOOLEAN_LITERAL pero tendriamos que comparar strings en Flex. 
%token<nombre> Id

%type<nodo> Program Declaraciones Declaracion Bloque Sentencias_list Sentencia Metodo_invocacion Expresiones Expr Literal
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
            NodoId* nombres = $2;
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
         NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
         nodo_nombre->id = strcpy($1);
         nodo_nombre->sig = $3;
         $$ = nodo_nombre;
       }
       | Id
        {
          NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
          nodo_nombre->id = strcpy($1);
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

Bloque: LLAVE_IZQ Var_declaraciones Sentencias_list LLAVE_DER{
  $$ = crearNodo(NODO_SENTENCIAS,NULL,$2,$3);
}
;

Sentencias_list: Sentencia Sentencias_list
               | %empty
               ;

Sentencia: Id ASIGNACION Expr PUNTO_COMA
      {
        Simbolo* idEncontrado = buscarSimbolo($1, tablaSimbolos); // TODO: hacer trabla de simbolos y tipo Simbolo 

        if(idEncontrado == NULL) { // TODO poner linea de error
            fprintf(stderr, "Error: variable '%s' no declarada.\n", $1);
            exit(1);
        } else if(idEncontrado->tipo != $3->simbolo->tipo) {
            fprintf(stderr, "Error: tipo de dato incompatible en la asignación a '%s'.\n", $1);
            exit(1);
        }
        idEncontrado->valor = $3->simbolo->valor;

        Nodo* hojaId = crearNodo(NODO_IDENTIFICADOR, idEncontrado, NULL, NULL);

        $$ = crearNodo(NODO_ASIGNACION, NULL, hojaId, $3);
      }

      | Metodo_invocacion PUNTO_COMA
      
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque ELSE Bloque
      | WHILE Expr Bloque
      | RETURN Expr PUNTO_COMA
      | RETURN PUNTO_COMA
      ;

Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER
      {
        Simbolo* idEncontrado = buscarSimbolo($1, tablaSimbolos);

        if(idEncontrado == NULL) { // TODO poner linea de error
            fprintf(stderr, "Error: metodo '%s' no declarado.\n", $1);
            exit(1);
        }

        $$ = $1; //TODO: ver que hacer con la invocacion de metodos a nivel AST 
      }
      ;

Expresiones: Expr Expresiones
          | Expr
          ;
Expr: 
    Id
    | Metodo_invocacion
    | Literal
    | Expr Op_binario Expr
    {
      $2->izq = $1;
      $2->der = $3;

      $$ = $2;
    }
    | RESTA Expr
    {
      if ($2->simbolo->tipo != TIPO_INT && $2->simbolo->tipo != TIPO_FLOAT){
        fprintf(stderr, "Error: tipo de dato '%s' incompatible con operador '-'.\n", $2);
        exit(1);
      }

      $2->simbolo->valor = -$2->simbolo->valor;
      $$ = crearNodo(NODO_RESTA, NULL, NULL, $2);
    }
    | NOT Expr
    {
      if ($2->simbolo->tipo != TIPO_BOOLEAN){
        fprintf(stderr, "Error: tipo de dato '%s' incompatible con operador '!'.\n", $2);
        exit(1);
      }

      $2->simbolo->valor = abs($2->simbolo->valor - 1);
      $$ = crearNodo(NODO_RESTA, NULL, NULL, $2);
    }
    | PARENTESIS_IZQ Expr PARENTESIS_DER
    ;

Op_binario: Op_arit
          | Op_rel
          | Op_cond
          ;

Op_arit: SUMA
        { 
          $$ = crearNodo(NODO_SUMA, NULL, NULL, NULL);
        }
        | MULTIPLICACION 
        {
          $$ = crearNodo(NODO_MULTIPLICACION, NULL, NULL, NULL);
        }
        | RESTA
        {
          $$ = crearNodo(NODO_RESTA, NULL, NULL, NULL);
        }
        | DIV
        {
          $$ = crearNodo(NODO_DIVISION, NULL, NULL, NULL);
        }
        | MOD
        {
          $$ = crearNodo(NODO_MOD, NULL, NULL, NULL);
        }
        ;//TODO: resolver la inscripcion de simbolos para la TS en los operadores binarios 

Op_cond: 
AND{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_AND;
  simbolo->tipoSimbolo = AND_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_AND,simbolo,NULL,NULL);
} 
| OR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_OR;
  simbolo->tipoSimbolo = OR_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_OR,simbolo,NULL,NULL);
};

Op_rel: 
IGUALDAD{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_IGUALDAD;
  simbolo->tipoSimbolo = IGUALDAD_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_IGUALDAD,simbolo,NULL,NULL);
} 
| MENOR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_MENOR;
  simbolo->tipoSimbolo = MENOR_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_MENOR,simbolo,NULL,NULL);
}
| MAYOR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_MAYOR;
  simbolo->tipoSimbolo = MAYOR_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_MAYOR,simbolo,NULL,NULL);
};

Literal: 
INT_LITERAL
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_INT;
  simbolo->tipoSimbolo = INT_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearNodo(NODO_INT,simbolo,NULL,NULL);
} 
| FLOAT_LITERAL
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_FLOAT;
  simbolo->tipoSimbolo = FLOAT_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);// TODO: metodo necesario en la TS 
  
  $$ = crearNodo(NODO_FLOAT,simbolo,NULL,NULL);
}
| FALSE
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = BOOLEAN_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);
  
  $$ = crearNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
| TRUE
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = BOOLEAN_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);
  
  $$ = crearNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
;
%%

void yyerror(const char *s)
{
    fprintf(stderr,
            "Error sintáctico en la línea %d: %s\n",
            yylineno,
            s);
}
