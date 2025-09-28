%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void arm();
    int ipow(int d, int p);  
%}

%%
[0-9]+      { arm(); }       
.           ;                
%%

int yywrap() {
    return 1;
}

int ipow(int d, int p) {
    int res = 1;
    for (int i = 0; i < p; i++) {
        res *= d;
    }
    return res;
}

void arm() {
    int n = strlen(yytext);
    int val = atoi(yytext);
    int temp = val;
    int res = 0;

    for (int i = 0; i < n; i++) {
        int digit = temp % 10;
        res += ipow(digit, n);
        temp /= 10;
    }

    if (val == res)
        printf("%d is an Armstrong number\n", val);
    else
        printf("%d is not an Armstrong number\n", val);
}

int main() {
    yylex();
    return 0;
}
/* To use pow() from math compile using, "gcc lex.yy.c -o armstrong -lfl -lm" */
