#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int tempcount = 0, tripleindex, startindex = 14;


int precedence(char c){
    switch (c){
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        case '^':return 3;
        case '(':return -1;
        default:return 0;
    }
}
void infixtopostfix(char infix[100], char postfix[100]){
    char stack[100];
    int top = -1, k = 0;
    for(int i = 0; infix[i]; i++){
        if(isspace(infix[i])) continue;
        if(isalnum(infix[i])){
            while(isalnum(infix[i])) postfix[k++] = infix[i++];
            postfix[k++] = ' ';
            i--;
        }
        else if(infix[i] == '(') stack[++top] = infix[i];
        else if(infix[i] == ')'){
            while(top != -1 && stack[top] != '(') postfix[k++] = stack[top--];
            top--;
        }
        else{
            while(top != -1 && infix[i] != '^' && stack[top] != '=' && precedence(infix[i]) <= precedence(stack[top]))
                postfix[k++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    while(top != -1) postfix[k++] = stack[top--];
    postfix[k] = '\0';
}

void parsepostfix(char postfix[100], FILE *f1, FILE *f2){
    int topQ = -1, topT = -1;
    char stackT[100][10], stackQ[100][10];
    for(int i = 0; postfix[i]; i++){
        if(isalnum(postfix[i])){
            char operand[10];
            int k = 0;
            while(!isspace(postfix[i])) operand[k++] = postfix[i++];
            operand[k] = '\0';
            strcpy(stackT[++topT],operand);
            strcpy(stackQ[++topQ],operand);
        }
        else{
            char arg1Q[10], arg2Q[10], arg1T[10], arg2T[10], result[10];
            strcpy(arg2Q, stackQ[topQ--]);
            strcpy(arg1Q, stackQ[topQ--]);
            strcpy(arg2T, stackT[topT--]);
            strcpy(arg1T, stackT[topT--]);
            if(postfix[i] == '='){
                strcpy(result, arg1Q);
                strcpy(arg1Q, arg2Q);
                strcpy(arg2Q, "-");
            }
            else    
                sprintf(result, "T%d", tempcount++);
            fprintf(f1, "(%2d) %c %-9s %-9s %-9s\n", tripleindex, postfix[i], arg1Q, arg2Q, result);
            printf("(%2d) %c %-9s %-9s %-9s\n", tripleindex, postfix[i], arg1Q, arg2Q, result);
            fprintf(f2, "(%2d) %c %-9s %-9s\n", tripleindex, postfix[i], arg1T, arg2T);
            strcpy(stackQ[++topQ], result);
            sprintf(result, "(%d)", tripleindex++);
            strcpy(stackT[++topT], result);  
        }
    }
}

int main(){
    char infix[100], postfix[100];
    FILE *fin = fopen("input.txt", "r");
    FILE *f1 = fopen("quad.txt", "w");
    FILE *f2 = fopen("tripl.txt", "w");
    tripleindex = startindex;
    while(fgets(infix, sizeof(infix), fin)){
        if(strlen(infix) == 0) continue;
        if(infix[strlen(infix) - 1] == '\n') infix[strlen(infix) - 1] = '\0';
        infixtopostfix(infix, postfix);
        parsepostfix(postfix, f1, f2);
    }
    fprintf(f2, "\n\npointers\n");
    for(int i = 0, poindex = startindex; poindex < tripleindex; poindex++){
        fprintf(f2, "P%2d (%2d)\n",i++,poindex);
    }
}