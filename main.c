extern int yylex();

int yyparse(void);

int yywrap(void) { return 1; }

int main() {
  yyparse();
  return 0;
}
