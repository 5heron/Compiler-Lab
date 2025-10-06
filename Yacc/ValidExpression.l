%{
#include "y.tab.h"
%}

%%

[0-9]+      { return NUM; }
[a-z]       { return ID; }
[ \t]+      { }
\n          { return 0; }
[+\-*/()]  { return yytext[0]; }
.           { printf("Invalid Expression\n"); exit(1); }

%%

int yywrap(void) { 
    return 1; 
}
