%{
    #include<stdio.h>
%}
%%
"int" | "main" {printf("keyword : %s\n", yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {printf("id : %s\n", yytext);}

[0-9]+\.[0-9]+ {printf("float : %s\n", yytext);}

[0-9][0-9a-zA-Z_]+ {printf("invalid : %s\n", yytext);}

[0-9]+ {printf("num : %s\n", yytext);}

[{}();,] {printf("sy : %s\n", yytext);}

"<=" | "<>" | ">=" | "==" | "--" | "++" {printf("op : %s\n", yytext);}

"//".* {}

[-+/%*<>=] {printf("op : %s\n", yytext);}

\"[^\n\"]\" {printf("string : %s\n", yytext);}

[ \t\n] {}

%%

int yywrap(){
    return 1;
}

int main(){
    yyin = fopen("input.txt","r");
    yylex();
    fclose(yyin);
}