%{
#include "y.tab.h"
#include <stdio.h>
%}

%%

"if"            return IF;
"else"          return ELSE;
"while"         return WHILE;
"do"            return DO;
"for"           return FOR;

"=="            return EQ;
"!="            return NE;
"<="            return LE;
">="            return GE;
"<"             return LT;
">"             return GT;

"="             return ASSIGN;
"+"             return ADD;
"-"             return SUB;
"*"             return MUL;
"/"             return DIV;

"("             return LPAREN;
")"             return RPAREN;
"{"             return LBRACE;
"}"             return RBRACE;
";"             return SEMI;
","             return COMMA;

[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  return ID;

[ \t\r\n]+      ;    /* ignore whitespace */

.               { printf("Unknown character: %s\n", yytext); }

%%

int yywrap(void) { return 1; }
