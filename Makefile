CC := gcc
BISON := bison
FLEX := flex

CFLAGS := -Wall -Wextra -g -Iinclude -Iparser
TARGET := c-tds

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
RM := -del /Q
else
SHELL := /bin/sh
RM := rm -f
endif

SOURCES := src/main.c parser/bisson.tab.c parser/lex.yy.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all gen run test clean rebuild

all: gen $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Genera bisson.tab.c, bisson.tab.h y lex.yy.c
# dentro de la carpeta parser
gen:
	cd parser && $(BISON) -d bisson.y
	cd parser && $(FLEX) lex.l

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

parser/bisson.tab.o: parser/bisson.tab.c parser/bisson.tab.h include/enums.h include/ASTdef.h
	$(CC) $(CFLAGS) -c $< -o $@

parser/lex.yy.o: parser/lex.yy.c parser/bisson.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) pruebas/ejemplo.ctds

test: $(TARGET)
	./tests/run_tests.sh

clean:
	$(RM) $(TARGET) $(TARGET).exe $(OBJECTS)
	$(RM) parser/bisson.tab.c parser/bisson.tab.h parser/lex.yy.c

rebuild: clean all
