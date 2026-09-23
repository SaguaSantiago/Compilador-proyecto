CC := gcc
BISON := bison
FLEX := flex

CFLAGS := -Wall -Wextra -g
TARGET := c-tds

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
RM := -del /Q
else
SHELL := /bin/sh
RM := rm -f
endif

SOURCES := main.c bisson.tab.c lex.yy.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all gen run test clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Regenera los archivos generados por bison/flex. Solo necesario si se
# modifica bisson.y o lex.l; para compilar el proyecto alcanza con gcc
# porque bisson.tab.c y lex.yy.c ya estan incluidos.
gen:
	$(BISON) -d bisson.y
	$(FLEX) lex.l

main.o: main.c
bisson.tab.o: bisson.tab.c enums.h bisson.tab.h
lex.yy.o: lex.yy.c bisson.tab.h

run: $(TARGET)
	./$(TARGET) pruebas/ejemplo.ctds

test: $(TARGET)
	./tests/run_tests.sh

clean:
	$(RM) $(TARGET) $(TARGET).exe $(OBJECTS)

rebuild: clean all