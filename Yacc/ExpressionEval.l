%{
#include <stdio.h>
#include <ctype.h>
#include "y.tab.h"

%}

%%

[0-9]+        { yylval = atoi(yytext); return NUM; }
[a-z]         { yylval = yytext[0] - 'a'; return ID; }   // single lowercase letters only
[\t ]+        ;  
.             { return yytext[0]; }
\n            { return 0; }

%%

int yywrap() {
    return 1;
}
