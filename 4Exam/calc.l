%{
    #include <stdio.h>
    #include <stdlib.h>

    int a = 0, b = 0;
    char op = 0;
%}

%%

[ \t\n]+    { /* skip whitespace */ }

[0-9]+      {
                if (op != 0) {
                    b = atoi(yytext);

                    if (op == '+') 
                        printf("%d + %d = %d\n", a, b, a + b);
                    else if (op == '-') 
                        printf("%d - %d = %d\n", a, b, a - b);
                    else if (op == '*') 
                        printf("%d * %d = %d\n", a, b, a * b);
                    else if (op == '/') {
                        if (b != 0)
                            printf("%d / %d = %d\n", a, b, a / b);
                        else
                            printf("Division by zero INVALID\n");
                    }
                    else if (op == '%') {
                        if (b != 0)
                            printf("%d %% %d = %d\n", a, b, a % b);
                        else
                            printf("Modulo by zero INVALID\n");
                    }

                    op = 0;  // reset after operation
                } 
                else {
                    a = atoi(yytext);
                }
            }

[-+*/%]     { op = yytext[0]; }

.           { /* ignore unknowns */ }

%%

int yywrap() { return 1; }

int main() {
    printf("Enter expressions like: 3 + 4 or 10 * 2 (space-separated)\n");
    printf("Press Ctrl+D (Linux/Mac) or Ctrl+Z (Windows) to end.\n\n");
    yylex();
    return 0;
}
