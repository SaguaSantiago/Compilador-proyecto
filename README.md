# Documentación — Proyecto de Taller de Diseño de Software 

Etapa: **1 (análisis léxico y sintáctico)** ·

---

## 1.0. Compilación, ejecución y testing 

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

## 1.1. División del trabajo en la etapa

El trabajo se repartió de la siguiente manera :

- **Lucas Lillo** : correccion de conflictos gramaticales, testing y documentación.
- **Santiago Sagua** : correccion de conflictos gramaticales, gramática base y lexer inicial 
- **Paloma Brizuela** : aportes gramaticales y lexer inicial 

---

## 1.2. Decisiones de diseño

Decisiones tomadas en esta etapa:

En esta etapa se tomaron desiciones base para la construcción del compilador, tales como: 
* Decidir la forma lexica de los `floats`.
* Establecer el comportamiento del signo `-` tanto en su uso como operador binario o como operador unario.
* Corregir conflictos gramaticales en ciertas partes de la gramatica (principalmente conflictos `shift/reduce` de las declaraciones).
* Organizar la gramatica a una versión optima para realizar los futuros avances. 
* Los literales `true` / `false` se modelan como `1` / `0`.

---

## 1.3. Descripción del diseño y decisiones clave

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

## 1.4. Detalles de implementación interesantes

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

## 1.5. Problemas conocidos

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

## 1.6. Testing

Se separaron los casos en diferentes grupos. La
suite se encuentra en `tests/` y consta de **18 casos**:

| Grupo | Casos | Qué verifica |
|-------|-------|--------------|
| `ok_*` (7) | `declaraciones_variables`, `metodos`, `llamadas`, `expresiones`, `control_flujo`, `comentarios`, `vacio` | exit 0, `.sint` idéntico al esperado, stdout vacío |
| `scan_*` (1) | `scan_declaracion_tokens` | `-target scan` acepta un programa que luego falla en `parse`; `.lex` esperado |
| `bad_*` (10) | `falta_puntocoma`, `punto_y_coma_extra`, `llave_sin_cerrar`, `llamada_vacia`, `id_numerico`, `declaracion` (`int ;`), `expr_incompleta`, `comas_en_llamada`, `comentario_sin_cerrar`, `caracter_ilegal` | exit != 0, **sin** archivo de salida, stderr con el patrón `.err` esperado |

Resultado: **18/18 aprobados**.

---

 Etapa: **2.1 (Árbol Sintático y Tabla de Simbolos)** ·

---

## 2.1.1. Division de responsabilidades

- Lillo Lucas: Implementacion de funciones de `TSdef.c` y `ASTdef.c`, creacion de nodos en la gramatica.
- Sagua Santiago: Creacion de nodos en la gramatica, traduccion de la gramatica, implementacion de diversas acciones de la gramatica e implementacion de funciones en `TSdef.c` y `ASTdef.c`.
- Brizuela Paloma: Creacion de nodos en la gramatica y estructuracion del proyecto. 

## 2.1.2. Lista de desiciones de diseño
Para esta etapa hubo que centrar la atencion en el diseño de los siguientes puntos: 
  1. Formato de la TS. 
  2. Tipos implementados: Simbolo, NodoNivel, TablaSimbolos, NodoSimbolo, NodoId y ASTNodo.
  3. Enumerados implementados: TipoNodo, TipoSimbolo y TipoDato.
  4. Construcción del AST. 
  
## 2.1.3. Desiciones tomadas en la etapa

Se decicidio modularizar diversas acciones de construcción para el AST y la TS en metodos declarados en `ASTdef.c` y `TSdef.c`. Por otra parte se decidio estructurar todas las cabeceras en un mismo directorio junto con la creacion de `compilador.h` que importa las demas cabeceras necesarias para `bisson.y`; los archivos `.c` en el directorio `proyecto/src` y los archivos ligados a flex y bisson en el directorio `proyecto/parser`.

A la hora de las declaraciones múltiples de variables, aceptadas por `TDS26`, se optó por la creación de listas de id's para que la regla encargada de armar el nodo declaraciones creara a partir de esta los nodos de las declaraciones por separado.

En cuanto a la estructura de la TS, decidimos diseñarla como un arreglo de listas, siendo la i-esima posicion del arreglo una marca inicial de los simbolos propios del i-esimo nivel de la tabla de simbolos.

Con el objetivo de anticiparnos a ciertos escenarios del analisis semántico, decidimos añadir al tipo simbolo un campo nuevo `nodoBloque` cuyo uso se lo brindará la invocación de métodos, de manera que, el nodo correspondiente a esta sentencia pueda acceder al bloque de ejecución del método; además, se diseñó que el funcionamiento del no terminal `Expresiones` armase una lista de símbolos global (`listaExpresiones`) para que, en un futuro, se pueda analizar su correctitud frente a los parámetros esperados.

## 2.1.4. Detalles de implementación interesantes
No se presentaron algoritmos complejos o poco triviales en esta etapa. 

## 2.1.5. Problemas de producción
En cuanto a diseño no tuvimos problemas especificos, fue una construcción similar a la misma etapa correspondiente al preproyecto, sin embargo los problemas aparecieron en la implementación del diseño donde el problema más común fue la no inicialización de punteros o el mal pasaje de parametros. Se localizaron y resolvieron estos conflictos utilizando logs tanto en `bisson.y` como en `lex.l` para llevar una traza de la ejecución. 

---

 Etapa: **2.2 (Ánalisis Semántico)** ·

---

## 2.2.1. División del trabajo en la etapa

El trabajo se repartió de la siguiente manera :

- **Lucas Lillo** : Reestructuración de la gramática, modularización y función principal `analisisSemantico`. 
- **Santiago Sagua** : Desarrollo de `semantica.c`, función principal `analisisSemantico` y funciones auxiliares. 
- **Paloma Brizuela** : Modularización, función principal `analisisSemantico` y funciones auxiliares. 

---

## 2.2.2. Decisiones de diseño

* Desacoplamiento de la creación de tabla de símbolos y creación del árbol.
* Se movio el enfoque anterior de busqueda de expresiones a traves de la variable global `listaExpresiones` para adaptarlo al analisis semantico.
* Se agrego un nuevo no terminal a la gramatica llamado `Var_declaracion`, esto para arreglar el mal funcionamiento de `Var_declaraciones` ya que antes tenia la forma `Var_declaraciones: Declaracion Var_declaraciones` y ahora es `Var_declaraciones: Var_declaracion Var_declaraciones`.
* Se movieron las adiciones de simbolo a la tabla de `bisson.y` a `semantica.c`.
* Se opto por incorporar la referencia al tipo de retorno en cada nivel de la tabla de simbolos. 

## 2.2.3. Descripción del diseño y decisiones clave

### Arquitectura
El núcleo de esta etapa coinsiste en la creación de `semantica.c`, aqui se concentra el codigo que maneja el analisis semantico del lenguaje. Se basa en un recorrido recursivo por el arbol y un analisis sistematico por cada nodo. Se optó por separar el analisis de simbolos de la creacion, de esta manera los simbolos son creados en `bisson.y` y el chequeo semantico se realiza en `semantica.c`. 
### Alternativas consideradas y justificación
Esta bien remarcar que el analisis se podria haber hecho en la propia gramatica dentro de `bisson.y` y asi no tener que recorrer nuevamente el árbol pero esto hubiera aumentado el acoplamiento y dificultado el manejo del codigo. 

## 2.2.4. Detalles de implementación interesantes
Unos detalles que vale la pena recalcar son, por ejemplo, la incorporacion de los atributos `parametros` en el tipo `Simbolo` y `tipoRetorno` en `NodoNivel`, el primero utilizado para almacenar los tipos de parametros esperados por un metodo y el segundo para guardar el retorno esperado por un nivel (int, void, bool o float).
## 2.2.5. Problemas de producción
Se debieron plantear muchas estructuras para solucionar diversas cuestiones del análisis semántico, para ello se analizaron diferentes alternativas que a continuación detallaremos.

* **Manejo de niveles**: A la hora de decidir como íbamos a manejar los niveles propusimos dos soluciones, una variable global `retornoEsperado` que almacene el tipo esperado o que el nivel de la tabla de simbolos guarde el tipo de retorno esperado, finalmente se optó por la segunda opción ya que nos pareció la mas limpia a la hora de debuggear el código.
* **Guardar parametros de los metodos**: la comparación entre parametros esperados y argumentos pasados requirió reestructurar el código. Para ello se agregó un nuevo atributo en `Simbolo` donde se guardan los parametros esperados por un metodo y, al momento de recorrer la invocación de dicha función, se comparan ordenadamente los parametros guardados en este atributo con los argumentos pasados. 

---

 Etapa: **3 (Código intermedio)** ·

---

## 3.1. División del trabajo en la etapa

El trabajo de esta etapa se repartió de la siguiente manera :

- **Lucas Lillo** : Diseño y estructuración de `CIdef.c` y `codigoIntermedio.c`. 
- **Santiago Sagua** : Pruebas y correcciones de diseño de análisis semántico y gramática, limpieza y reestructuración de `main.c`, contribuciones en el metodo `construirCodigoIntermedio` de `codigoIntermedio.c`. 
- **Paloma Brizuela** : Correcciones del análisis semántico, implementación de la jerarquía de operadores y debugging del código intermedio.

---

## 3.2. Decisiones de diseño
En esta etapa las desiciones de diseño se centraron en como iba a estar compuesta la arquitectura del código intermedio que, a diferencia del preproyecto, utiliza una lista de instrucciones en lugar de una salida en formato de texto. En principio estas instrucciones estaban conformadas por campos de tipo `String`, pero se decidio cambiar su tipo por `Simbolo` para que de esta manera podamos guardar tipos pensando en la futura implementación del constructor de assembly. 

## 2.2.3. Descripción del diseño y decisiones clave

### Cambios en etapa de parsing
Se encontró una inconsistencia en el momento en que se analiza semánticamente la invocación de una función (y el uso de una variable ya declarada) y su declaración:
* Cuando el analizador semántico analizaba el nodo que representa la invocación de una función, buscaba el símbolo creado en su declaración y lo guardaba como propio (en su campo simbolo). La inconsistencia se genera en este nodo, pues, se espera que el tipo de su simbolo sea un método y no una declaración de un método. (analizar el enumerado TipoSimbolo).
* De manera análoga, se generaba la misma inconsistencia con la declaración de variables y su uso. En el momento en el que el analizador se encontraba con un nodo identificador, al igual que con las invocaciones de funciones, buscaba el simbolo declarado anteriormente y asignaba una referencia al mismo. Allí se generaba otra inconsistencia: el nodo Identificador (la variable) tendría referencia a un símbolo con tipo declaración, generando dificultades a la hora del código intermedio.

> Como solución se estableció que en la etapa de analisis semántico los nodos identificadores tengan referencia a símbolos de tipo Var_local, Var_global o metodo al igual que sus declaraciones, de manera que, las declaraciones y el uso de una variable o metodo sean tratadas de manera uniforme.
>> Notamos también que este cambio nos facilitó la diferenciación del tipo de variable en la etapa de generación de assembly (local o global) 

### Arquitectura
La arquitectura del constructor de código intermedio se divide en dos archivos claves: `CIdef.c` y `codigoIntermedio.c`. 

El primero tiene como objetivo brindar los metodos necesarios para construir y manipular el código, ademas de contener al mismo. La estructura de este código coinsiste en una lista de instrucciones, estas instrucciones son estructuras de datos con 5 campos:
* Op op
* Simbolo *arg1
* Simbolo *arg2
* Simbolo *resultado
* char *label
Notese que la estructura está basada en un sistema de cuadruplos adicionando el campo `label`, este campo es utilizado cuando la instrucción necesita hacer referencia o almacenar ciertas cadenas como por ejemplo en el mismisimo operador `LABEL`. El primer campo de tipo `Op` hace referencia a un tipo enumerado que contiene todas las operaciones permitidas por nuestro código intermedio. 
`CIdef.c` también brinda métodos para crear nuevos temporales y labels.

Por otro lado las tareas de `codigoIntermedio.c` se centran en recorrer el AST y construir el código intermedio a traves de los metodos brindados por `CIdef.c`. 
Esto se logra gracias a dos metodos esenciales:
* `construirCodigoIntermedio`: esta función recorre los nodos recursivamente generando las instrucciones necesarias en el proceso y llamando a `generarExpresion` cuando sea necesario. 
* `generarExpresion`: este metodo se utiliza para procesar aquellos nodos que devuelven un valor ya sea constante o temporal (llamadas a metodos, variables, operadores, etc), su comportamiento se basa en recorrer los nodos que sean necesarios para construir el simbolo final a devolver y generar instrucciones en su recorrido. 

### Alternativas consideradas y justificación
Como se mencionó anteriormente la primera versión utilizaba Strings en lugar de Simbolos para los campos de las instrucciones, esta forma fue descartada por la perdida de información existente en la transición del analisis semantico hacia el generador de assembly. También se consideró agrupar el recorrido del árbol en un solo metodo pero esto ensuciaba el código y traia conflictos a la hora de desarrollar. 

## 2.2.4. Detalles de implementación interesantes
Un detalle ya mencionado es la adición del campo label a `Instruccion` para poder almacenar cadenas de texto. También vale la pena mencionar algunos operadores implementados para facilitar la traducción a assembly como:
* `VAR_GLOBAL` y `VAR_LOCAL`: distinguimos la declaración de variables globales y locales puesto a que requeriran diferentes tratamientos en la etapa de generación de assembly. 
* `FIN_METODO`: previendo las acciones que se deben ejecutar en bajo nivel a la hora de salir de un "método" decidimos diferenciar esta operación y emitirla a la salida de un método. 
* `PUSH`: a la hora de llamar a un metodo en assembly se deben guardar el valor de los argumentos en registros, teniendo en cuenta esto, decidimos anticipar este comportamiento y simularlo en código intermedio a traves del operador PUSH. 
