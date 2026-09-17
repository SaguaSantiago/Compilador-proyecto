%{
    #include <stdio.h>
    #include "bisson.tab.h"
    int yylex(void);
    extern int yywrap(void);
%}

%option yylineno

Letra       [a-zA-Z]
Digito      [0-9]
Id          {Letra}({Letra}|{Digito})*
Int         {Digito}+
Float	    {Digito}+\.{Digito}+
Comentario_bloque	    "/*"(.|\n)*"*/"
Comentario_linea 	    "//".*

%%
"int"       { return INT; }
"boolean"      { return BOOLEAN; }
"void"      { return VOID; }
"main"      { return MAIN; }
"return"    { return RETURN; }

"true"      { 
    yylval.valor = 1;
    return TRUE; 
}
"false"     { 
    yylval.valor = 0;
    return FALSE; 
}

{Id} { 
    yylval.nombre = strdup(yytext);
    return IDENTIFICADOR; 
}
{Int} { 
    yylval.valor = atoi(yytext);
    return Int; 
}

{Float} {
    yylval.valor = atoi(yytext);
    return Int;
}


"+"         { return SUMA; }
"*"         { return MULTIPLICACION; }
"="         { return ASIGNACION; }

"("         { return PARENTESIS_IZQ; }
")"         { return PARENTESIS_DER; }
"{"         { return LLAVE_IZQ; }
"}"         { return LLAVE_DER; }
";"         { return PUNTO_COMA; }

"if"	    { return IF; }
"else"      { return ELSE; }

"while"     { return WHILE; }
"float"     { return FLOAT; }

"&&"        { return AND; }
"||"	    { return OR; }
"!"         { return NOT; }

">"	    { return MAYOR; }
"<"	    { return MENOR; }
"=="	    { return IGUAL; }

"%"	    { return MOD; }
"-"	    { return RESTA; }
"/"	    { return DIV; }

[ \t]+     {}
\n         {}

{Comentario_bloque} {}
{Comentario_linea}  {}

.           {
                fprintf(stderr,
                        "Error léxico en línea %d: carácter inesperado '%s'\n",
                        yylineno,
                        yytext);
            }
%%
