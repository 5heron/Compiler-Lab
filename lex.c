#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 50

char keywords[][10] = {"int", "float", "if", "else", "while", "return", "main"};
int n_keywords = sizeof(keywords)/sizeof(keywords[0]);

int isKeyword(char *word) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) { 
        perror("input.txt"); 
        exit(1); 
    }

    int ch;
    char word[MAX_WORD];
    int i = 0, state = 0;

    ch = fgetc(fp);
    while (ch != EOF) {
        switch (state) {
            case 0: // Start
                if (isspace(ch)) break;

                if (ch == '/') state = 9;
                else if (isalpha(ch) || ch == '_') { i = 0; word[i++] = ch; state = 1; }
                else if (isdigit(ch)) { i = 0; word[i++] = ch; state = 2; }
                else if (ch == '<') state = 3;
                else if (ch == '>') state = 4;
                else if (ch == '=') state = 5;
                else if (ch == '+') state = 6;
                else if (ch == '-') state = 7;
                else if (ch == '*' || ch == '%') printf("Operator: %c\n", ch);
                else if (strchr(";{}(),.", ch)) printf("Symbol: %c\n", ch);
                break;

            case 1: // Identifier / Keyword
                if (isalnum(ch) || ch == '_') {
                    if (i < MAX_WORD - 1) word[i++] = ch;
                } else {
                    word[i] = '\0';
                    if (isKeyword(word)) printf("Keyword: %s\n", word);
                    else printf("Identifier: %s\n", word);
                    i = 0;
                    state = 0;
                    continue;
                }
                break;

            case 2: // Number
                if (isdigit(ch)) {
                    if (i < MAX_WORD - 1) word[i++] = ch;
                } else if (ch == '.') {
                    if (i < MAX_WORD - 2) {
                        word[i++] = '.';
                        state = 8;
                    } else {
                        word[i] = '\0';
                        printf("Number: %s\n", word);
                        i = 0;
                        state = 0;
                    }
                } else if (isalpha(ch) || ch == '_') {
                    state = 10;
                    if (i < MAX_WORD - 1) word[i++] = ch;
                } else {
                    word[i] = '\0';
                    printf("Number: %s\n", word);
                    i = 0;
                    state = 0;
                    continue;
                }
                break;

            case 8: // Float continuation
                if (isdigit(ch)) {
                    if (i < MAX_WORD - 1) word[i++] = ch;
                } else {
                    word[i] = '\0';
                    printf("Float: %s\n", word);
                    i = 0;
                    state = 0;
                    continue;
                }
                break;

            case 3: // '<'
                if (ch == '=') { printf("Operator: <=\n"); state = 0; }
                else if (ch == '>') { printf("Operator: <>\n"); state = 0; }
                else { printf("Operator: <\n"); state = 0; continue; }
                break;

            case 4: // '>'
                if (ch == '=') { printf("Operator: >=\n"); state = 0; }
                else { printf("Operator: >\n"); state = 0; continue; }
                break;

            case 5: // '='
                if (ch == '=') { printf("Operator: ==\n"); state = 0; }
                else { printf("Assignment Operator: =\n"); state = 0; continue; }
                break;

            case 6: // '+'
                if (ch == '+') { printf("Operator: ++\n"); state = 0; }
                else { printf("Operator: +\n"); state = 0; continue; }
                break;

            case 7: // '-'
                if (ch == '-') { printf("Operator: --\n"); state = 0; }
                else { printf("Operator: -\n"); state = 0; continue; }
                break;

            case 9: // '/'
                if (ch == '/') state = 11;
                else { printf("Operator: /\n"); state = 0; continue; }
                break;

            case 11: // inside comment
                if (ch == '\n') state = 0;
                break;

            case 10: // invalid identifier starting with digit
                if (isalnum(ch) || ch == '_') {
                    if (i < MAX_WORD - 1) word[i++] = ch;
                } else {
                    word[i] = '\0';
                    printf("Error: Invalid identifier starting with digit: %s\n", word);
                    i = 0;
                    state = 0;
                    continue;
                }
                break;
        }

        ch = fgetc(fp);
    }

    fclose(fp);
    return 0;
}
