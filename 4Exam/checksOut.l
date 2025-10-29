%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ipow(int d, int p);
void check_armstrong(int n);
void check_odd_even(int n);
void check_prime(int n);
void check_palindrome(char *str);
%}

%%
[0-9]+              {
                        int n = atoi(yytext);
                        check_odd_even(n);
                        check_prime(n);
                        check_armstrong(n);
                    }

[^ \t\n]+           { check_palindrome(yytext); }

[ \t\n]+            ;    /* Ignore whitespace */

%%

int yywrap() { return 1; }

int ipow(int d, int p) {
    int res = 1;
    for (int i = 0; i < p; i++)
        res *= d;
    return res;
}

void check_armstrong(int n) {
    int temp = n, digits = 0, sum = 0;
    while (temp) {
        digits++;
        temp /= 10;
    }
    temp = n;
    while (temp) {
        int digit = temp % 10;
        sum += ipow(digit, digits);
        temp /= 10;
    }
    if (sum == n)
        printf("%d is an Armstrong number\n", n);
    else
        printf("%d is not an Armstrong number\n", n);
}

void check_odd_even(int n) {
    if (n % 2 == 0)
        printf("%d is Even\n", n);
    else
        printf("%d is Odd\n", n);
}

void check_prime(int n) {
    if (n < 2) {
        printf("%d is not Prime\n", n);
        return;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d is not Prime\n", n);
            return;
        }
    }
    printf("%d is Prime\n", n);
}

void check_palindrome(char *str) {
    int i = 0, j = strlen(str) - 1;
    while (i < j) {
        if (str[i++] != str[j--]) {
            printf("%s is not a palindrome\n", str);
            return;
        }
    }
    printf("%s is a palindrome\n", str);
}

int main() {
    printf("Enter input text (numbers/words):\n");
    yylex();
    return 0;
}
