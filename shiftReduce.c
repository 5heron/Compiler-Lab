#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100], stack[100][10]; // stack holds strings ("a", "+", "E", etc.)
int top = -1;

void push(char *sym) {
    strcpy(stack[++top], sym);
}

void printStack() {
    for (int i = 0; i <= top; i++)
        printf("%s", stack[i]);
    printf("\n");
}

void reduce() {
    int i;
    // Reduce "id" → E
    for (i = 0; i <= top; i++) {
        if (isalnum((unsigned char)stack[i][0])) {
            strcpy(stack[i], "E");
        }
    }
    // Reduce (E) → E
    for (i = 0; i <= top - 2; i++) {
        if (strcmp(stack[i], "(") == 0 &&
            strcmp(stack[i+1], "E") == 0 &&
            strcmp(stack[i+2], ")") == 0) {
            strcpy(stack[i], "E");
            // shift stack left
            for (int j = i+1; j <= top-2; j++)
                strcpy(stack[j], stack[j+2]);
            top -= 2;
        }
    }
    // Reduce E+E or E-E or E/E or E*E → E
    for (i = 0; i <= top - 2; i++) {
        if (strcmp(stack[i], "E") == 0 &&
           (strcmp(stack[i+1], "+") == 0 || strcmp(stack[i+1], "*") == 0 || 
           strcmp(stack[i+1], "-") == 0 || strcmp(stack[i+1], "/") == 0) &&
            strcmp(stack[i+2], "E") == 0) {
            strcpy(stack[i], "E");
            for (int j = i+1; j <= top-2; j++)
                strcpy(stack[j], stack[j+2]);
            top -= 2;
        }
    }
}

int main() {
    printf("Enter the input string (like a+b-c): ");
    scanf("%s", input);

    printf("\nSHIFT-REDUCE Parsing Steps:\n");

    int i = 0;
    while (i < strlen(input)) {
        char sym[2] = {input[i++], '\0'};
        push(sym);
        printf("Shift: ");
        printStack();
        reduce();
        printf("Reduce: ");
        printStack();
    }
    // Final reduction
    reduce();
    if (top == 0 && strcmp(stack[0], "E") == 0)
        printf("\nString accepted.\n");
    else
        printf("\nString rejected.\n");

    return 0;
}
