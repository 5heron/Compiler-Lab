%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token NUM ID
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

stmt: expr { printf("Valid Expression\n"); }
    ;

expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '-' expr %prec UMINUS
    | '(' expr ')'
    | NUM
    | ID
    ;

%%

int main(void) {
    printf("Enter the Expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Invalid Expression\n");
    exit(1);
}
