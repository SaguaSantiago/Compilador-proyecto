#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static void uso(FILE *salida) {
  fprintf(salida,
          "Uso: c-tds [opcion] nombreArchivo.ctds\n"
          "Opciones:\n"
          "  -o <salida>          Renombra el archivo ejecutable a <salida>\n"
          "  -target <etapa>      Etapa hasta donde compilar: scan, parse,\n"
          "                       codinter o assembly\n"
          "  -opt [optimizacion]  Realiza la lista de optimizaciones (all = todas)\n"
          "  -debug               Imprime informacion de debugging\n");
}

static int termina_en(const char *s, const char *sufijo) {
  size_t ls = strlen(s);
  size_t lf = strlen(sufijo);
  return ls >= lf && strcmp(s + ls - lf, sufijo) == 0;
}

EtapaCompilacion procesarEtapa(char* etapaString){
  if(strcmp(etapaString, "scan") == 0) return SCAN;
  else if(strcmp(etapaString, "parse") == 0) return PARSE;
  else if(strcmp(etapaString, "codinter") == 0) return CODINTER;
  else if(strcmp(etapaString, "assembly") == 0) return ASSEMBLY;
}


Optimizacion procesarOptimizacion(char* optString){
  if(strcmp(optString, "all")) return ALL;
}

int optimizacionValida(char* optString){
  return strcmp(optString, "all");
}

int debug;

int main(int argc, char *argv[]) {

  const char *input = NULL;
  EtapaCompilacion target = ASSEMBLY;
  Optimizacion opt_val = ALL;  /* optimizaciones solicitadas      */
  const char *salida = NULL;   /* parametro de -o                 */
  debug = 0;
  int i;
  int ok;
  const char *ext;
  char *out_path;
  size_t len;

  for (i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if (strcmp(arg, "-o") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "error: falta un argumento para -o\n");
        uso(stderr);
        return 1;
      }
      salida = argv[++i];
    } else if (strcmp(arg, "-target") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "error: falta un argumento para -target\n");
        uso(stderr);
        return 1;
      }
      target = procesarEtapa(argv[++i]);
    } else if (strcmp(arg, "-opt") == 0) {
      if (optimizacionValida(argv[i+1])) {
        opt_val = procesarOptimizacion(argv[++i]);
      }
    } else if (strcmp(arg, "-debug") == 0) {
      debug = 1;
    } else if (arg[0] == '-') {
      fprintf(stderr, "error: opcion desconocida '%s'\n", arg);
      uso(stderr);
      return 1;
    } else {
      if (input != NULL) {
        fprintf(stderr, "error: se recibieron varios archivos de entrada\n");
        uso(stderr);
        return 1;
      }
      if (!termina_en(arg, ".ctds")) {
        fprintf(stderr, "error: el archivo debe tener extension .ctds: '%s'\n", arg);
        return 1;
      }
      input = arg;
    }
  }


  if (input == NULL) {
    fprintf(stderr, "error: falta el archivo de entrada\n");
    uso(stderr);
    return 1;
  }


  // if (target != SCAN && target != PARSE && target != CODINTER) { // TODO: implementar ASSEMBLY
  //   fprintf(stderr,
  //           "error: la etapa '%d' no esta implementada en esta entrega\n",
  //           target);
  //   return 1;
  // }


  if (debug) {
    logging_set_enabled(1);
  }

  log_debug("Entrada: %s", input);
  log_debug("Etapa solicitada: %d", target);
  log_debug("Optimizacion solicitada: %s", "ALL");

  log_debug("Abriendo archivo de entrada");
  yyin = fopen(input, "r");
  if (yyin == NULL) {
    fprintf(stderr, "error: no se puede abrir el archivo '%s'\n", input);
    return 1;
  }
  log_debug("Archivo de entrada abierto");

  ext = target == SCAN? "lex" : "sint";
  len = strlen(input);
  out_path = (char *)malloc(len + 8);
  snprintf(out_path, len + 8, "%.*s.%s", (int)(len - 5), input, ext);

  log_debug("Abriendo archivo de salida: %s", out_path);
  yyout = fopen(out_path, "w");
  if (yyout == NULL) {
    fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", out_path);
    fclose(yyin);
    free(out_path);
    return 1;
  }
  log_debug("Archivo de salida abierto");

  if(target == SCAN) {
    int resultado;
    log_debug("Iniciando analisis lexico");
    while ((resultado = yylex()) != 0) {
      if(resultado == -1) break;
    }
    ok = resultado != -1;
    if (ok) {
      fprintf(yyout, "Analisis lexico OK\n");
      log_debug("Analisis lexico finalizado correctamente");
    } else {
      log_debug("Analisis lexico finalizado con errores");
    }
  } else {
    if(target >= PARSE) {
      log_debug("Iniciando analisis sintactico");
      ok = yyparse() == 0;
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
    }

    if(target >= CODINTER) {
      log_debug("Iniciando generacion de codigo intermedio");
      construirCodigoIntermedio(raiz);
      log_debug("Mostrando codigo intermedio");
      mostrarCodigo();
      log_debug("Generacion de codigo intermedio finalizada");
    } // TODO: implementar
    if(target >= ASSEMBLY) {
      construirCodigoAssembly(codigoIntermedio, codigoCantidad);
    } // TODO: implementar
  }


  fclose(yyout);
  fclose(yyin);

  if (!ok) {
    log_debug("Compilacion fallida");
    fprintf(stderr, "error: compilacion fallida en la etapa '%d'\n", target);
    remove(out_path);
    free(out_path);
    return 1;
  }

  log_debug("Compilacion finalizada correctamente; salida: %s", out_path);

  free(out_path);
  return 0;
}