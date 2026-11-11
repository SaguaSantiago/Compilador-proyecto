#ifndef GENERACION_ASSEMBLY_H
#define GENERACION_ASSEMBLY_H
#include "CIdef.h"

void construirCodigoAssembly(FILE* out, Instruccion *codigoIntermedio, int codigoCantidad);
#endif