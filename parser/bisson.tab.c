/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "bisson.y"
 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "compilador.h"
    extern int yylineno;

    int yylex(void);
    void yyerror(const char *s);
    ASTNodo *raiz;
    TablaSimbolos *tablaSimbolos;

    NodoSimbolo *listaExpresiones = NULL;

#line 86 "bisson.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bisson.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MAIN = 3,                       /* MAIN  */
  YYSYMBOL_BOOLEAN = 4,                    /* BOOLEAN  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_SUMA = 7,                       /* SUMA  */
  YYSYMBOL_MULTIPLICACION = 8,             /* MULTIPLICACION  */
  YYSYMBOL_ASIGNACION = 9,                 /* ASIGNACION  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_PARENTESIS_IZQ = 12,            /* PARENTESIS_IZQ  */
  YYSYMBOL_PARENTESIS_DER = 13,            /* PARENTESIS_DER  */
  YYSYMBOL_LLAVE_IZQ = 14,                 /* LLAVE_IZQ  */
  YYSYMBOL_LLAVE_DER = 15,                 /* LLAVE_DER  */
  YYSYMBOL_PUNTO_COMA = 16,                /* PUNTO_COMA  */
  YYSYMBOL_COMA = 17,                      /* COMA  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_MAYOR = 24,                     /* MAYOR  */
  YYSYMBOL_MENOR = 25,                     /* MENOR  */
  YYSYMBOL_IGUALDAD = 26,                  /* IGUALDAD  */
  YYSYMBOL_MOD = 27,                       /* MOD  */
  YYSYMBOL_RESTA = 28,                     /* RESTA  */
  YYSYMBOL_DIV = 29,                       /* DIV  */
  YYSYMBOL_FLOAT_LITERAL = 30,             /* FLOAT_LITERAL  */
  YYSYMBOL_INT_LITERAL = 31,               /* INT_LITERAL  */
  YYSYMBOL_TRUE = 32,                      /* TRUE  */
  YYSYMBOL_FALSE = 33,                     /* FALSE  */
  YYSYMBOL_Id = 34,                        /* Id  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_Program = 36,                   /* Program  */
  YYSYMBOL_Declaraciones = 37,             /* Declaraciones  */
  YYSYMBOL_Declaracion = 38,               /* Declaracion  */
  YYSYMBOL_Id_list = 39,                   /* Id_list  */
  YYSYMBOL_Tipo_dato = 40,                 /* Tipo_dato  */
  YYSYMBOL_Params_decl = 41,               /* Params_decl  */
  YYSYMBOL_Var_declaraciones = 42,         /* Var_declaraciones  */
  YYSYMBOL_Bloque = 43,                    /* Bloque  */
  YYSYMBOL_Sentencias_list = 44,           /* Sentencias_list  */
  YYSYMBOL_Sentencia = 45,                 /* Sentencia  */
  YYSYMBOL_Metodo_invocacion = 46,         /* Metodo_invocacion  */
  YYSYMBOL_Expresiones = 47,               /* Expresiones  */
  YYSYMBOL_Expr = 48,                      /* Expr  */
  YYSYMBOL_Op_binario = 49,                /* Op_binario  */
  YYSYMBOL_Op_arit = 50,                   /* Op_arit  */
  YYSYMBOL_Op_cond = 51,                   /* Op_cond  */
  YYSYMBOL_Op_rel = 52,                    /* Op_rel  */
  YYSYMBOL_Literal = 53                    /* Literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   204

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  93

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    55,    60,    63,    86,    97,   110,   117,
     126,   130,   134,   140,   146,   151,   154,   158,   161,   166,
     167,   170,   179,   181,   185,   189,   190,   191,   194,   204,
     208,   213,   219,   220,   221,   228,   240,   254,   260,   262,
     264,   268,   275,   282,   289,   296,   306,   314,   324,   332,
     340,   350,   360,   370,   380
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "MAIN", "BOOLEAN", "VOID",
  "RETURN", "SUMA", "MULTIPLICACION", "ASIGNACION", "INT", "FLOAT",
  "PARENTESIS_IZQ", "PARENTESIS_DER", "LLAVE_IZQ", "LLAVE_DER",
  "PUNTO_COMA", "COMA", "IF", "ELSE", "WHILE", "AND", "OR", "NOT", "MAYOR",
  "MENOR", "IGUALDAD", "MOD", "RESTA", "DIV", "FLOAT_LITERAL",
  "INT_LITERAL", "TRUE", "FALSE", "Id", "$accept", "Program",
  "Declaraciones", "Declaracion", "Id_list", "Tipo_dato", "Params_decl",
  "Var_declaraciones", "Bloque", "Sentencias_list", "Sentencia",
  "Metodo_invocacion", "Expresiones", "Expr", "Op_binario", "Op_arit",
  "Op_cond", "Op_rel", "Literal", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      40,   -34,   -27,   -34,   -34,    19,   -34,    40,    -9,    30,
     -34,   -34,    -6,    31,    17,    17,    14,   -34,    18,    42,
      43,    44,   -34,    45,    49,    49,    17,    40,   -34,   -34,
     -34,    40,    -4,   -34,   158,    47,   170,    34,    50,    -4,
      41,   170,   -34,   170,   170,   -34,   -34,   -34,   -34,    52,
     -34,    10,   -34,   170,    74,   170,   170,   -34,   -34,   -34,
      84,   140,   140,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   170,   -34,   -34,   -34,   107,   -34,
     130,    70,    46,   -34,   140,    49,   -34,   -34,   170,   -34,
      65,    49,   -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    12,     0,    10,    11,     0,     2,     4,     0,     0,
       1,     3,     9,     0,    15,    15,     0,     5,     0,     0,
       0,     9,     8,    14,     0,     0,    15,    17,     7,     6,
      13,    17,    20,    16,     0,     0,     0,     0,     0,    20,
       0,     0,    27,     0,     0,    52,    51,    54,    53,    31,
      32,     0,    33,     0,     0,     0,     0,    18,    19,    22,
       0,    36,    35,    41,    42,    26,    46,    47,    50,    49,
      48,    45,    43,    44,     0,    38,    40,    39,     0,    25,
       0,     0,    30,    37,    34,     0,    21,    28,     0,    29,
      23,     0,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,    78,   -22,    71,    -2,   -11,    55,   -25,    51,
     -34,     1,     7,   -33,   -34,   -34,   -34,   -34,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,    13,     8,    19,    32,    28,    38,
      39,    50,    81,    62,    74,    75,    76,    77,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    51,    34,    54,    20,    31,    15,     9,    60,    31,
      61,    16,    18,    18,    35,    30,    36,    63,    64,    10,
      78,     1,    80,    82,    18,    12,    65,     3,     4,    79,
      37,    66,    67,    40,    68,    69,    70,    71,    72,    73,
      40,    84,    14,    55,     1,     2,    56,    17,    21,    82,
       3,     4,    23,    63,    64,    24,    25,    59,    41,    53,
      90,    16,    26,    27,    56,    57,    92,    66,    67,    43,
      68,    69,    70,    71,    88,    73,    45,    46,    47,    48,
      49,    63,    64,    87,    91,    11,    33,    22,    27,    89,
      58,    63,    64,     0,     0,    66,    67,    83,    68,    69,
      70,    71,    72,    73,     0,    66,    67,     0,    68,    69,
      70,    71,    72,    73,    63,    64,     0,     0,     0,     0,
      85,     0,     0,     0,     0,     0,     0,     0,    66,    67,
       0,    68,    69,    70,    71,    72,    73,    63,    64,     0,
       0,     0,     0,     0,     0,     0,    86,    63,    64,     0,
       0,    66,    67,     0,    68,    69,    70,    71,    72,    73,
       0,    66,    67,     0,    68,    69,    70,    71,    72,    73,
      41,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    43,    41,     0,     0,     0,    44,     0,    45,    46,
      47,    48,    49,    43,     0,     0,     0,     0,    44,     0,
      45,    46,    47,    48,    49
};

static const yytype_int8 yycheck[] =
{
      25,    34,     6,    36,    15,    27,    12,    34,    41,    31,
      43,    17,    14,    15,    18,    26,    20,     7,     8,     0,
      53,     4,    55,    56,    26,    34,    16,    10,    11,    54,
      34,    21,    22,    32,    24,    25,    26,    27,    28,    29,
      39,    74,    12,     9,     4,     5,    12,    16,    34,    82,
      10,    11,    34,     7,     8,    13,    13,    16,    12,    12,
      85,    17,    17,    14,    12,    15,    91,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     7,     8,    13,    19,     7,    31,    16,    14,    82,
      39,     7,     8,    -1,    -1,    21,    22,    13,    24,    25,
      26,    27,    28,    29,    -1,    21,    22,    -1,    24,    25,
      26,    27,    28,    29,     7,     8,    -1,    -1,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,
      -1,    24,    25,    26,    27,    28,    29,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,     7,     8,    -1,
      -1,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      -1,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      12,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    12,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    34,    23,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,    10,    11,    36,    37,    38,    40,    34,
       0,    37,    34,    39,    12,    12,    17,    16,    40,    41,
      41,    34,    39,    34,    13,    13,    17,    14,    43,    43,
      41,    38,    42,    42,     6,    18,    20,    34,    44,    45,
      46,    12,    16,    23,    28,    30,    31,    32,    33,    34,
      46,    48,    53,    12,    48,     9,    12,    15,    44,    16,
      48,    48,    48,     7,     8,    16,    21,    22,    24,    25,
      26,    27,    28,    29,    49,    50,    51,    52,    48,    43,
      48,    47,    48,    13,    48,    13,    16,    13,    28,    47,
      43,    19,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    39,    39,
      40,    40,    40,    41,    41,    41,    42,    42,    43,    44,
      44,    45,    45,    45,    45,    45,    45,    45,    46,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      49,    50,    50,    50,    50,    50,    51,    51,    52,    52,
      52,    53,    53,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     6,     6,     3,     1,
       1,     1,     1,     4,     2,     0,     2,     0,     4,     2,
       0,     4,     2,     5,     7,     3,     3,     2,     4,     2,
       1,     1,     1,     1,     3,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */


/* User initialization code.  */
#line 43 "bisson.y"
{
  inicializarTs(&tablaSimbolos);
}

#line 1231 "bisson.tab.c"

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Declaraciones  */
#line 50 "bisson.y"
       {
        raiz = crearASTNodo(NODO_ROOT, NULL, (yyvsp[0].nodo), NULL);
       }
#line 1436 "bisson.tab.c"
    break;

  case 3: /* Declaraciones: Declaracion Declaraciones  */
#line 56 "bisson.y"
              {
                // fprintf(stderr, "llegue a declaraciones \n");
                (yyval.nodo) = crearASTNodo(NODO_DECLS, NULL, (yyvsp[-1].nodo), (yyvsp[0].nodo));
              }
#line 1445 "bisson.tab.c"
    break;

  case 4: /* Declaraciones: %empty  */
#line 60 "bisson.y"
                       {(yyval.nodo) = NULL;}
#line 1451 "bisson.tab.c"
    break;

  case 5: /* Declaracion: Tipo_dato Id_list PUNTO_COMA  */
#line 64 "bisson.y"
           {
             TipoDato tipo = (yyvsp[-2].tipo_dato);
            NodoId* nombres = (yyvsp[-1].lista_nombres);
            ASTNodo* decl_raiz = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            ASTNodo* aux = decl_raiz;

            while(nombres != NULL){
              Simbolo* simbolo = crearSimbolo();
              simbolo->tipoSimbolo = SIMBOLO_VAR_DECL;
              simbolo->tipoDato = tipo;
              simbolo->nombre = strdup(nombres->id);
              
              agregarSimbolo(simbolo, tablaSimbolos);
              // fprintf(stderr, "llegue a declaracion \n");

              ASTNodo* nuevoNodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
              aux->izq = nuevoNodo;
              aux = nuevoNodo;
              nombres = nombres->sig;
            }
            (yyval.nodo) = decl_raiz;
           }
#line 1478 "bisson.tab.c"
    break;

  case 6: /* Declaracion: Tipo_dato Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque  */
#line 87 "bisson.y"
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = TIPO_VOID;
            simbolo->nombre = strdup((yyvsp[-4].nombre));
            simbolo->nodoBloque = (yyvsp[0].nodo);
            
            agregarSimbolo(simbolo, tablaSimbolos);
            (yyval.nodo) = crearASTNodo(NODO_DECL_MET, simbolo, (yyvsp[-2].nodo), NULL);
           }
#line 1493 "bisson.tab.c"
    break;

  case 7: /* Declaracion: VOID Id PARENTESIS_IZQ Params_decl PARENTESIS_DER Bloque  */
#line 98 "bisson.y"
           {
            Simbolo* simbolo = crearSimbolo();
            simbolo->tipoSimbolo = SIMBOLO_MET_DECL;
            simbolo->tipoDato = TIPO_VOID;
            simbolo->nombre = strdup((yyvsp[-4].nombre));
            simbolo->nodoBloque = (yyvsp[0].nodo);

            agregarSimbolo(simbolo, tablaSimbolos);
            (yyval.nodo) = crearASTNodo(NODO_DECL_MET, simbolo, (yyvsp[-2].nodo), NULL);
           }
#line 1508 "bisson.tab.c"
    break;

  case 8: /* Id_list: Id COMA Id_list  */
#line 111 "bisson.y"
       {
         NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
         nodo_nombre->id = strdup((yyvsp[-2].nombre));
         nodo_nombre->sig = (yyvsp[0].lista_nombres);
         (yyval.lista_nombres) = nodo_nombre;
       }
#line 1519 "bisson.tab.c"
    break;

  case 9: /* Id_list: Id  */
#line 118 "bisson.y"
        {
          NodoId* nodo_nombre = (NodoId*) malloc(sizeof(NodoId));
          nodo_nombre->id = strdup((yyvsp[0].nombre));
          nodo_nombre->sig = NULL;
          (yyval.lista_nombres) = nodo_nombre;
        }
#line 1530 "bisson.tab.c"
    break;

  case 10: /* Tipo_dato: INT  */
#line 127 "bisson.y"
          {
            (yyval.tipo_dato) = TIPO_INTEGER;
          }
#line 1538 "bisson.tab.c"
    break;

  case 11: /* Tipo_dato: FLOAT  */
#line 131 "bisson.y"
          {
            (yyval.tipo_dato) = TIPO_FLOAT;
          }
#line 1546 "bisson.tab.c"
    break;

  case 12: /* Tipo_dato: BOOLEAN  */
#line 135 "bisson.y"
          {
            (yyval.tipo_dato) = TIPO_BOOLEAN;
          }
#line 1554 "bisson.tab.c"
    break;

  case 13: /* Params_decl: Tipo_dato Id COMA Params_decl  */
#line 141 "bisson.y"
           {
            ASTNodo *nodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            
            (yyval.nodo) = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, (yyvsp[0].nodo));
           }
#line 1564 "bisson.tab.c"
    break;

  case 14: /* Params_decl: Tipo_dato Id  */
#line 147 "bisson.y"
           {
            ASTNodo *nodo = crearASTNodo(NODO_DECL_VAR, NULL, NULL, NULL);
            (yyval.nodo) = crearASTNodo(NODO_PARAM_DECL, NULL, nodo, NULL);
           }
#line 1573 "bisson.tab.c"
    break;

  case 15: /* Params_decl: %empty  */
#line 151 "bisson.y"
                    {(yyval.nodo) = NULL;}
#line 1579 "bisson.tab.c"
    break;

  case 16: /* Var_declaraciones: Declaracion Var_declaraciones  */
#line 155 "bisson.y"
      {
          (yyval.nodo) = crearASTNodo(NODO_DECLS, NULL, (yyvsp[-1].nodo), (yyvsp[0].nodo));
      }
#line 1587 "bisson.tab.c"
    break;

  case 17: /* Var_declaraciones: %empty  */
#line 158 "bisson.y"
               {(yyval.nodo) = NULL;}
#line 1593 "bisson.tab.c"
    break;

  case 18: /* Bloque: LLAVE_IZQ Var_declaraciones Sentencias_list LLAVE_DER  */
#line 161 "bisson.y"
                                                             {
  (yyval.nodo) = crearASTNodo(NODO_BLOQUE,NULL,(yyvsp[-2].nodo),(yyvsp[-1].nodo));
}
#line 1601 "bisson.tab.c"
    break;

  case 19: /* Sentencias_list: Sentencia Sentencias_list  */
#line 166 "bisson.y"
                                           {(yyval.nodo) = crearASTNodo(NODO_SENTENCIAS, NULL, (yyvsp[-1].nodo), (yyvsp[0].nodo));}
#line 1607 "bisson.tab.c"
    break;

  case 20: /* Sentencias_list: %empty  */
#line 167 "bisson.y"
                        {(yyval.nodo) = NULL;}
#line 1613 "bisson.tab.c"
    break;

  case 21: /* Sentencia: Id ASIGNACION Expr PUNTO_COMA  */
#line 171 "bisson.y"
      {
        Simbolo* idEncontrado = buscarSimbolo((yyvsp[-3].nombre), SIMBOLO_VAR_DECL, tablaSimbolos);
        
        ASTNodo* hojaId = crearASTNodo(NODO_IDENTIFICADOR, idEncontrado, NULL, NULL);

        (yyval.nodo) = crearASTNodo(NODO_ASIGNACION, NULL, hojaId, (yyvsp[-1].nodo));
      }
#line 1625 "bisson.tab.c"
    break;

  case 22: /* Sentencia: Metodo_invocacion PUNTO_COMA  */
#line 179 "bisson.y"
                                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1631 "bisson.tab.c"
    break;

  case 23: /* Sentencia: IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque  */
#line 181 "bisson.y"
                                                     {
        ASTNodo* bloques = crearASTNodo(NODO_BLOQUES_IF, NULL, (yyvsp[0].nodo), NULL);
        (yyval.nodo) = crearASTNodo(NODO_IF, NULL, (yyvsp[-2].nodo), bloques);
      }
#line 1640 "bisson.tab.c"
    break;

  case 24: /* Sentencia: IF PARENTESIS_IZQ Expr PARENTESIS_DER Bloque ELSE Bloque  */
#line 185 "bisson.y"
                                                                 {
        ASTNodo* bloques = crearASTNodo(NODO_BLOQUES_IF, NULL, (yyvsp[-2].nodo), (yyvsp[0].nodo));
        (yyval.nodo) = crearASTNodo(NODO_IF_ELSE, NULL, (yyvsp[-4].nodo), bloques);
      }
#line 1649 "bisson.tab.c"
    break;

  case 25: /* Sentencia: WHILE Expr Bloque  */
#line 189 "bisson.y"
                          {(yyval.nodo) = crearASTNodo(NODO_WHILE, NULL, (yyvsp[-1].nodo), (yyvsp[0].nodo));}
#line 1655 "bisson.tab.c"
    break;

  case 26: /* Sentencia: RETURN Expr PUNTO_COMA  */
#line 190 "bisson.y"
                               {(yyval.nodo) = crearASTNodo(NODO_RETORNO, NULL, (yyvsp[-1].nodo), NULL);}
#line 1661 "bisson.tab.c"
    break;

  case 27: /* Sentencia: RETURN PUNTO_COMA  */
#line 191 "bisson.y"
                          {(yyval.nodo) = crearASTNodo(NODO_RETORNO, NULL, NULL, NULL);}
#line 1667 "bisson.tab.c"
    break;

  case 28: /* Metodo_invocacion: Id PARENTESIS_IZQ Expresiones PARENTESIS_DER  */
#line 195 "bisson.y"
      {
       NodoSimbolo* expresiones = listaExpresiones;
       free(listaExpresiones);
       listaExpresiones = NULL;
       
       (yyval.nodo) = crearASTNodo(NODO_INVOCACION, NULL, (yyvsp[-1].nodo), NULL);
       }
#line 1679 "bisson.tab.c"
    break;

  case 29: /* Expresiones: Expr Expresiones  */
#line 204 "bisson.y"
                              {
            agregarSimboloALista((yyvsp[-1].nodo)->simbolo, &listaExpresiones);
            (yyval.nodo) = crearASTNodo(NODO_EXPRESIONES, NULL, (yyvsp[-1].nodo), (yyvsp[0].nodo));
           }
#line 1688 "bisson.tab.c"
    break;

  case 30: /* Expresiones: Expr  */
#line 208 "bisson.y"
                 {
            (yyval.nodo) = (yyvsp[0].nodo);
          }
#line 1696 "bisson.tab.c"
    break;

  case 31: /* Expr: Id  */
#line 213 "bisson.y"
      {// TODO: buscar simbolo declaracion en la tabla de simbolos para asignarle tipo de datos
      Simbolo* simboloId = crearSimbolo();
      simboloId->tipoSimbolo = SIMBOLO_IDENTIFICADOR;
      simboloId->nombre = strdup((yyvsp[0].nombre));
      (yyval.nodo) = crearASTNodo(NODO_IDENTIFICADOR, simboloId, NULL, NULL);
    }
#line 1707 "bisson.tab.c"
    break;

  case 32: /* Expr: Metodo_invocacion  */
#line 219 "bisson.y"
                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1713 "bisson.tab.c"
    break;

  case 33: /* Expr: Literal  */
#line 220 "bisson.y"
              {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1719 "bisson.tab.c"
    break;

  case 34: /* Expr: Expr Op_binario Expr  */
#line 222 "bisson.y"
    {
      (yyvsp[-1].nodo)->izq = (yyvsp[-2].nodo);
      (yyvsp[-1].nodo)->der = (yyvsp[0].nodo);

      (yyval.nodo) = (yyvsp[-1].nodo);
    }
#line 1730 "bisson.tab.c"
    break;

  case 35: /* Expr: RESTA Expr  */
#line 229 "bisson.y"
    {
      if ((yyvsp[0].nodo)->simbolo->tipoDato != TIPO_INTEGER && (yyvsp[0].nodo)->simbolo->tipoDato != TIPO_FLOAT){
        fprintf(stderr, "Error: tipo de dato incompatible con operador '-'.\n");
        exit(1);
      }
      Simbolo* simbolo = crearSimbolo();
      simbolo->tipoSimbolo = SIMBOLO_RESTA;
      agregarSimbolo(simbolo, tablaSimbolos);
      simbolo->tipoDato = (yyvsp[0].nodo)->simbolo->tipoDato;
      (yyval.nodo) = crearASTNodo(NODO_RESTA, simbolo, NULL, (yyvsp[0].nodo));
    }
#line 1746 "bisson.tab.c"
    break;

  case 36: /* Expr: NOT Expr  */
#line 241 "bisson.y"
    {
      if ((yyvsp[0].nodo)->simbolo->tipoDato != TIPO_BOOLEAN){
        fprintf(stderr, "Error: tipo de dato incompatible con operador '!'.\n");
        exit(1);
      }

      Simbolo* simbolo = crearSimbolo();
      simbolo->tipoDato = TIPO_BOOLEAN;
      simbolo->tipoSimbolo = SIMBOLO_NOT;
      agregarSimbolo(simbolo, tablaSimbolos);
      (yyvsp[0].nodo)->simbolo->valor = abs((yyvsp[0].nodo)->simbolo->valor - 1); //TODO ver si funciona
      (yyval.nodo) = crearASTNodo(NODO_NOT, simbolo, NULL, (yyvsp[0].nodo));
    }
#line 1764 "bisson.tab.c"
    break;

  case 37: /* Expr: PARENTESIS_IZQ Expr PARENTESIS_DER  */
#line 255 "bisson.y"
    {
      (yyval.nodo) = (yyvsp[-1].nodo); 
    }
#line 1772 "bisson.tab.c"
    break;

  case 38: /* Op_binario: Op_arit  */
#line 261 "bisson.y"
          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1778 "bisson.tab.c"
    break;

  case 39: /* Op_binario: Op_rel  */
#line 263 "bisson.y"
          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1784 "bisson.tab.c"
    break;

  case 40: /* Op_binario: Op_cond  */
#line 265 "bisson.y"
          {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1790 "bisson.tab.c"
    break;

  case 41: /* Op_arit: SUMA  */
#line 269 "bisson.y"
        { 
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_SUMA;
          agregarSimbolo(simbolo, tablaSimbolos);
          (yyval.nodo) = crearASTNodo(NODO_SUMA, simbolo, NULL, NULL);
        }
#line 1801 "bisson.tab.c"
    break;

  case 42: /* Op_arit: MULTIPLICACION  */
#line 276 "bisson.y"
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_MULTIPLICACION;
          agregarSimbolo(simbolo, tablaSimbolos);
          (yyval.nodo) = crearASTNodo(NODO_MULTIPLICACION, simbolo, NULL, NULL);
        }
#line 1812 "bisson.tab.c"
    break;

  case 43: /* Op_arit: RESTA  */
#line 283 "bisson.y"
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_RESTA;
          agregarSimbolo(simbolo, tablaSimbolos);
          (yyval.nodo) = crearASTNodo(NODO_RESTA, simbolo, NULL, NULL);
        }
#line 1823 "bisson.tab.c"
    break;

  case 44: /* Op_arit: DIV  */
#line 290 "bisson.y"
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_DIV;
          agregarSimbolo(simbolo, tablaSimbolos);
          (yyval.nodo) = crearASTNodo(NODO_DIVISION, simbolo, NULL, NULL);
        }
#line 1834 "bisson.tab.c"
    break;

  case 45: /* Op_arit: MOD  */
#line 297 "bisson.y"
        {
          Simbolo* simbolo = crearSimbolo();
          simbolo->tipoSimbolo = SIMBOLO_MOD;
          agregarSimbolo(simbolo, tablaSimbolos);
          (yyval.nodo) = crearASTNodo(NODO_MOD, simbolo, NULL, NULL);
        }
#line 1845 "bisson.tab.c"
    break;

  case 46: /* Op_cond: AND  */
#line 306 "bisson.y"
   {
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_AND;
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_AND,simbolo,NULL,NULL);
}
#line 1858 "bisson.tab.c"
    break;

  case 47: /* Op_cond: OR  */
#line 314 "bisson.y"
    {
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_OR;
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_OR,simbolo,NULL,NULL);
}
#line 1871 "bisson.tab.c"
    break;

  case 48: /* Op_rel: IGUALDAD  */
#line 324 "bisson.y"
        {
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_IGUALDAD;
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_IGUALDAD,simbolo,NULL,NULL);
}
#line 1884 "bisson.tab.c"
    break;

  case 49: /* Op_rel: MENOR  */
#line 332 "bisson.y"
       {
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_MENOR;
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_MENOR,simbolo,NULL,NULL);
}
#line 1897 "bisson.tab.c"
    break;

  case 50: /* Op_rel: MAYOR  */
#line 340 "bisson.y"
       {
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_MAYOR;
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_MAYOR,simbolo,NULL,NULL);
}
#line 1910 "bisson.tab.c"
    break;

  case 51: /* Literal: INT_LITERAL  */
#line 351 "bisson.y"
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_INTEGER;
  simbolo->tipoSimbolo = SIMBOLO_INTEGER_LITERAL;
  simbolo->valor = (yyvsp[0].valor_int);
  agregarSimbolo(simbolo, tablaSimbolos);

  (yyval.nodo) = crearASTNodo(NODO_INT,simbolo,NULL,NULL);
}
#line 1924 "bisson.tab.c"
    break;

  case 52: /* Literal: FLOAT_LITERAL  */
#line 361 "bisson.y"
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_FLOAT;
  simbolo->tipoSimbolo = SIMBOLO_FLOAT_LITERAL;
  simbolo->valor = (yyvsp[0].valor_float);
  agregarSimbolo(simbolo, tablaSimbolos);// TODO: metodo necesario en la tablaSimbolo 
  
  (yyval.nodo) = crearASTNodo(NODO_FLOAT,simbolo,NULL,NULL);
}
#line 1938 "bisson.tab.c"
    break;

  case 53: /* Literal: FALSE  */
#line 371 "bisson.y"
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_BOOLEAN_LITERAL;
  simbolo->valor = (yyvsp[0].valor_int);
  agregarSimbolo(simbolo, tablaSimbolos);
  
  (yyval.nodo) = crearASTNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
#line 1952 "bisson.tab.c"
    break;

  case 54: /* Literal: TRUE  */
#line 381 "bisson.y"
{
  Simbolo* simbolo = crearSimbolo();
  simbolo->tipoDato = TIPO_BOOLEAN;
  simbolo->tipoSimbolo = SIMBOLO_BOOLEAN_LITERAL;
  simbolo->valor = (yyvsp[0].valor_int);
  agregarSimbolo(simbolo, tablaSimbolos);
  
  (yyval.nodo) = crearASTNodo(NODO_BOOLEAN,simbolo,NULL,NULL);
}
#line 1966 "bisson.tab.c"
    break;


#line 1970 "bisson.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 391 "bisson.y"


void yyerror(const char *s)
{
    fprintf(stderr,
            "Error sintáctico en la línea %d: %s\n",
            yylineno,
            s);
}
