#ifndef UTILS_H
#define UTILS_H
#include "tipos.h"
#include "TSdef.h"

const char* nombreTipo(TipoDato tipo);
void lanzarError(ASTNodo *nodo, const char *formato, ...);
int chequearTipos(TipoDato tipoEsperado, int cantidadTipos,...);
int esTipoNumerico(TipoDato tipo);
int procesarOpNumerica(ASTNodo *nodo);
int procesarOpBooleano(ASTNodo *nodo);
int procesarComparacion(ASTNodo *nodo);

#endif