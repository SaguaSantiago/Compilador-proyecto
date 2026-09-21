/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BISSON_TAB_H_INCLUDED
# define YY_YY_BISSON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "bisson.y"

  #include "enums.h"

#line 53 "bisson.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MAIN = 258,                    /* MAIN  */
    BOOLEAN = 259,                 /* BOOLEAN  */
    VOID = 260,                    /* VOID  */
    RETURN = 261,                  /* RETURN  */
    SUMA = 262,                    /* SUMA  */
    MULTIPLICACION = 263,          /* MULTIPLICACION  */
    ASIGNACION = 264,              /* ASIGNACION  */
    INT = 265,                     /* INT  */
    FLOAT = 266,                   /* FLOAT  */
    PARENTESIS_IZQ = 267,          /* PARENTESIS_IZQ  */
    PARENTESIS_DER = 268,          /* PARENTESIS_DER  */
    LLAVE_IZQ = 269,               /* LLAVE_IZQ  */
    LLAVE_DER = 270,               /* LLAVE_DER  */
    PUNTO_COMA = 271,              /* PUNTO_COMA  */
    COMA = 272,                    /* COMA  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    AND = 276,                     /* AND  */
    OR = 277,                      /* OR  */
    NOT = 278,                     /* NOT  */
    MAYOR = 279,                   /* MAYOR  */
    MENOR = 280,                   /* MENOR  */
    IGUALDAD = 281,                /* IGUALDAD  */
    MOD = 282,                     /* MOD  */
    RESTA = 283,                   /* RESTA  */
    DIV = 284,                     /* DIV  */
    INT_LITERAL = 285,             /* INT_LITERAL  */
    FLOAT_LITERAL = 286,           /* FLOAT_LITERAL  */
    TRUE = 287,                    /* TRUE  */
    FALSE = 288,                   /* FALSE  */
    Id = 289                       /* Id  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "bisson.y"

  ASTNodo nodo;
  float valor; // Los tipo INT seran tratados como FLOAT internamente.
  char* nombre;

#line 110 "bisson.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BISSON_TAB_H_INCLUDED  */
