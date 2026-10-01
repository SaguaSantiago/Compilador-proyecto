#ifndef AST_DEF_H
#define AST_DEF_H
#include "enums.h"
#include "tipos.h"

typedef enum TipoNodo {
  NODO_ROOT,
  NODO_DECL_VAR,
  NODO_DECL_MET,
  NODO_DECLS,
  NODO_PARAM_DECL,
  NODO_EXPRESIONES,
  NODO_INVOCACION,
  NODO_SENTENCIAS,
  NODO_ASIGNACION,
  NODO_IF,
  NODO_IF_ELSE,
  NODO_BLOQUES_IF,
  NODO_WHILE,
  NODO_BLOQUE,
  NODO_RETORNO,
  NODO_SUMA,
  NODO_MULTIPLICACION,
  NODO_IDENTIFICADOR,
  NODO_RESTA,
  NODO_DIVISION,
  NODO_MOD,
  NODO_AND,
  NODO_OR,
  NODO_NOT,
  NODO_IGUALDAD,
  NODO_MAYOR,
  NODO_MENOR,
  NODO_FLOAT,
  NODO_INT,
  NODO_BOOLEAN,
  NODO_PROGRAMA
} TipoNodo;

typedef struct ASTNodo {
  Simbolo *simbolo;
  TipoNodo tipo;

  struct ASTNodo *izq;
  struct ASTNodo *der;
} ASTNodo;

/**
 * Tipo de nodo que compone lista de ids
 * Se utiliza para la multiple declaracion de variables de un mismo tipo
 * */
typedef struct Nodo_Id {
  struct Nodo_Id *sig;
  char *id;
} NodoId;

/**
 * Crea un nuevo nodo del arbol sintactico
 * (En caso de que se desee una hoja *izq,*der = NULL)
 * */
ASTNodo *crearASTNodo(TipoNodo tipo, Simbolo *simbolo, ASTNodo *izq,
                      ASTNodo *der);

#endif
