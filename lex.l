%{
    #include <stdio.h>
    #include "bisson.tab.h"
    int yylex(void);
    extern int yywrap(void);
    extern int yylineno; 
    /* Se pone en 1 ante un error lexico (caracter inesperado). */
    int error_lexico = 0;
%}

%option yylineno

Letra       [a-zA-Z]
Digito      [0-9]
Id          {Letra}({Letra}|{Digito}|_)*
Int         {Digito}+
Float	    {Digito}+\.{Digito}+
Comentario_bloque	    "/*"(.|\n)*"*/"
Comentario_linea 	    "//".*

%%
"int"       { fprintf(yyout, "INT\n"); return INT; }
"boolean"      { fprintf(yyout, "BOOLEAN\n"); return BOOLEAN; }
"void"      { fprintf(yyout, "VOID\n"); return VOID; }

"return"    { fprintf(yyout, "RETURN\n"); return RETURN; }

"if"	    { fprintf(yyout, "IF\n"); return IF; }
"else"      { fprintf(yyout, "ELSE\n"); return ELSE; }

"while"     { fprintf(yyout, "WHILE\n"); return WHILE; }
"float"     { fprintf(yyout, "FLOAT\n"); return FLOAT; }

"true"      { 
    yylval.valor = 1;
    fprintf(yyout, "TRUE\n");
    return TRUE; 
}
"false"     { 
    yylval.valor = 0;
    fprintf(yyout, "FALSE\n");
    return FALSE; 
}

{Id} { 
    yylval.nombre = strdup(yytext);
    fprintf(yyout, "Id\n");
    return Id; 
}
{Int} { 
    yylval.valor = atoi(yytext);
    fprintf(yyout, "INT_LITERAL\n");
    return INT_LITERAL; 
}

{Float} {
    yylval.valor = atof(yytext);
    fprintf(yyout, "FLOAT_LITERAL\n");
    return FLOAT_LITERAL;
}


"+"         { fprintf(yyout, "SUMA\n"); return SUMA; }
"*"         { fprintf(yyout, "MULTIPLICACION\n"); return MULTIPLICACION; }
"="         { fprintf(yyout, "ASIGNACION\n"); return ASIGNACION; }

"("         { fprintf(yyout, "PARENTESIS_IZQ\n"); return PARENTESIS_IZQ; }
")"         { fprintf(yyout, "PARENTESIS_DER\n"); return PARENTESIS_DER; }
"{"         { fprintf(yyout, "LLAVE_IZQ\n"); return LLAVE_IZQ; }
"}"         { fprintf(yyout, "LLAVE_DER\n"); return LLAVE_DER; }
";"         { fprintf(yyout, "PUNTO_COMA\n"); return PUNTO_COMA; }

","	    { fprintf(yyout, "COMA\n"); return COMA; }

"&&"        { fprintf(yyout, "AND\n"); return AND; }
"||"	    { fprintf(yyout, "OR\n"); return OR; }
"!"         { fprintf(yyout, "NOT\n"); return NOT; }

">"	    { fprintf(yyout, "MAYOR\n"); return MAYOR; }
"<"	    { fprintf(yyout, "MENOR\n"); return MENOR; }
"=="	    { fprintf(yyout, "IGUALDAD\n"); return IGUALDAD; }

"%"	    { fprintf(yyout, "MOD\n"); return MOD; }
"-"	    { fprintf(yyout, "RESTA\n"); return RESTA; }
"/"	    { fprintf(yyout, "DIV\n"); return DIV; }

[ \t\r]+   {}
\n         {}

{Comentario_bloque} {}
{Comentario_linea}  {}

.           {
                error_lexico = 1;
                fprintf(stderr,
                        "Error léxico en línea %d: carácter inesperado '%s'\n",
                        yylineno,
                        yytext);
            }
%%