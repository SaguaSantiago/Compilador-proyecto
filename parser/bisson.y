%code requires {
  #include "compilador.h"
}

%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "compilador.h"
    extern int yylineno;

    int yylex(void);
    void yyerror(const char *s);
    ASTNodo *raiz;

    NodoSimbolo *listaParametros = NULL;
%}
%define parse.error detailed

%union {
  ASTNodo* nodo;
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
%type<nodo> Program Declaraciones Declaracion Var_declaraciones Var_declaracion Params_decl
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
              | %empty {$$ = NULL;}
              ; 

Declaracion: Var_declaracion {$$ = $1;}
           | Tipo_dato Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = $1;
            simbolo->nombre = strdup($2);
            simbolo->nodoBloque = $6;
            simbolo->parametros = listaParametros;
            listaParametros = NULL;
          
            $$ = crearASTNodo(NODO_DECL_MET, simbolo, $4, $6);
           }
           | VOID Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = TIPO_VOID;
            simbolo->nombre = strdup($2);
            simbolo->nodoBloque = $6;
            simbolo->parametros = listaParametros;
            listaParametros = NULL;
            $$ = crearASTNodo(NODO_DECL_MET, simbolo, $4, $6);
           }
           ;

Var_declaracion: Tipo_dato Id_list PUNTO_COMA 
           {
             TipoDato tipo = $1;
            NodoId* nombres = $2;
            ASTNodo* decl_raiz = NULL;
            ASTNodo* aux = NULL;

            while(nombres != NULL){
              Simbolo* simbolo = crearSimbolo();
              simbolo->tipoSimbolo = SIMBOLO_VAR_DECL;
              simbolo->tipoDato = tipo;
              simbolo->nombre = strdup(nombres->id);

              ASTNodo* nuevoNodo = crearASTNodo(NODO_DECL_VAR, simbolo, NULL, NULL);

              if (decl_raiz == NULL) {
                decl_raiz = nuevoNodo;
              } else {
                aux->izq = nuevoNodo;
              }
              aux = nuevoNodo;
              nombres = nombres->sig;
            }
            $$ = decl_raiz;
           }

Id_list: Id COMA Id_list 
       {
         NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
         nodo_nombre->id = strdup($1);
         nodo_nombre->sig = $3;
         $$ = nodo_nombre;
       }
       | Id
        {
          NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
          nodo_nombre->id = strdup($1);
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
            Simbolo* simbolo = crearSimbolo(); 
            simbolo->nombre = strdup($2);
            simbolo->tipoDato = $1;
            simbolo->tipoSimbolo = SIMBOLO_VAR_DECL; 

            agregarSimboloALista(simbolo, &listaParametros);
            ASTNodo *nodo = crearASTNodo(NODO_DECL_VAR, simbolo, NULL, NULL);
            
            $$ = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, $4);
           }
           | Tipo_dato Id
           {
            Simbolo* simbolo = crearSimbolo(); 
            simbolo->nombre = strdup($2);
            simbolo->tipoDato = $1;
            simbolo->tipoSimbolo = SIMBOLO_VAR_DECL; 

            agregarSimboloALista(simbolo, &listaParametros);
            ASTNodo *nodo = crearASTNodo(NODO_DECL_VAR, simbolo, NULL, NULL);
            $$ = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, NULL);
           }
           | %empty {$$ = NULL;}
           ;
    
Var_declaraciones: Var_declaracion Var_declaraciones // TODO: es correcto?
      {
          $$ = crearASTNodo(NODO_DECLS, NULL, $1, $2);
      }
      | %empty {$$ = NULL;}
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
        Simbolo* simboloId = crearSimbolo();
        simboloId->nombre = strdup($1);
        simboloId->tipoSimbolo = SIMBOLO_IDENTIFICADOR;
        ASTNodo* nodoId = crearASTNodo(NODO_IDENTIFICADOR, simboloId, NULL, NULL);

        Simbolo* simbolo = crearSimbolo();
        simbolo->nombre = $1; 
        simbolo->tipoSimbolo = SIMBOLO_ASIGNACION;

        $$ = crearASTNodo(NODO_ASIGNACION, simbolo, nodoId, $3);
      }

      | Metodo_invocacion PUNTO_COMA {$$ = $1;}
      
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque {
        $$ = crearASTNodo(NODO_IF, NULL, $3, $5);
      }
      | IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque ELSE Bloque {
        ASTNodo* bloques = crearASTNodo(NODO_BLOQUES_IF, NULL, $5, $7);
        $$ = crearASTNodo(NODO_IF_ELSE, NULL, $3, bloques);
      }
      | WHILE Expr Bloque {$$ = crearASTNodo(NODO_WHILE, NULL, $2, $3);}
      | RETURN Expr PUNTO_COMA {
        Simbolo* simbolo = crearSimbolo();
        simbolo->tipoSimbolo = SIMBOLO_RETURN;

        $$ = crearASTNodo(NODO_RETORNO, simbolo, $2, NULL);
        }
      | RETURN PUNTO_COMA {
        Simbolo* simbolo = crearSimbolo();
        simbolo->tipoSimbolo = SIMBOLO_RETURN;
        simbolo->tipoDato = TIPO_VOID;

        $$ = crearASTNodo(NODO_RETORNO, simbolo, NULL, NULL);
        }
      ;

Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER
      {
        Simbolo* simboloId = crearSimbolo();
        simboloId->nombre = strdup($1);
        simboloId->tipoSimbolo = SIMBOLO_IDENTIFICADOR;
        ASTNodo* nodoId = crearASTNodo(NODO_IDENTIFICADOR, simboloId, NULL, NULL);

        
        $$ = crearASTNodo(NODO_INVOCACION, NULL, nodoId, $3);
      }
      ;

Expresiones: Expr Expresiones {
            $$ = crearASTNodo(NODO_EXPRESIONES, NULL, $1, $2);
           }
          | Expr {
            $$ = $1;
          }
          ;
Expr:
    Id{
      Simbolo* simboloId = crearSimbolo();
      simboloId->tipoSimbolo = SIMBOLO_IDENTIFICADOR;
      simboloId->nombre = strdup($1);
      
      $$ = crearASTNodo(NODO_IDENTIFICADOR, simboloId, NULL, NULL);
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
      Simbolo* simbolo = crearSimbolo();
      simbolo->tipoSimbolo = SIMBOLO_RESTA;
      
      simbolo->tipoDato = $2->simbolo->tipoDato;
      $$ = crearASTNodo(NODO_RESTA, simbolo, $2, NULL);
    }
    | NOT Expr
    {
      Simbolo* simbolo = crearSimbolo();
      simbolo->tipoDato = TIPO_BOOLEAN;
      simbolo->tipoSimbolo = SIMBOLO_NOT;
      
      $2->simbolo->valor = abs($2->simbolo->valor - 1); //TODO ver si funciona
      $$ = crearASTNodo(NODO_NOT, simbolo, $2, NULL);
    }
    | PARENTESIS_IZQ Expr PARENTESIS_DER
    {
      $$ = $2; 
    }
    ;

Op_binario: Op_arit
          {$$ = $1;}
          | Op_cond
          {$$ = $1;}
          | Op_rel
          {$$ = $1;}
          ;

Op_arit: SUMA
        { 
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_SUMA;
          
          $$ = crearASTNodo(NODO_SUMA, simbolo, NULL, NULL);
        }
        | RESTA
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_RESTA;
          
          $$ = crearASTNodo(NODO_RESTA, simbolo, NULL, NULL);
        }
        | MULTIPLICACION 
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_MULTIPLICACION;
          
          $$ = crearASTNodo(NODO_MULTIPLICACION, simbolo, NULL, NULL);
        }
        | DIV
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_DIV;
          
          $$ = crearASTNodo(NODO_DIVISION, simbolo, NULL, NULL);
        }
        | MOD
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_MOD;
          
          $$ = crearASTNodo(NODO_MOD, simbolo, NULL, NULL);
        }
        ;

Op_cond: 
AND{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_AND;
  

  $$ = crearASTNodo(NODO_AND,simbolo,NULL,NULL);
} 
| OR{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_OR;
  

  $$ = crearASTNodo(NODO_OR,simbolo,NULL,NULL);
};

Op_rel: 
IGUALDAD{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_IGUALDAD;
  

  $$ = crearASTNodo(NODO_IGUALDAD,simbolo,NULL,NULL);
} 
| MENOR{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_MENOR;
  

  $$ = crearASTNodo(NODO_MENOR,simbolo,NULL,NULL);
}
| MAYOR{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_MAYOR;
  

  $$ = crearASTNodo(NODO_MAYOR,simbolo,NULL,NULL);
};

Literal: 
INT_LITERAL
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_INTEGER;
  simbolo->tipoSimbolo = SIMBOLO_INTEGER_LITERAL;
  simbolo->valor = $1;
  

  $$ = crearASTNodo(NODO_INT,simbolo,NULL,NULL);
} 
| FLOAT_LITERAL
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_FLOAT;
  simbolo->tipoSimbolo = SIMBOLO_FLOAT_LITERAL;
  simbolo->valor = $1;
  
  $$ = crearASTNodo(NODO_FLOAT,simbolo,NULL,NULL);
}
| FALSE
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_BOOLEAN_LITERAL;
  simbolo->valor = $1;
  
  $$ = crearASTNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
| TRUE
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_BOOLEAN_LITERAL;
  simbolo->valor = $1;
  
  
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
