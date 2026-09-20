CC := gcc
BISON := bison
FLEX := flex

CFLAGS := -Wall -Wextra -g
TARGET := compilador

SOURCES := main.c bisson.tab.c lex.yy.c 
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

bisson.tab.c bisson.tab.h: bisson.y enums.h
	$(BISON) -d bisson.y

lex.yy.c: lex.l bisson.tab.h
	$(FLEX) lex.l

main.o: main.c
bisson.tab.o: bisson.tab.c enums.h
lex.yy.o: lex.yy.c bisson.tab.h

run: $(TARGET)
	./$(TARGET) < input.txt

clean:
	$(RM) $(TARGET) $(OBJECTS)

rebuild: clean all