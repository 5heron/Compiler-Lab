#include<stdio.h>
#include<string.h>
#include<ctype.h>

char keywords[][10] = {"int", "main", "if", "while", "else", "return", "float"};
int n_k = 7;

int iskeyword(char word[100]){
    for(int i = 0; i < n_k; i++)
        if(strcmp(word, keywords[i]) == 0) return 1;
    return 0;
}

int main(){
    int state = 0, i;
    FILE *fin = fopen("input.txt", "r");
    char ch = fgetc(fin), word[100];
    while(ch != EOF){
        switch (state){
            case 0: 
                if(ch == '*' || ch == '%') printf("op : %c\n",ch);
                else if(isalpha(ch) || ch == '_') {state = 1; i = 0; word[i++] = ch;}
                else if(isdigit(ch)) {state = 2; i = 0; word[i++] = ch;}
                else if(ch == '+') state = 3;
                else if(ch == '-') state = 4;
                else if(ch == '/') state = 5;
                else if(ch == '>') state = 6;
                else if(ch == '<') state = 7;
                else if(ch == '=') state = 8;
                else if(strchr("(){};,",ch)) printf("Sy : %c\n",ch);
                break;
            case 1:
                if(isalnum(ch) || ch == '_') {word[i++] = ch;}
                else {
                    word[i] = '\0'; 
                    if(iskeyword(word))
                        printf("keyword : %s\n",word);
                    else printf("id : %s\n",word);
                    state = 0;
                    continue;
                }
                break;
            case 2:
                if(isdigit(ch)) {word[i++] = ch;}
                else if(ch == '.') {word[i++] = ch; state = 9;}
                else if(isalpha(ch) || ch == '_') {word[i++] = ch; state = 10;}
                else {word[i] = '\0'; printf("num : %s\n",word); state = 0; continue;}
                break;
            case 3:
                if(ch == '+') {printf("op : ++\n"); state = 0;}
                else {printf("op : +\n"); state = 0; continue;}
                break;
            case 4:
                if(ch == '-') {printf("op : --\n"); state = 0;}
                else {printf("op : -\n"); state = 0; continue;}
                break;
            case 5:
                if(ch == '/') {state = 11;}
                else {printf("op : /\n"); state = 0; continue;}
                break;
            case 6:
                if(ch == '=') {printf("op : >=\n"); state = 0;}
                else {printf("op : >\n"); state = 0; continue;}
                break;
            case 7:
                if(ch == '=') {printf("op : <=\n"); state = 0;}
                else if(ch == '>') {printf("op : <>\n"); state = 0;}
                else {printf("op : <\n"); state = 0; continue;}
                break;
            case 8:
                if(ch == '=') {printf("op : ==\n"); state = 0;}
                else {printf("op : =\n"); state = 0; continue;}
                break;
            case 9:
                if(isdigit(ch)) {word[i++] = ch;}
                else if(isalpha(ch) || ch == '_') {word[i++] = ch; state = 10;}
                else {word[i] = '\0'; printf("float : %s\n",word); state = 0; continue;}
                break;
            case 10:
                if(isalnum(ch) || ch == '_') {word[i++] = ch;}
                else {word[i] = '\0'; printf("invalid id : %s\n",word); state = 0; continue;}
                break;
            case 11:
                if(ch == '\n') state = 0;
                break;
            default:
                break;
        }
        ch = fgetc(fin);
    }
    fclose(fin);
}