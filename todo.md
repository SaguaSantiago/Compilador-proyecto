# TODO

Errores pendientes, agrupados por archivo. Todos fueron detectados al compilar
el proyecto; ninguno viene de la separacion de headers que ya se hizo.

Estado actual: los headers ya no se incluyen de forma recursiva (ver
`include/tipos.h` y `include/compilador.h`), pero **`make` no llega a compilar**
por los puntos 1 a 3.

---

## 1. Makefile / build

- `Makefile:16` — `SOURCES` no incluye `src/astdef.c` ni `src/TSdef.c`. Ninguna
  de las funciones que el parser usa (`crearSimbolo`, `agregarSimbolo`,
  `buscarSimbolo`, `agregarSimboloALista`) llega al ejecutable, y
  `crearASTNodo` tampoco: van a fallar como *undefined reference* al linkear.
- `Makefile:16` — tampoco se compila `src/main.c` con las deps de `include/`.
  Agregar las deps de `include/tipos.h`, `include/compilador.h`.
- `Makefile:35` — la regla de `parser/bisson.tab.o` lista `include/ASTdef.h`
  pero no `include/TSdef.h` ni `include/tipos.h`.
- `Makefile:6` — `TARGET := c-tds`, pero en la raiz hay un ejecutable viejo
  llamado `compilador`. Definir cual es el nombre bueno y borrar el otro.
- Raiz — hay `.o` sueltos (`main.o`, `lex.yy.o`, `bisson.tab.o`) de una
  compilacion en otra carpeta. Estan ignorados por `.gitignore`; borrarlos.

## 2. Bloquea a bison: errores de la gramatica

`make gen` falla aca, asi que los archivos generados quedaron desincronizados
con `bisson.y`. Hay que correr `make gen` recien arreglado esto.

- `parser/bisson.y:98` — `simbolo->tipoDato = $1;` en la alternativa
  `VOID Id ...`: `$1` es el token `VOID`, que no tiene tipo declarado.
  `simbolo->tipoDato` deberia recibir `TIPO_VOID` o similar.
- `parser/bisson.y:88` — falta `Tipo_dato` / `VOID` como tipo de retorno real en
  `TipoDato` (`include/enums.h:7` solo tiene INTEGER, FLOAT, BOOLEAN).

## 3. Headers incompletos

- `include/TSdef.h:44` — `agregarSimboloALista(Simbolo*, NodoSimbolo*)` recibe la
  lista **por valor**: el `lista = nuevoNodo` de `src/TSdef.c:80` se pierde al
  salir de la funcion. La lista nunca crece. Deberia ser `NodoSimbolo**`.
- `include/TSdef.h` — `buscarSimbolo` y `crearSimbolo` se usan en `bisson.y`
  pero no estan declaradas. Actualmente son implicitas.
- `include/TSdef.h:27` — `agregarSimbolo` declarada `void`, pero
  `src/TSdef.c:13` y `:24` hacen `return 0` / `return 1`. Devuelve `int`.
- `include/TSdef.h:29` — `inicializarTs` declarada `void`, pero
  `src/TSdef.c:38` hace `return ts`. Devuelve `TablaSimbolo*`.
- `include/ASTdef.h:60` — declara `crearASTNodo`, pero `src/astdef.c:5` define
  `crearNodo`. Ademas no hay prototipo en el .c.
- `src/TSdef.c` — falta `#include <string.h>` (`strcmp` en `:12` y `:63`).
- `parser/bisson.y:105`, `:112` — `strcpy($1)` con un solo argumento; deberia
  ser `strdup($1)`. Tambien falta `<string.h>` en el prologo.

## 4. Nombres desincronizados en bisson.y

`bisson.y` sigue usando los nombres anteriores al renombre de `enums.h` y de
`struct Simbolo`.

- Tipo del struct del AST:
  - `bisson.y:177` — `Nodo* hojaId`; el tipo se llama `ASTNodo`.
  - `bisson.y:134`, `:140` — `ASTNodo nodo = crearASTNodo(...)` asigna un
    puntero a un struct por valor. Deberia ser `ASTNodo *nodo`.
- Lista de nombres:
  - `bisson.y:58`, `:104`, `:111` — `NodoId` / `nombres->id`; el struct es
    `struct Nodo_Id` y el campo es `Id` (`ASTdef.h:51-54`).
- Campo del tipo de dato:
  - `bisson.y:171`, `:236`, `:248`, `:254`, `:314`, `:322`, `:332`, `:340`,
    `:348`, `:359`, `:369`, `:379`, `:388` — `simbolo->tipo`. El campo que
    existe es `tipoDato` (`TSdef.h:11`). `tipo` es `TipoNodo` y es de `ASTNodo`.
- `TipoDato` viejos que ya no existen en `enums.h:7`:
  - `bisson.y:236`, `:359` — `TIPO_INT` -> `TIPO_INTEGER`.
  - `bisson.y:314`, `:322`, `:332`, `:340`, `:348` — `TIPO_AND`, `TIPO_OR`,
    `TIPO_IGUALDAD`, `TIPO_MENOR`, `TIPO_MAYOR`. No existen: son operadores, no
    tipos de dato.
- `TipoSimbolo` viejos que ya no existen en `enums.h:9-36`:
  - `bisson.y:315`, `:323`, `:333`, `:341`, `:349` — `AND_SIM`, `OR_SIM`,
    `IGUALDAD_SIM`, `MENOR_SIM`, `MAYOR_SIM`.
  - `bisson.y:360`, `:370`, `:380`, `:389` — `INT_SIM`, `FLOAT_SIM`,
    `BOOLEAN_SIM`. Los nombres actuales son `SIMBOLO_INTEGER_LITERAL`,
    `SIMBOLO_FLOAT_LITERAL`, `SIMBOLO_TRUE_LITERAL` / `SIMBOLO_FALSE_LITERAL`.
- Tokens de `TipoNodo` que no existen (`ASTdef.h:5-36`):
  - `bisson.y:136`, `:141` — `NODO_PARAM_DECL`. No esta en el enum.
  - `bisson.y:194`, `:195` — `NODO_RETURN`. El nombre real es `NODO_RETORNO`.
- Variables sin declarar en `bisson.y`:
  - `ts` (`bisson.y:68`, `:86`, `:97`) y `tablaSimbolos` (`:166`, `:218`,
    `:242`, `:256`, `:278`, `:286`, `:294`, `:302`, `:316`, `:324`, `:334`,
    `:342`, `:350`, `:362`, `:372`, `:382`, `:390`) no existen. Ademas no se
    instancia ninguna `TablaSimbolo` en ningun lado: falta crearla e
    inicializarla con `inicializarTs`.

## 5. Bugs de logica

- `src/TSdef.c:6`, `:21`, `:59` — indexan `ts->niveles[nivelActual]` asumiendo
  un array, pero `niveles` es `NodoNivel *` y `NodoNivel` es una lista enlazada
  (`struct Nivel { Simbolo *sim; struct Nivel *sig; }`). El diseno de niveles
  esta roto: falta un tipo `Nivel` con `Simbolo **simbolos; struct Nivel *sig;`.
- `src/TSdef.c:41-51` — `agregarNivel` incrementa `nivelActual` **antes** de
  indexar (desborra la primera vez) y guarda `nuevoNodo` en una variable local
  en vez de en la ranura del nivel.
- `src/TSdef.c:28` — `inicializarTs` reasigna el puntero local `ts`; la tabla del
  llamador queda sin inicializar. Deberia inicializar `*ts` o recibir
  `TablaSimbolo**`.
- `src/TSdef.c:71` — `free(nodoActual)` cuando `nodoActual` ya es `NULL`.
- `src/TSdef.c:83` — `crearSimbolo()` no inicializa `tipoSimbolo`, `tipoDato` ni
  `nodoBloque`. El llamador los setea a veces y no siempre.
- `bisson.y:175`, `:243`, `:257` — la accion semantica hace const folding
  (`idEncontrado->valor = ...`), lo que evalua en tiempo de parseo y descarta
  el arbol. Deberia emitir un nodo operador.
- `bisson.y:171` — compara `idEncontrado->tipo` con `$3->simbolo->tipo`: son
  cosas distintas (tipo de simbolo vs tipo de dato). Ademas ambos campos
  equivocados (ver punto 4).
- `bisson.y:237`, `:249` — `fprintf(stderr, "... '%s' ...", $2)` con `$2` siendo
  un `ASTNodo *`, no una cadena.
- `bisson.y:75` — `free(aux)` libera un nodo que sigue enlazado desde
  `aux->izq`: use-after-free.
- `bisson.y:200-204` — se leen `listaExpresiones` y `$3`, pero `$3` es el
  resultado de la regla, no la lista de argumentos. Los argumentos nunca llegan
  al nodo de invocacion.
- `bisson.y:209` — `agregarSimboloALista($1->simbolo, ...)` manda el simbolo de
  un nodo, no el simbolo del argumento.