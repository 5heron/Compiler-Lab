#include <stdio.h>
#include <string.h>

typedef struct {
    char result[10];
    char arg1[10];
    char op;
    char arg2[10];
} Quadruple;


int main() {
    FILE *fin;
    fin = fopen("inputExpressions.txt", "r");
    if (!fin) {
        printf("Error opening file.\n");
        return 1;
    }

    Quadruple q[50];
    int n = 0;

    char line[100];
    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");
    while (fgets(line, sizeof(line), fin)) {
        if (sscanf(line, " %s = %s %c %s", q[n].result, q[n].arg1, &q[n].op, q[n].arg2) == 4) {
            // Format: a = b + c
        }
        else if (sscanf(line, " %s = %s", q[n].result, q[n].arg1) == 2) {
            q[n].op = '=';
            strcpy(q[n].arg2, "-");
        }
        printf("%-9c %-9s %-9s %-9s\n", q[n].op, q[n].arg1, q[n].arg2, q[n].result); 
        n++;
    }
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
