%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token INT FLOAT CHAR ID

%%

stmt:
      type varlist ';'   { printf("Valid Declaration\n"); }
    ;

type:
      INT
    | FLOAT
    | CHAR
    ;

varlist:
      ID
    | varlist ',' ID
    ;

%%

int main(void) {
    printf("Enter Declaration: ");
    if (yyparse() == 0)
        return 0;
    return 1;
}

int yyerror(const char *s) {
    printf("Invalid Declaration\n");
    exit(1);
}
