%{
#include <stdio.h>
#include <stdlib.h>

int values[26];  
int assigned[26];
int yylex(void);
int yyerror(const char *s);

%}

%token NUM ID
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

stmt: expr { printf("Valid Expression\nResult = %d\n", $1); };

expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { if ($3 == 0) { printf("Error: Division by zero\n"); exit(1); } $$ = $1 / $3; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUM { $$ = $1; }
    | ID { if (!assigned[$1]) {
               printf("Enter value for %c: ", 'a' + $1);
               scanf("%d", &values[$1]);
               assigned[$1] = 1;
           }
           $$ = values[$1];
         }
;

%%

int main() {
    printf("Enter the Expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Invalid Expression\n"); 
    return 0;
}
