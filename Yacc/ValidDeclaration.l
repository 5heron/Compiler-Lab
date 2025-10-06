%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

int             { return INT; }
float           { return FLOAT; }
char            { return CHAR; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
","             { return ','; }
";"             { return ';'; }
[ \t]+          { }
\n              { return 0; }
.               { printf("Invalid token: %s\n", yytext); exit(1); }

%%

int yywrap(void) { 
    return 1; 
}