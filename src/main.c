#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "semantica.h"
#include "codigoIntermedio.h"
#include "generacionAssembly.h"
#include "CIdef.h"
#include "Logging.h"

extern int yyparse(void);
extern int yylex(void);
extern ASTNodo* raiz;

/* Definidos en lex.yy.c */
extern FILE *yyin;
extern FILE *yyout;
extern int error_lexico;

extern Instruccion* codigoIntermedio;
extern int codigoCantidad;

/* Se llama al final del archivo; 1 = no hay mas entradas. */
int yywrap(void) { return 1; }

static int ejecutarCompilacion(const Opciones *op);
static int etapaScan(const Opciones *op);
static char *rutaSalida(const char *base, const char *sufijo);
static int etapaParse(const Opciones *op);
static int etapaCodinter(const Opciones *op);
static int etapaAssembly(const Opciones *op);

int main(int argc, char *argv[]) {
  Opciones op;

  if (parsearOpciones(argc, argv, &op) != 0) {
    liberarOpciones(&op);
    return 1;
  }
  
  if (op.debug) {
    logging_set_enabled(1);
  }

  int rc = ejecutarCompilacion(&op);
  liberarOpciones(&op);
  return rc;
}

static int ejecutarCompilacion(const Opciones *op) {
  log_debug("Entrada: %s", op->entrada);
  log_debug("Etapa solicitada: %d", op->target);
  log_debug("Optimizacion solicitada: %d", op->opt);

  log_debug("Abriendo archivo de entrada");
  yyin = fopen(op->entrada, "r");
  if (yyin == NULL) {
    fprintf(stderr, "error: no se puede abrir el archivo '%s'\n", op->entrada);
    return 1;
  }
  log_debug("Archivo de entrada abierto");

  int rc;
  if (op->target == SCAN) {
    rc = etapaScan(op);
  } else {
    rc = etapaParse(op);
    if (rc == 0 && op->target >= CODINTER) rc = etapaCodinter(op);
    if (rc == 0 && op->target >= ASSEMBLY) rc = etapaAssembly(op);
  }

  fclose(yyin);
  yyin = NULL;

  if (rc != 0) {
    log_debug("Compilacion fallida");
    fprintf(stderr, "error: compilacion fallida en la etapa '%d'\n", op->target);
  } else {
    log_debug("Compilacion finalizada correctamente");
  }

  return rc;
}


static char *rutaSalida(const char *base, const char *sufijo) {
  size_t len = strlen(base) + strlen(sufijo) + 2;
  char *ruta = (char *)malloc(len);
  if (ruta == NULL) return NULL;
  snprintf(ruta, len, "%s.%s", base, sufijo);
  return ruta;
}

static int etapaScan(const Opciones *op) {
  char *ruta = rutaSalida(op->salida, "lex");
  if (ruta == NULL) {
    fprintf(stderr, "error: sin memoria\n");
    return 1;
  }

  log_debug("Abriendo archivo de salida: %s", ruta);
  yyout = fopen(ruta, "w");
  if (yyout == NULL) {
    fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", ruta);
    free(ruta);
    return 1;
  }

  log_debug("Iniciando analisis lexico");
  int resultado;
  while ((resultado = yylex()) != 0) {
    if (resultado == -1) break;
  }
  int ok = resultado != -1;

  if (ok) {
    fprintf(yyout, "Analisis lexico OK\n");
    log_debug("Analisis lexico finalizado correctamente");
  } else {
    log_debug("Analisis lexico finalizado con errores");
  }

  fclose(yyout);
  yyout = NULL;

  if (!ok) {
    remove(ruta);
    free(ruta);
    return 1;
  }

  log_debug("Compilacion finalizada correctamente; salida: %s", ruta);
  free(ruta);
  return 0;
}

static int etapaParse(const Opciones *op) {
  char *ruta = rutaSalida(op->salida, "sint");
  if (ruta == NULL) {
    fprintf(stderr, "error: sin memoria\n");
    return 1;
  }

  log_debug("Abriendo archivo de salida: %s", ruta);
  yyout = fopen(ruta, "w");
  if (yyout == NULL) {
    fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", ruta);
    free(ruta);
    return 1;
  }

  log_debug("Iniciando analisis sintactico");
  int ok = yyparse() == 0;
  if (ok) {
    fprintf(yyout, "Analisis sintactico OK\n");
    log_debug("Analisis sintactico finalizado correctamente");
    log_debug("Iniciando analisis semantico");
    analisisSemantico(raiz);
    fprintf(yyout, "Analisis semantico OK\n");
    log_debug("Analisis semantico finalizado");
  } else {
    log_debug("Analisis sintactico finalizado con errores");
  }

  fclose(yyout);
  yyout = NULL;

  if (!ok) {
    remove(ruta);
    free(ruta);
    return 1;
  }

  free(ruta);
  return 0;
}

static int etapaCodinter(const Opciones *op) {
  log_debug("Iniciando generacion de codigo intermedio");
  construirCodigoIntermedio(raiz);

  if (op->debug) {
    log_debug("Mostrando codigo intermedio");
    mostrarCodigo(stdout);
  } else {
    char *ruta = rutaSalida(op->salida, "int");
    if (ruta == NULL) {
      fprintf(stderr, "error: sin memoria\n");
      return 1;
    }

    FILE *intFile = fopen(ruta, "w");
    if (intFile == NULL) {
      fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", ruta);
      free(ruta);
      return 1;
    }

    log_debug("Escribiendo codigo intermedio");
    mostrarCodigo(intFile);
    fclose(intFile);
    free(ruta);
  }

  log_debug("Generacion de codigo intermedio finalizada");
  return 0;
}

static int etapaAssembly(const Opciones *op) {
  log_debug("Iniciando generacion de codigo Assembly");
  log_debug("Abriendo archivo assembly");
  
  char *ruta = rutaSalida(op->salida, "s");
  FILE* f = fopen(ruta, "w");
  if (f == NULL) {
    fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", ruta);
    free(ruta);
    return 1;
  }

  log_debug("construyendo...");
  construirCodigoAssembly(f, codigoIntermedio, codigoCantidad);
  
  fprintf(stdout, "Assembly generado en el archivo: %s\n", ruta);
  fclose(f);
  free(ruta);
  return 0;
}
