#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {"int", "float", "if", "else", "while", "return", "main"};
int n_keywords = 7;

int isKeyword(char *word) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main(){
    FILE *fin = fopen("input.txt","r");
    char ch = fgetc(fin), word[20];
    int state = 0, i = 0;
    while(ch != EOF){
        switch (state){
            case 0:
                if(ch == '*' || ch == '%') printf("Op : %c\n",ch);
                else if(ch == '<') { state = 1; }
                else if(ch == '>') { state = 2; }
                else if(ch == '=') { state = 3; }
                else if(ch == '+') { state = 4;}
                else if(ch == '-') { state = 5;}
                else if(isalpha(ch) || ch == '_') { state = 6; i = 0; word[i++] = ch;}
                else if(isdigit(ch)) { state = 7; i = 0; word[i++] = ch;}
                else if(ch == '/') { state = 10; }
                else if(ch == '(' || ch == ')' || ch == ';' || ch == '{' || ch == '}' || ch == ',')
                    printf("Symbol : %c\n",ch);
                break;
            case 1:
                if(ch == '>') {printf("Op : <>\n"); state = 0;}
                else if(ch == '=') {printf("Op : <=\n"); state = 0;}
                else { printf("<\n"); state = 0; continue;}
                break;
            case 2:
                if(ch == '=') {printf("Op : >=\n"); state = 0;}
                else { printf("Op : >\n");state = 0; continue;}
                break;
            case 3:
                if(ch == '=') {printf("Op : ==\n"); state = 0;}
                else { printf("Assign : =\n");state = 0; continue;}
                break;
            case 4:
                if(ch == '+') {printf("Op : ++\n"); state = 0;}
                else { printf("Op : +\n");state = 0; continue;}
                break;
            case 5:
                if(ch == '-') {printf("Op : --\n"); state = 0;}
                else { printf("Op : -\n");state = 0; continue;}
                break;
            case 6:
                if(isalnum(ch) || ch == '_') { word[i++] = ch;}
                else 
                { 
                    word[i] = '\0'; 
                    if(isKeyword(word)) printf("Keyword : ");
                    else printf("ID : "); 
                    printf("%s\n",word);
                    state = 0; 
                    continue;}
                break;
            case 7:
                if(isdigit(ch)) { word[i++] = ch;}
                else if(isalpha(ch) || ch == '_') { state = 9; word[i++] = ch;}
                else if(ch == '.') { state = 8; word[i++] = ch;}
                else { word[i] = '\0'; printf("Number : %s\n",word);state = 0; continue;}
                break;
            case 8:
                if(isdigit(ch)) { word[i++] = ch;}
                else { word[i] = '\0'; printf("Float : %s\n",word);state = 0; continue;}
                break;
            case 9:
                if(isalnum(ch) || ch == '_') { word[i++] = ch;}
                else { word[i] = '\0'; printf("Invalid id : %s\n",word);state = 0; continue;}
                break;
            case 10:
                if(ch == '/') {state = 11;}
                else { printf("/");state = 0; continue;}
                break;
            case 11:
                if(ch == '\n') state = 0;
                break;
        }
        ch = fgetc(fin);
    }
    fclose(fin); 
}