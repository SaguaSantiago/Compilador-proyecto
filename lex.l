%{
    #include <stdio.h>
    #include "bisson.tab.h"
    int yylex(void);
    extern int yywrap(void);
    extern int yylineno; 
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
"int"       { printf("INT\n"); return INT; }
"boolean"      { printf("BOOLEAN\n"); return BOOLEAN; }
"void"      { printf("VOID\n"); return VOID; }

"return"    { printf("RETURN\n"); return RETURN; }

"if"	    { printf("IF\n"); return IF; }
"else"      { printf("ELSE\n"); return ELSE; }

"while"     { printf("WHILE\n"); return WHILE; }
"float"     { printf("FLOAT\n"); return FLOAT; }

"true"      { 
    yylval.valor = 1;
    printf("TRUE\n");
    return TRUE; 
}
"false"     { 
    yylval.valor = 0;
    printf("FALSE\n");
    return FALSE; 
}

{Id} { 
    yylval.nombre = strdup(yytext);
    printf("Id\n");
    return Id; 
}
{Int} { 
    yylval.valor = atoi(yytext);
    printf("INT_LITERAL\n");
    return INT_LITERAL; 
}

{Float} {
    yylval.valor = atoi(yytext);
    printf("FLOAT_LITERAL\n");
    return FLOAT_LITERAL;
}


"+"         { printf("SUMA\n"); return SUMA; }
"*"         { printf("MULTIPLICACION\n"); return MULTIPLICACION; }
"="         { printf("ASIGNACION\n"); return ASIGNACION; }

"("         { printf("PARENTESIS_IZQ\n"); return PARENTESIS_IZQ; }
")"         { printf("PARENTESIS_DER\n"); return PARENTESIS_DER; }
"{"         { printf("LLAVE_IZQ\n"); return LLAVE_IZQ; }
"}"         { printf("LLAVE_DER\n"); return LLAVE_DER; }
";"         { printf("PUNTO_COMA\n"); return PUNTO_COMA; }

"&&"        { printf("AND\n"); return AND; }
"||"	    { printf("OR\n"); return OR; }
"!"         { printf("NOT\n"); return NOT; }

">"	    { printf("MAYOR\n"); return MAYOR; }
"<"	    { printf("MENOR\n"); return MENOR; }
"=="	    { printf("IGUALDAD\n"); return IGUALDAD; }

"%"	    { printf("MOD\n"); return MOD; }
"-"	    { printf("RESTA\n"); return RESTA; }
"/"	    { printf("DIV\n"); return DIV; }

[ \t\r]+   {}
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
