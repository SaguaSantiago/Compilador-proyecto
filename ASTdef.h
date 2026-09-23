#ifndef AST_DEF_H
#define AST_DEF_H
typedef struct Simbolo {
} Simbolo; // TODO: Sacar el tipo en un archivo dedicado a la tabla de simbolos

typedef enum TipoNodo {
  NODO_ROOT,
  NODO_DECL_VAR,
  NODO_DECL_MET,
  NODO_DECLS,
  NODO_SENTENCIAS,
  NODO_ASIGNACION,
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

typedef struct Nodo {
  Simbolo *simbolo;
  TipoNodo tipo;

  struct Nodo *izq;
  struct Nodo *der;
} ASTNodo;

/**
 * Tipo de nodo que compone lista de ids
 * Se utiliza para la multiple declaracion de variables de un mismo tipo
 * */
typedef struct Nodo_Id {
  struct Nodo_Id *sig;
  char *Id;
} NodoId;

/**
 * Crea un nuevo nodo del arbol sintactico
 * (En caso de que se desee una hoja *izq,*der = NULL)
 * */
ASTNodo *crearNodo(TipoNodo tipo, Simbolo *simbolo, ASTNodo *izq, ASTNodo *der);

#endif
