# Documentación — Proyecto de Taller de Diseño de Software 

Etapa: **1 (análisis léxico y sintáctico)** ·

---

## 0. Compilación, ejecución y testing 

Requisitos: solo `gcc` y `make`.

* `make all`          # compila c-tds (o c-tds.exe con mingw32-make en Windows)
* `make run`          # ejecuta el compilador sobre pruebas/ejemplo.ctds
* `make test`         # corre la suite de tests (tests/run_tests.sh)
* `make gen`          # regenera bisson.tab.c/h y lex.yy.c desde bisson.y y lex.l
* `make clean`        # elimina binarios y objetos

Uso del compilador:

c-tds [opcion] nombreArchivo.ctds

  - `-o < salida >:`          renombra el ejecutable a < salida > (se valida y se avisa
                       que en esta etapa no se genera ejecutable)
  - `-target < etapa >:`      scan | parse | codinter | assembly
  - `-opt [optimizacion]:`  lista de optimizaciones; se acepta "all" sin efecto
                       hasta la etapa de optimización
  - `-debug:`               imprime información de debugging en stdout


Salidas: `-target parse` (default) genera `<nombre>.sint`; `-target scan` genera
`<nombre>.lex`. Ambos contienen el listado de los tokens reconocidos por el analizador y la línea
`Analisis sintactico OK` / `Analisis lexico OK`. Cualquier error va a stderr, el proceso termina con exit code 1.

---

## 1. División del trabajo en la etapa

El trabajo se repartió de la siguiente manera :

- **Lucas Lillo** : correccion de conflictos gramaticales, testing y documentación.
- **Santiago Sagua** : correccion de conflictos gramaticales, gramática base y lexer inicial 
- **Paloma Brizuela** : aportes gramaticales y lexer inicial 

---

## 2. Decisiones de diseño

Decisiones tomadas en esta etapa:

En esta etapa se tomaron desiciones base para la construcción del compilador, tales como: 
* Decidir la forma lexica de los `floats`.
* Establecer el comportamiento del signo `-` tanto en su uso como operador binario o como operador unario.
* Corregir conflictos gramaticales en ciertas partes de la gramatica (principalmente conflictos `shift/reduce` de las declaraciones).
* Organizar la gramatica a una versión optima para realizar los futuros avances. 
* Los literales `true` / `false` se modelan como `1` / `0`.

---

## 3. Descripción del diseño y decisiones clave

### Arquitectura

El compilador tiene tres módulos:

- `main.c` : apertura de `yyin`/`yyout`, decisión de la etapa y manejo del
  resultado (exit codes, limpieza del archivo de salida).
- `lex.l` : analizador léxico (Flex). Cada regla imprime el token
  reconocido en `yyout` y devuelve
  el token al parser. Ante un carácter inesperado setea `error_lexico`,
  reporta línea y carácter.
- `bisson.y`: analizador sintáctico (Bison). Solo valida la
  secuencia de tokens e informa errores con `yylineno`. El final exitoso queda
  señalado por el mensaje OK que escribe `main.c`.

### Alternativas consideradas y justificación

En esta primera etapa no nos encontramos con muchas deciciones considerables puesto que tendio a ser un desarrollo muy estructurado. Se analizaron alternativas a futuro como el modo de construcción del AST y la LS para ciertos nodos conflictivos, se anotaron prevenciones de posibles conflictos futuros, como la asignación de simbolos en los operadores binarios con respecto a la actual implementación de la gramatica. 

### Deficiencias detectadas y alternativas propuestas

- **conflictos shift/reduce** en la gramática. Se optó por modificar aspectos clave de la gramatica como la factorización de las declaraciones de variables y las decalaraciones de metodos.

---

## 4. Detalles de implementación interesantes

- **La salida es una impresión del propio lexer.** Cada regla de `lex.l` hace
  `fprintf(yyout, "TOKEN\n")`. Esto simplifica el debuggin del proceso.
- **Reporte de línea uniforme.** Tanto `yyerror` como el error léxico usan
  `yylineno` para ubicar el error.
- **Diseño de tests.** Se asignó una convención de nombres `ok_*`/`scan_*`/`bad_*`
  que evita llamar un expect/plan por caso.
- **Makefile portable.** Selección de shell y comando de borrado según SO, y
  entrega de los archivos generados por bison/flex para que el build no exija
  herramientas fuera de `gcc`.

---

## 5. Problemas conocidos

1. **El lexer original no tokenizaba la coma (`,`).** 
   Un programa legal con `int a, b;`  fallaba en el parse.
   Se pudo corregir agregando `"," → COMA` en `lex.l`. Caso de test `ok_declaraciones_variables` lo cubre; el caso
   `bad_comas_en_llamada` verifica que la COMA siga estando prohibida en las
   llamadas.
2. **`FLOAT_LITERAL` se parseaba con `atoi`.** Se detecto en la revisión del
   valor almacenado en `yylval.valor` para literales con `1.5`. Se corrigió a `atof` (`lex.l:57`).
3. **Comentario de bloque sin cerrar.** Al faltar `*/`, la regla
   `"/*"(.|\n)*"*/"` no matchea y el lexer reporta "carácter inesperado" para
   el resto del archivo.
4. **conflictos shift/reduce** pendientes (heredados de la gramática). No
   afectan a los casos de test actuales.
---

## 6. Testing

Se separaron los casos en diferentes grupos. La
suite se encuentra en `tests/` y consta de **18 casos**:

| Grupo | Casos | Qué verifica |
|-------|-------|--------------|
| `ok_*` (7) | `declaraciones_variables`, `metodos`, `llamadas`, `expresiones`, `control_flujo`, `comentarios`, `vacio` | exit 0, `.sint` idéntico al esperado, stdout vacío |
| `scan_*` (1) | `scan_declaracion_tokens` | `-target scan` acepta un programa que luego falla en `parse`; `.lex` esperado |
| `bad_*` (10) | `falta_puntocoma`, `punto_y_coma_extra`, `llave_sin_cerrar`, `llamada_vacia`, `id_numerico`, `declaracion` (`int ;`), `expr_incompleta`, `comas_en_llamada`, `comentario_sin_cerrar`, `caracter_ilegal` | exit != 0, **sin** archivo de salida, stderr con el patrón `.err` esperado |

Resultado: **18/18 aprobados**.