%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%%

"int"   | "if" | "float" | "main"    { printf("Keyword    : %s\n", yytext); }

[a-zA-Z_][a-zA-Z_0-9]*               { printf("Identifier : %s\n", yytext); }

[0-9]+\.[0-9]+                       { printf("Float      : %s\n", yytext); }
[0-9]+                               { printf("Number     : %s\n", yytext); }
[0-9][a-zA-Z_0-9]+                   { printf("Invalid    : %s\n", yytext); }

[\[\]{}();,]                         { printf("Symbol     : %s\n", yytext); }

"<="                                 { printf("LE         : %s\n", yytext); }
">="                                 { printf("GE         : %s\n", yytext); }
"=="                                 { printf("EQ         : %s\n", yytext); }
"<>"                                 { printf("NE         : %s\n", yytext); }
"++"                                 { printf("INC        : %s\n", yytext); }
"--"                                 { printf("DEC        : %s\n", yytext); }

"<"                                  { printf("LT         : %s\n", yytext); }
">"                                  { printf("GT         : %s\n", yytext); }
"="                                  { printf("ASSIGN     : %s\n", yytext); }
"+"                                  { printf("PLUS       : %s\n", yytext); }
"-"                                  { printf("MINUS      : %s\n", yytext); }
"*"                                  { printf("MUL        : %s\n", yytext); }
"//".*                               { printf("Comment    : %s\n", yytext); }
"/"                                  { printf("DIV        : %s\n", yytext); }
"%"                                  { printf("MOD        : %s\n", yytext); }
\"[^\"\n]*\"                         { printf("String     : %s\n", yytext); }

[ \t\n]                              { /* ignore */ }
.                                    { /* ignore unknowns */ }

%%

int yywrap() {
    return 1;
}

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("input.txt");
        exit(1);
    }
    yylex();
    fclose(yyin);
    return 0;
}
