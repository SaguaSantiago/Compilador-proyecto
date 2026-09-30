%code requires {
  #include "compilador.h"
}

%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include "compilador.h"
    extern int yylineno;

    int yylex(void);
    void yyerror(const char *s);
    ASTNodo *raiz;

    NodoSimbolo *listaExpresiones = NULL;
%}
%define parse.error detailed

%union {
  ASTNodo nodo;
  TipoDato tipo_dato;
  int valor_int;
  float valor_float;
  char* nombre;
  NodoId* lista_nombres;
}

%token MAIN BOOLEAN VOID RETURN SUMA MULTIPLICACION ASIGNACION INT FLOAT PARENTESIS_IZQ PARENTESIS_DER LLAVE_IZQ LLAVE_DER PUNTO_COMA COMA IF ELSE WHILE AND OR NOT MAYOR MENOR IGUALDAD MOD RESTA DIV
%token<valor_float> FLOAT_LITERAL
%token<valor_int> INT_LITERAL TRUE FALSE // Podriamos poner BOOLEAN_LITERAL pero tendriamos que comparar strings en Flex. 
%token<nombre> Id

%type<tipo_dato> Tipo_dato
%type<nodo> Program Declaraciones Declaracion Var_declaraciones Params_decl
%type<nodo> Bloque Sentencias_list Sentencia 
%type<nodo> Metodo_invocacion Expresiones Expr Literal 
%type<nodo> Op_binario Op_arit Op_cond Op_rel 
%type<lista_nombres> Id_list
%start Program
%%

Program: Declaraciones
       {
        raiz = crearASTNodo(NODO_ROOT, NULL, $1, NULL);
       }
       ;

Declaraciones: Declaracion Declaraciones 
              {
                $$ = crearASTNodo(NODO_DECLS, NULL, $1, $2);
              }
              ; 

Declaracion: Tipo_dato Id_list PUNTO_COMA 
           {
            TipoDato tipo = $1;
            NodoId* nombres = $2;
            ASTNodo* decl_raiz = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            ASTNodo* aux = decl_raiz;

            while(nombres != NULL){
              Simbolo* simbolo = crearSimbolo();
              simbolo->tipoSimbolo = SIMBOLO_VAR_DECL;
              simbolo->tipoDato = tipo;
              simbolo->nombre = strdup(nombres->id);
              
              agregarSimbolo(simbolo, ts);

              ASTNodo* nuevoNodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
              aux->izq = nuevoNodo;
              aux = nuevoNodo;
              nombres = nombres->sig;
            }
            free(aux);
            $$ = decl_raiz;
           }
           | Tipo_dato Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = $1;
            simbolo->nombre = strdup($2);
            simbolo->nodoBloque = $6;
            
            agregarSimbolo(simbolo, ts);
            $$ = crearASTNodo(NODO_DECL_MET, simbolo, $4, NULL);
           }
           | VOID Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = $1;
            simbolo->nombre = strdup($2);
            simbolo->nodoBloque = $6;

            agregarSimbolo(simbolo, ts);
            $$ = crearASTNodo(NODO_DECL_MET, simbolo, $4, NULL);
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
            ASTNodo nodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            
            $$ = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, $4);
           }
           | Tipo_dato Id
           {
            ASTNodo nodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            $$ = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, NULL);
           }
           | %empty
           {
            $$ = NULL;
           }
           ;
    
Var_declaraciones: Declaracion Var_declaraciones
      {
          $$ = crearASTNodo(NODO_DECLS, NULL, $1, $2);
      }
;

Bloque: LLAVE_IZQ Var_declaraciones Sentencias_list LLAVE_DER{
  $$ = crearASTNodo(NODO_BLOQUE,NULL,$2,$3);
}
;

Sentencias_list: Sentencia Sentencias_list {$$ = crearASTNodo(NODO_SENTENCIAS, NULL, $1, $2);}
               | %empty {$$ = NULL;}
               ;

Sentencia: Id ASIGNACION Expr PUNTO_COMA
      {
        Simbolo* idEncontrado = buscarSimbolo($1, tablaSimbolos); 

        if(idEncontrado == NULL) { // TODO poner linea de error
            fprintf(stderr, "Error: variable '%s' no declarada.\n", $1);
            exit(1);
        } else if(idEncontrado->tipo != $3->simbolo->tipo) {
            fprintf(stderr, "Error: tipo de dato incompatible en la asignación a '%s'.\n", $1);
            exit(1);
        }
        idEncontrado->valor = $3->simbolo->valor;

        Nodo* hojaId = crearASTNodo(NODO_IDENTIFICADOR, idEncontrado, NULL, NULL);

        $$ = crearASTNodo(NODO_ASIGNACION, NULL, hojaId, $3);
      }

      | Metodo_invocacion PUNTO_COMA {$$ = $1}
      
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque {
        ASTNodo* bloques = crearASTNodo(NODO_BLOQUES_IF, NULL, $5, NULL);
        $$ = crearASTNodo(NODO_IF, NULL, $3, bloques);
      }
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque ELSE Bloque {
        ASTNodo* bloques = crearASTNodo(NODO_BLOQUES_IF, NULL, $5, $7);
        
        $$ = crearASTNodo(NODO_IF_ELSE, NULL, $3, bloques);
      }
      | WHILE Expr Bloque {$$ = crearASTNodo(NODO_WHILE, NULL, $2, $3);}
      | RETURN Expr PUNTO_COMA {$$ = crearASTNodo(NODO_RETURN, NULL, $2, NULL);}
      | RETURN PUNTO_COMA {$$ = crearASTNodo(NODO_RETURN, NULL, NULL, NULL);}
      ;

Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER
      {
       NodoSimbolo* expresiones = listaExpresiones;
       free(listaExpresiones);
       listaExpresiones = NULL;
       
       $$ = crearASTNodo(NODO_INVOCACION, NULL, $3, NULL);
       }
      ;

Expresiones: Expr Expresiones {
            agregarSimboloALista($1->simbolo, listaExpresiones);
            $$ = crearASTNodo(NODO_EXPRESIONES, NULL, $1, $2);
           }
          | Expr {
            $$ = $1;
          }
          ;
Expr:
    Id{
      Simbolo* simbolo = buscarSimbolo($1, tablaSimbolos);
      if(simbolo == NULL){
        fprintf(stderr, "Error: identificador '%s' no declarado.\n", $1);
        exit(1);
      }
      $$ = crearASTNodo(NODO_IDENTIFICADOR, simbolo, NULL, NULL);
    }
    | Metodo_invocacion {$$ = $1;}
    | Literal {$$ = $1;}
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
      Simbolo* simbolo = malloc(sizeof(Simbolo));
      simbolo->tipoSimbolo = SIMBOLO_RESTA;
      agregarSimbolo(simbolo, tablaSimbolos);
      $2->simbolo->valor = -$2->simbolo->valor; //TODO funciona?
      $$ = crearASTNodo(NODO_RESTA, simbolo, NULL, $2);
    }
    | NOT Expr
    {
      if ($2->simbolo->tipo != TIPO_BOOLEAN){
        fprintf(stderr, "Error: tipo de dato '%s' incompatible con operador '!'.\n", $2);
        exit(1);
      }

      Simbolo* simbolo = malloc(sizeof(Simbolo));
      simbolo->tipo = TIPO_BOOLEAN;
      simbolo->tipoSimbolo = SIMBOLO_NOT;
      agregarSimbolo(simbolo, tablaSimbolos);
      $2->simbolo->valor = abs($2->simbolo->valor - 1); //TODO ver si funciona
      $$ = crearASTNodo(NODO_NOT, simbolo, NULL, $2);
    }
    | PARENTESIS_IZQ Expr PARENTESIS_DER
    {
      $$ = $2; 
    }
    ;

Op_binario: Op_arit
          {$$ = $1;}
          | Op_rel
          {$$ = $1;}
          | Op_cond
          {$$ = $1;}
          ;

Op_arit: SUMA
        { 
          Simbolo* simbolo = malloc(sizeof(Simbolo));
          simbolo->tipoSimbolo = SIMBOLO_SUMA;
          agregarSimbolo(simbolo, tablaSimbolos);
          $$ = crearASTNodo(NODO_SUMA, simbolo, NULL, NULL);
        }
        | MULTIPLICACION 
        {
          Simbolo* simbolo = malloc(sizeof(Simbolo));
          simbolo->tipoSimbolo = SIMBOLO_MULTIPLICACION;
          agregarSimbolo(simbolo, tablaSimbolos);
          $$ = crearASTNodo(NODO_MULTIPLICACION, simbolo, NULL, NULL);
        }
        | RESTA
        {
          Simbolo* simbolo = malloc(sizeof(Simbolo));
          simbolo->tipoSimbolo = SIMBOLO_RESTA;
          agregarSimbolo(simbolo, tablaSimbolos);
          $$ = crearASTNodo(NODO_RESTA, simbolo, NULL, NULL);
        }
        | DIV
        {
          Simbolo* simbolo = malloc(sizeof(Simbolo));
          simbolo->tipoSimbolo = SIMBOLO_DIV;
          agregarSimbolo(simbolo, tablaSimbolos);
          $$ = crearASTNodo(NODO_DIV, simbolo, NULL, NULL);
        }
        | MOD
        {
          Simbolo* simbolo = malloc(sizeof(Simbolo));
          simbolo->tipoSimbolo = SIMBOLO_MOD;
          agregarSimbolo(simbolo, tablaSimbolos);
          $$ = crearASTNodo(NODO_MOD, simbolo, NULL, NULL);
        }
        ;

Op_cond: 
AND{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_AND;
  simbolo->tipoSimbolo = AND_SIM;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_AND,simbolo,NULL,NULL);
} 
| OR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_OR;
  simbolo->tipoSimbolo = OR_SIM;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_OR,simbolo,NULL,NULL);
};

Op_rel: 
IGUALDAD{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_IGUALDAD;
  simbolo->tipoSimbolo = IGUALDAD_SIM;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_IGUALDAD,simbolo,NULL,NULL);
} 
| MENOR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_MENOR;
  simbolo->tipoSimbolo = MENOR_SIM;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_MENOR,simbolo,NULL,NULL);
}
| MAYOR{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_MAYOR;
  simbolo->tipoSimbolo = MAYOR_SIM;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_MAYOR,simbolo,NULL,NULL);
};

Literal: 
INT_LITERAL
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_INT;
  simbolo->tipoSimbolo = INT_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);

  $$ = crearASTNodo(NODO_INT,simbolo,NULL,NULL);
} 
| FLOAT_LITERAL
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_FLOAT;
  simbolo->tipoSimbolo = FLOAT_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);// TODO: metodo necesario en la TS 
  
  $$ = crearASTNodo(NODO_FLOAT,simbolo,NULL,NULL);
}
| FALSE
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = BOOLEAN_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);
  
  $$ = crearASTNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
| TRUE
{
  Simbolo* simbolo = (Simbolo*) malloc(sizeof(Simbolo));
  simbolo->tipo = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = BOOLEAN_SIM;
  simbolo->valor = $1;
  agregarSimbolo(simbolo, tablaSimbolos);
  
  $$ = crearASTNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
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
