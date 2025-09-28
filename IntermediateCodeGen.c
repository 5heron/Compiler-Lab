#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tmpCount = 0;

// Function to check operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to convert infix expression to postfix
void infixToPostfix(char* expr, char* postfix) {
    char stack[100];
    int top = -1;
    int k = 0, i;

    for (i = 0; expr[i]; i++) {
        if (isalnum(expr[i])) {   // If operand, add to postfix
            postfix[k++] = expr[i];
        } 
        else if (expr[i] == '(') {
            stack[++top] = expr[i];
        } 
        else if (expr[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--; // remove '('
        } 
        else {  // Operator
            while (top != -1 && ((expr[i] != '^' && precedence(stack[top]) >= precedence(expr[i])))) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = expr[i];
        }
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
    }

    postfix[k] = '\0';
    printf("Postfix expression: %s\n", postfix);
}

// Function to parse postfix and generate intermediate code
void parsePostfix(char* postfix) {
    char stack[100][10];
    int top = -1;
    int i = 0;
    char result[10];

    while (postfix[i] != '\0') {
        if (isalnum(postfix[i])) {
            stack[++top][0] = postfix[i];
            stack[top][1] = '\0';
        } else {
            char arg2[10], arg1[10];
            strcpy(arg2, stack[top--]);
            strcpy(arg1, stack[top--]);

            sprintf(result, "T%d", tmpCount++);
            printf("%-9c %-9s %-9s %-9s\n", postfix[i], arg1, arg2, result);

            strcpy(stack[++top], result);
        }
        i++;
    }
}

int main() {
    char expr[100];
    char postfix[100];

    printf("Enter an infix expression: ");
    scanf("%99s", expr);   // safer input

    tmpCount = 0; // reset temp variable count

    infixToPostfix(expr, postfix);

    printf("\nIntermediate code:\n");
    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");

    parsePostfix(postfix);

    return 0;
}
