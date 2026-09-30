CC := gcc
BISON := bison
FLEX := flex

CFLAGS := -Wall -Wextra -g -Iinclude -Iparser
TARGET := c-tds

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
RM := -del /Q 2>NUL
RUN := $(TARGET).exe
# 'del' de cmd.exe no parsea bien las rutas con '/' dentro de un
# subdirectorio ("del src/main.o" -> "modificador no valido"), asi que
# para borrar se pasan con '\'.
WINPATH = $(subst /,\,$(1))
else
SHELL := /bin/sh
RM := rm -f
RUN := ./$(TARGET)
WINPATH = $(1)
endif

HEADERS := include/enums.h include/tipos.h include/compilador.h \
           include/ASTdef.h include/TSdef.h

SOURCES := src/main.c src/astdef.c src/TSdef.c \
           parser/bisson.tab.c parser/lex.yy.c
OBJECTS := $(SOURCES:.c=.o)

# .o sueltos que quedaron en la raiz de una compilacion en otra carpeta
STALE := main.o lex.yy.o bisson.tab.o

.PHONY: all gen run test clean distclean rebuild

all: gen $(TARGET)

# Genera bisson.tab.c, bisson.tab.h y lex.yy.c
# dentro de la carpeta parser. Los archivos se entregan trackeados, asi que
# solo se regeneran si cambian bisson.y, lex.l o un header de la gramatica:
# el build no exige tener bison/flex instalados.
gen: parser/bisson.tab.c parser/lex.yy.c

# bison -d genera el .c y el .h juntos, asi que basta con una sola regla para
# el .c. La del .h no lleva receta: es la que evita que make lance bison dos
# veces cuando ambos estan vencidos.
parser/bisson.tab.c: parser/bisson.y include/enums.h
	cd parser && $(BISON) -d bisson.y

parser/bisson.tab.h: parser/bisson.tab.c

parser/lex.yy.c: parser/lex.l parser/bisson.tab.h
	cd parser && $(FLEX) lex.l

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

src/astdef.o: src/astdef.c include/ASTdef.h include/enums.h include/tipos.h
	$(CC) $(CFLAGS) -c $< -o $@

src/TSdef.o: src/TSdef.c include/TSdef.h include/ASTdef.h include/enums.h include/tipos.h
	$(CC) $(CFLAGS) -c $< -o $@

parser/bisson.tab.o: parser/bisson.tab.c parser/bisson.tab.h $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

parser/lex.yy.o: parser/lex.yy.c parser/bisson.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(RUN) pruebas/ejemplo.ctds

test: $(TARGET)
	./tests/run_tests.sh

# Borra binarios y objetos, pero conserva los generados por bison/flex:
# estan trackeados a proposito para que el proyecto compile con solo gcc.
clean:
	$(RM) $(TARGET) $(TARGET).exe $(call WINPATH,$(OBJECTS)) $(call WINPATH,$(STALE))

# clean + borra tambien los generados por bison/flex (deja el proyecto como
# estaba antes de 'make gen' en un clon nuevo).
distclean: clean
	$(RM) $(call WINPATH,parser/bisson.tab.c) $(call WINPATH,parser/bisson.tab.h) $(call WINPATH,parser/lex.yy.c)

rebuild: clean all
