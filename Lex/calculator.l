%{
    #include <stdio.h>
    #include <stdlib.h>

    int a = 0, b = 0;
%}

%%

[ \t\n]+    { /* skip whitespace */ }

[0-9]+      {
                if (a == 0)
                    a = atoi(yytext);
                else
                    b = atoi(yytext);
            }

"+"         { printf("%d + %d = %d\n", a, b, a + b); a = 0; b = 0; }
"-"         { printf("%d - %d = %d\n", a, b, a - b); a = 0; b = 0; }
"*"         { printf("%d * %d = %d\n", a, b, a * b); a = 0; b = 0; }
"/"         { 
                if (b != 0)
                    printf("%d / %d = %d\n", a, b, a / b);
                else
                    printf("Division by zero INVALID\n");
                a = 0; b = 0;
            }
"%"         {
                if (b != 0)
                    printf("%d %% %d = %d\n", a, b, a % b);
                else
                    printf("Modulo by zero INVALID\n");
                a = 0; b = 0;
            }
.           { /* ignore unknowns */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the inputs (as Operand1 Operand2 Operator):\n");
    yylex();
    return 0;
}
