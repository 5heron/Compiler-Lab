#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

struct Code {
    char op;
    char arg1[MAX];
    char arg2[MAX];
    char res[MAX];
    int used;
} code[MAX];

int codeCount = 0;

// Constant Folding
void constant_folding() {
    for (int i = 0; i < codeCount; i++) {
        char *a1 = code[i].arg1;
        char *a2 = code[i].arg2;

        if (isdigit(a1[0]) && isdigit(a2[0])) {
            int x = atoi(a1);
            int y = atoi(a2);
            int result = 0;

            switch (code[i].op) {
                case '+': result = x + y; break;
                case '-': result = x - y; break;
                case '*': result = x * y; break;
                case '/': result = (y != 0) ? x / y : 0; break;
                default: break;
            }

            sprintf(code[i].arg1, "%d", result);
            strcpy(code[i].arg2, "-");
            code[i].op = '=';
        }
    }
}

// Common Subexpression Elimination
void common_subexpression_elimination() {
    for (int i = 0; i < codeCount; i++) {
        for (int j = i + 1; j < codeCount; j++) {
            if (code[i].op == code[j].op &&
                strcmp(code[i].arg1, code[j].arg1) == 0 &&
                strcmp(code[i].arg2, code[j].arg2) == 0) {
                
                for (int k = j + 1; k < codeCount; k++) {
                    if (strcmp(code[k].arg1, code[j].res) == 0)
                        strcpy(code[k].arg1, code[i].res);
                    if (strcmp(code[k].arg2, code[j].res) == 0)
                        strcpy(code[k].arg2, code[i].res);
                }
                code[j].used = 0; // Mark duplicate
            }
        }
    }
}

// Dead Code Elimination
void dead_code_elimination() {
    for (int i = 0; i < codeCount; i++) {
        for (int j = 0; j < codeCount; j++) {
            if (strcmp(code[j].arg1, code[i].res) == 0 ||
                strcmp(code[j].arg2, code[i].res) == 0) {
                code[i].used = 1;
                break;
            }
        }
    }

    printf("\nOptimized Code:\n");
    printf("OPR\tA1\tA2\tRES\n");
    for (int i = 0; i < codeCount; i++) {
        if (code[i].used || i == codeCount - 1) {
            printf("%c\t%s\t%s\t%s\n",
                   code[i].op, code[i].arg1, code[i].arg2, code[i].res);
        }
    }
}

int main() {
    printf("Enter number of 3-address code instructions: ");
    scanf("%d", &codeCount);

    printf("\nEnter 3-address code (OP A1 A2 RES):\n");
    for (int i = 0; i < codeCount; i++) {
        scanf(" %c %s %s %s", &code[i].op, code[i].arg1, code[i].arg2, code[i].res);
        code[i].used = 0;
    }

    printf("\n--- Original Code ---\n");
    printf("OPR\tA1\tA2\tRES\n");
    for (int i = 0; i < codeCount; i++) {
        printf("%c\t%s\t%s\t%s\n",
               code[i].op, code[i].arg1, code[i].arg2, code[i].res);
    }

    constant_folding();
    common_subexpression_elimination();
    dead_code_elimination();

    return 0;
}

/* OUTPUT
developer@ccfl2-pc7:~$ ./a.out
Enter number of 3-address code instructions: 6
Enter 3-address code (OP A1 A2 RES):
+ 2 3 t1
+ 4 5 t2
+ t1 t2 t3
+ 2 3 t4
+ t3 t4 t5
= t5 - a

--- Original Code ---
OPR     A1      A2      RES
+       2       3       t1
+       4       5       t2
+       t1      t2      t3
+       2       3       t4
+       t3      t4      t5
=       t5      -       a

Optimized Code:
OPR     A1      A2      RES
=       5       -       t1
=       9       -       t2
+       t1      t2      t3
+       t3      t1      t5
=       t5      -       a
*/
