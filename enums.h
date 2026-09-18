#ifndef ENUMS_H
#define ENUMS_H

/**
 * Tipos de datos del lenguaje
 * */
typedef enum Tipo_Dato { TIPO_INTEGER, TIPO_FLOAT, TIPO_BOOLEAN } Tipo_Dato;

/**
  Tipos de Nodos del arbol ast
  */
typedef enum Tipo_Nodo {
  // Aca iran los tipos de nodos del arbol
  // TODO: definir tipos
  Nodo
} Tipo_Nodo;

typedef struct Nodo {
  Tipo_Nodo tipoNodo;
} ASTNodo;
#endif
