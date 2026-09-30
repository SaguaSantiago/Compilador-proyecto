#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yyparse(void);
extern int yylex(void);

/* Definidos en lex.yy.c */
extern FILE *yyin;
extern FILE *yyout;
extern int error_lexico;

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

int main(int argc, char *argv[]) {
  const char *input = NULL;
  const char *target = NULL;   /* NULL = etapa corriente (parse) */
  const char *opt_val = NULL;  /* optimizaciones solicitadas      */
  const char *salida = NULL;   /* parametro de -o                 */
  int debug = 0;
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
      target = argv[++i];
    } else if (strcmp(arg, "-opt") == 0) {
      if (i + 1 < argc && strcmp(argv[i + 1], "all") == 0) {
        opt_val = argv[++i];
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

  if (target == NULL) {
    target = "parse"; /* etapa corriente */
  }

  if (strcmp(target, "scan") != 0 && strcmp(target, "parse") != 0) {
    fprintf(stderr,
            "error: la etapa '%s' no esta implementada en esta entrega\n",
            target);
    return 1;
  }

  if (salida != NULL) {
    fprintf(stderr,
            "aviso: opcion -o ignorada (en esta etapa no se genera ejecutable)\n");
  }

  if (debug) {
    printf("debug: entrada %s\n", input);
    printf("debug: etapa %s\n", target);
    printf("debug: optimizaciones %s\n", opt_val != NULL ? opt_val : "ninguna");
  }

  yyin = fopen(input, "r");
  if (yyin == NULL) {
    fprintf(stderr, "error: no se puede abrir el archivo '%s'\n", input);
    return 1;
  }

  ext = (strcmp(target, "scan") == 0) ? "lex" : "sint";
  len = strlen(input);
  out_path = (char *)malloc(len + 8);
  snprintf(out_path, len + 8, "%.*s.%s", (int)(len - 5), input, ext);

  yyout = fopen(out_path, "w");
  if (yyout == NULL) {
    fprintf(stderr, "error: no se puede crear el archivo de salida '%s'\n", out_path);
    fclose(yyin);
    free(out_path);
    return 1;
  }

  if (strcmp(target, "scan") == 0) {
    while (yylex() != 0) {
    }
    ok = (error_lexico == 0);
    if (ok) {
      fprintf(yyout, "Analisis lexico OK\n");
    }
  } else {
    ok = (yyparse() == 0 && error_lexico == 0);
    if (ok) {
      fprintf(yyout, "Analisis sintactico OK\n");
    }
  }

  fclose(yyout);
  fclose(yyin);

  if (!ok) {
    fprintf(stderr, "error: compilacion fallida en la etapa '%s'\n", target);
    remove(out_path);
    free(out_path);
    return 1;
  }

  if (debug) {
    printf("debug: salida %s\n", out_path);
  }

  free(out_path);
  return 0;
}