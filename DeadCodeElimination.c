#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
    int isDead;
} Quadruple;

int main() {
    FILE *fin, *fout;
    fin = fopen("inputExpressions.txt", "r");
    fout = fopen("opt2code.txt", "w");
    if (!fin) {
        printf("Error opening file.\n");
        return 1;
    }

    Quadruple q[100];
    int n = 0;

    char line[100];
    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");
    while (fgets(line, sizeof(line), fin)) {
        q[n].isDead = 0;
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

    // --- Common Subexpression Elimination (safe) ---
    for (int i = 0; i < n; i++) {
        if (q[i].op == '=') continue;
        for (int j = i + 1; j < n; j++) {
            if (q[i].op == q[j].op &&
                strcmp(q[i].arg1, q[j].arg1) == 0 &&
                strcmp(q[i].arg2, q[j].arg2) == 0) {

                // Replace later uses of q[j].result with q[i].result
                for (int k = j + 1; k < n; k++) {
                    if (strcmp(q[j].result, q[k].arg1) == 0)
                        strcpy(q[k].arg1, q[i].result);
                    if (strcmp(q[j].result, q[k].arg2) == 0)
                        strcpy(q[k].arg2, q[i].result);
                }
                q[j].isDead = 1;
            }
            //if either arg of common subexpression is redefined
            if (strcmp(q[j].result, q[i].arg1) == 0 || strcmp(q[j].result, q[i].arg2) == 0) break; 
        }
    }

    // --- Dead Code Elimination ---
    for (int i = 0; i < n; i++) {
        int used = 0;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(q[i].result, q[j].arg1) == 0 ||
                strcmp(q[i].result, q[j].arg2) == 0) {
                used = 1;
                break;
            }
        }
        if (!used) q[i].isDead = 1;
    }

    printf("\nOptimized Code :\n");
    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (!q[i].isDead){
            printf("%-9c %-9s %-9s %-9s\n", q[i].op, q[i].arg1, q[i].arg2, q[i].result);
            fprintf(fout, "%-9c %-9s %-9s %-9s\n", q[i].op, q[i].arg1, q[i].arg2, q[i].result);
        }
    }

    return 0;
}