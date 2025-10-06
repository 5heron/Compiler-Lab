#include <stdio.h>
#include <string.h>

typedef struct {
    char result[10];
    char arg1[10];
    char op;
    char arg2[10];
} Quadruple;

int main() {
    FILE *fin = fopen("optcode.txt", "r");
    if (!fin) {
        printf("Error opening file.\n");
        return 1;
    }

    Quadruple q[50];
    int n = 0;

    // Read lines in format: Operator Arg1 Arg2 Result
    while (fscanf(fin, " %c %s %s %s", &q[n].op, q[n].arg1, q[n].arg2, q[n].result) == 4) 
        n++;
    fclose(fin);

    printf("Generated Assembly Code:\n\n");

    for (int i = 0; i < n; i++) {
        if (q[i].op == '=') {
            // Move constant or value into result
            printf("MOV %s, %s\n", q[i].result, q[i].arg1);
        } else {
            // Arithmetic operation
            printf("MOV R0, %s\n", q[i].arg1);
            switch (q[i].op) {
                case '+': printf("ADD R0, %s\n", q[i].arg2); break;
                case '-': printf("SUB R0, %s\n", q[i].arg2); break;
                case '*': printf("MUL R0, %s\n", q[i].arg2); break;
                case '/': printf("DIV R0, %s\n", q[i].arg2); break;
            }
            printf("MOV %s, R0\n", q[i].result);
        }
    }

    return 0;
}
