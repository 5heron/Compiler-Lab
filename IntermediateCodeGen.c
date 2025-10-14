#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tmpCount = 0;

// Function to check operator precedence
int precedence(char op) {
    switch (op) {
        case '=':
            return 0; 
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
    int top = -1, k = 0;

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;  // skip spaces
        
        if (isalnum(expr[i])) {
            postfix[k++] = expr[i];
        } 
        else if (expr[i] == '(') {
            stack[++top] = expr[i];
        } 
        else if (expr[i] == ')') {
            while (stack[top] != '(')
                postfix[k++] = stack[top--];
            top--; // remove '('
        } 
        else { // Operator
            while (top != -1 && expr[i] != '^' && expr[i] != '=' && precedence(stack[top]) >= precedence(expr[i])) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = expr[i];
        }
    }

    while (top != -1)
        postfix[k++] = stack[top--];

    postfix[k] = '\0';
}

// --- Parse postfix → Intermediate code ---
void parsePostfix(char* postfix, FILE *fout) {
    char stack[100][10];
    int top = -1;
    char result[10];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            stack[++top][0] = postfix[i];
            stack[top][1] = '\0';
        } else {
            char arg2[10], arg1[10];
            strcpy(arg2, stack[top--]);
            strcpy(arg1, stack[top--]);

            if (postfix[i] == '=') {
                strcpy(result, arg1);
                strcpy(arg1, arg2);
                strcpy(arg2, "-");
            } else {
                sprintf(result, "T%d", tmpCount++);
            }

            printf("%-9c %-9s %-9s %-9s\n", postfix[i], arg1, arg2, result);
            fprintf(fout, "%-9c %-9s %-9s %-9s\n", postfix[i], arg1, arg2, result);

            strcpy(stack[++top], result);
        }
    }
}

int main() {
    FILE *fin, *fout;
    fin = fopen("inputExpressions.txt", "r");
    fout = fopen("icode.txt", "w");

    if (!fin || !fout) {
        printf("Error opening file.\n");
        return 1;
    }

    char expr[100];
    char postfix[100];
    tmpCount = 0;

    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");

    // --- Read multiple expressions ---
    while (fgets(expr, sizeof(expr), fin)) {
        if (strlen(expr) == 0) continue;  // skip blank lines
        if (expr[strlen(expr) - 1] == '\n') expr[strlen(expr) - 1] = '\0'; // Clean line endings
        infixToPostfix(expr, postfix);
        parsePostfix(postfix, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("\nIntermediate code saved to icode.txt\n");
    return 0;
}