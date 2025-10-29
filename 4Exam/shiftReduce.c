#include <stdio.h>
#include <string.h>

#define MAX 50

struct {
    char lhs;
    char rhs[20];
} prods[10];
char stack[MAX], input[MAX];
int top = -1, n;

void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
        stack[top + 1] = '\0';
    }
}

void pop() {
    if (top >= 0) {
        top--;
        stack[top + 1] = '\0';
    }
}

void display(int ip, const char *action) {
    printf("%-15s %-15s %s\n", stack, input + ip, action);
}

int main() {
    int choice;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (example: E->E+E):\n");
    for (int i = 0; i < n; i++)
        scanf(" %c->%s", &prods[i].lhs, prods[i].rhs);

    do {
        top = -1;
        printf("\nEnter input string: ");
        scanf("%s", input);
        strcat(input, "$");
        push('$');

        printf("\n%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");
        printf("-------------------------------------------\n");

        int ip = 0;
        while (1) {
            // shift next symbol from input
            push(input[ip++]);
            display(ip, "Shift");

            // repeatedly attempt reduction
            int reduced = 1;
            while (reduced) {
                reduced = 0;
                for (int i = 0; i < n; i++) {
                    int len = strlen(prods[i].rhs);
                    // only check if stack has enough symbols
                    if (top + 1 >= len) {
                        // compare the top of stack substring with RHS
                        if (strncmp(stack + top - len + 1, prods[i].rhs, len) == 0) {
                            // perform reduction
                            top = top - len + 1;
                            stack[top] = prods[i].lhs;
                            stack[top + 1] = '\0';
                            display(ip, "Reduce");
                            reduced = 1;
                            break;
                        }
                    }
                }
            }
            // acceptance check
            if (stack[top] == prods[0].lhs && input[ip] == '$' && top == 1) {
                display(ip, "Accepted");
                break;
            }
            // rejection check
            if (input[ip] == '$' && !reduced) {
                display(ip, "Rejected");
                break;
            }
        }
        printf("\n1: Continue  2: Exit → ");
        scanf("%d", &choice);
    } while (choice != 2);
    return 0;
}