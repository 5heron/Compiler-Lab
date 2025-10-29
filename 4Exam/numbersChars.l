%{
    #include <stdio.h>
    #include <string.h>

    int l = 0, s = 0, t = 0;             // line, space, tab counters
    int vow = 0, con = 0;                // vowel, consonant counters
    int positives = 0, negatives = 0;    // positive/negative number counters
    int dec = 0, oct = 0, hex = 0, flt = 0;  // number type counters
    int str_lit = 0;                     // string literal counter
%}

%%
[\n]                { l++; }                        // Count lines
[ ]                 { s++; }                        // Count spaces
[\t]                { t++; }                        // Count tabs

[aeiouAEIOU]        { vow++; }                      // Count vowels
[a-zA-Z]            { con++; }                      // Count consonants

0[xX][0-9a-fA-F]+   { hex++; printf("Hexadecimal: %s\n", yytext); }
0[0-7]+             { oct++; printf("Octal: %s\n", yytext); }
[-]?[0-9]+\.[0-9]+  { flt++; printf("Float: %s\n", yytext); }
-[0-9]+             { negatives++; dec++; printf("Negative decimal: %s\n", yytext); }
[0-9]+              { positives++; dec++; printf("Positive decimal: %s\n", yytext); }

\"[^\"\n]*\"    { str_lit++; printf("String literal: %s\n", yytext); }
'[^'\n]*'       { str_lit++; printf("String literal: %s\n", yytext); }

.                   { }                             // Ignore others
%%

int yywrap() { return 1; }

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error opening input.txt\n");
        return 1;
    }

    printf("===== DETECTED TOKENS =====\n");
    yylex();

    printf("\n===== CHARACTER STATISTICS =====\n");
    printf("Number of lines      : %d\n", l);
    printf("Number of spaces     : %d\n", s);
    printf("Number of tabs       : %d\n", t);

    printf("\n===== LETTER STATISTICS =====\n");
    printf("Number of vowels     : %d\n", vow);
    printf("Number of consonants : %d\n", con);

    printf("\n===== NUMBER STATISTICS =====\n");
    printf("Positives (decimal)  : %d\n", positives);
    printf("Negatives (decimal)  : %d\n", negatives);
    printf("Decimal numbers      : %d\n", dec);
    printf("Octal numbers        : %d\n", oct);
    printf("Hexadecimal numbers  : %d\n", hex);
    printf("Floating-point nums  : %d\n", flt);

    printf("\n===== STRING STATISTICS =====\n");
    printf("String literals      : %d\n", str_lit);

    fclose(yyin);
    return 0;
}
