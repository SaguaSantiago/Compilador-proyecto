#include "cli.h"

#include <stdlib.h>
#include <string.h>

static int termina_en(const char *s, const char *sufijo) {
  size_t ls = strlen(s);
  size_t lf = strlen(sufijo);
  return ls >= lf && strcmp(s + ls - lf, sufijo) == 0;
}

static int parsearEtapa(const char *texto, EtapaCompilacion *etapa) {
  if (strcmp(texto, "scan") == 0) *etapa = SCAN;
  else if (strcmp(texto, "parse") == 0) *etapa = PARSE;
  else if (strcmp(texto, "codinter") == 0) *etapa = CODINTER;
  else if (strcmp(texto, "assembly") == 0) *etapa = ASSEMBLY;
  else return 0;
  return 1;
}

static int parsearOptimizacion(const char *texto, Optimizacion *opt) {
  if (strcmp(texto, "all") == 0) {
    *opt = ALL;
    return 1;
  }
  return 0;
}

static char *derivarSalida(const char *entrada) {
  size_t len = strlen(entrada);
  size_t base = len - strlen(".ctds");
  char *salida = (char *)malloc(base + 1);
  if (salida == NULL) return NULL;
  memcpy(salida, entrada, base);
  salida[base] = '\0';
  return salida;
}

void imprimirUso(FILE *salida) {
  fprintf(salida,
          "Uso: c-tds [opcion] nombreArchivo.ctds\n"
          "Opciones:\n"
          "  -o <salida>          Renombra el archivo ejecutable a <salida>\n"
          "  -target <etapa>      Etapa hasta donde compilar: scan, parse,\n"
          "                       codinter o assembly\n"
          "  -opt [optimizacion]  Realiza la lista de optimizaciones (all = todas)\n"
          "  -debug               Imprime informacion de debugging\n");
}

int parsearOpciones(int argc, char *argv[], Opciones *op) {
  op->entrada = NULL;
  op->salida = NULL;
  op->target = ASSEMBLY;
  op->opt = ALL;
  op->debug = 0;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if (strcmp(arg, "-o") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "error: falta un argumento para -o\n");
        imprimirUso(stderr);
        return 1;
      }
      free(op->salida);
      op->salida = strdup(argv[++i]);
      if (op->salida == NULL) {
        fprintf(stderr, "error: sin memoria\n");
        return 1;
      }
    } else if (strcmp(arg, "-target") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "error: falta un argumento para -target\n");
        imprimirUso(stderr);
        return 1;
      }
      if (!parsearEtapa(argv[++i], &op->target)) {
        fprintf(stderr, "error: etapa desconocida '%s'\n", argv[i]);
        imprimirUso(stderr);
        return 1;
      }
    } else if (strcmp(arg, "-opt") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "error: falta un argumento para -opt\n");
        imprimirUso(stderr);
        return 1;
      }
      if (!parsearOptimizacion(argv[++i], &op->opt)) {
        fprintf(stderr, "error: optimizacion desconocida '%s'\n", argv[i]);
        imprimirUso(stderr);
        return 1;
      }
    } else if (strcmp(arg, "-debug") == 0) {
      op->debug = 1;
    } else if (arg[0] == '-') {
      fprintf(stderr, "error: opcion desconocida '%s'\n", arg);
      imprimirUso(stderr);
      return 1;
    } else {
      if (op->entrada != NULL) {
        fprintf(stderr, "error: se recibieron varios archivos de entrada\n");
        imprimirUso(stderr);
        return 1;
      }
      if (!termina_en(arg, ".ctds")) {
        fprintf(stderr, "error: el archivo debe tener extension .ctds: '%s'\n", arg);
        return 1;
      }
      op->entrada = arg;
    }
  }

  if (op->entrada == NULL) {
    fprintf(stderr, "error: falta el archivo de entrada\n");
    imprimirUso(stderr);
    return 1;
  }

  if (op->salida == NULL) {
    op->salida = derivarSalida(op->entrada);
    if (op->salida == NULL) {
      fprintf(stderr, "error: sin memoria\n");
      return 1;
    }
  }

  return 0;
}

void liberarOpciones(Opciones *op) {
  free(op->salida);
  op->salida = NULL;
}
