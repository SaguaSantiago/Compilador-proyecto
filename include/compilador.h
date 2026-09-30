#ifndef COMPILADOR_H
#define COMPILADOR_H

/**
 * Header agregador para los modulos que necesitan el AST y la tabla de
 * simbolos a la vez (por ejemplo el parser).
 *
 * El orden importa: enums.h debe ir primero porque struct Simbolo guarda
 * TipoSimbolo y TipoDato por valor, que necesitan estar completos.
 * */

#include "enums.h"
#include "tipos.h"
#include "ASTdef.h"
#include "TSdef.h"

#endif