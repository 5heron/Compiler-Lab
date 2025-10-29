#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tmpCount = 0;
int startIndex = 14;  // 👈 You can set this to start numbering from any index
int tripleIndex; 

// --- Operator precedence ---
int precedence(char op) {
    switch (op) {
        case '=': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default:  return 0;
    }
}

// --- Convert infix to postfix ---
void infixToPostfix(char* expr, char* postfix) {
    char stack[100];
    int top = -1, k = 0;

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;

        if (isalnum(expr[i])) {
            while (isalnum(expr[i])) postfix[k++] = expr[i++];
            postfix[k++] = ' ';
            i--;
        } 
        else if (expr[i] == '(') {
            stack[++top] = expr[i];
        } 
        else if (expr[i] == ')') {
            while (top >= 0 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--;
        } 
        else { 
            while (top != -1 && stack[top] != '(') {
                int p1 = precedence(expr[i]);
                int p2 = precedence(stack[top]);
                if ((p2 > p1) || (p2 == p1 && expr[i] != '^'))
                    postfix[k++] = stack[top--];
                else
                    break;
            }
            stack[++top] = expr[i];
        }
    }
    while (top != -1)
        postfix[k++] = stack[top--];
    postfix[k] = '\0';
}

// --- Generate Intermediate Code ---
void parsePostfix(char* postfix, FILE *fq, FILE *ft, FILE *fi) {
    char stack[100][10];
    int top = -1;
    char result[10];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[10];
            int j = 0;
            while (postfix[i] != ' ') operand[j++] = postfix[i++];
            operand[j] = '\0';
            strcpy(stack[++top], operand);
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

            // --- QUADRUPLES ---
            fprintf(fq, "(%-2d)   %-6c %-10s %-10s %-10s\n", tripleIndex, postfix[i], arg1, arg2, result);

            // --- TRIPLES ---
            fprintf(ft, "(%-2d)   %-6c %-10s %-10s\n", tripleIndex, postfix[i], arg1, arg2);

            // --- INDIRECT TRIPLES (Instruction Table) ---
            fprintf(fi, "(%-2d)   %-6c %-10s %-10s\n", tripleIndex, postfix[i], arg1, arg2);

            strcpy(stack[++top], result);
            tripleIndex++;
        }
    }
}

int main() {
    FILE *fin, *fq, *ft, *fi;
    fin = fopen("inputExpressions.txt", "r");
    fq  = fopen("quadruples.txt", "w");
    ft  = fopen("triples.txt", "w");
    fi  = fopen("indirectTriples.txt", "w");

    if (!fin || !fq || !ft || !fi) {
        printf("Error opening file.\n");
        return 1;
    }

    char expr[100], postfix[100];
    tmpCount = 0;
    tripleIndex = startIndex;

    // --- Quadruple Header ---
    fprintf(fq, "================ QUADRUPLE TABLE ================\n");
    fprintf(fq, "%-4s %-6s %-10s %-10s %-10s\n", "No", "Op", "Arg1", "Arg2", "Result");
    fprintf(fq, "-------------------------------------------------\n");

    // --- Triple Header ---
    fprintf(ft, "================ TRIPLE TABLE ===================\n");
    fprintf(ft, "%-4s %-6s %-10s %-10s\n", "No", "Op", "Arg1", "Arg2");
    fprintf(ft, "-------------------------------------------------\n");

    // --- Indirect Triple Header ---
    fprintf(fi, "============= INDIRECT TRIPLE TABLE =============\n");
    fprintf(fi, "Instruction Table:\n");
    fprintf(fi, "%-4s %-6s %-10s %-10s\n", "No", "Op", "Arg1", "Arg2");
    fprintf(fi, "-------------------------------------------------\n");

    // --- Process each expression ---
    while (fgets(expr, sizeof(expr), fin)) {
        if (strlen(expr) == 0) continue;
        if (expr[strlen(expr) - 1] == '\n') expr[strlen(expr) - 1] = '\0';
        infixToPostfix(expr, postfix);
        parsePostfix(postfix, fq, ft, fi);
    }

    // --- Indirect Triple Pointer Table (at end) ---
    fprintf(fi, "\nPointer Table:\n");
    fprintf(fi, "%-6s %-10s\n", "Ptr", "Instruction");
    fprintf(fi, "----------------------\n");
    for (int p = startIndex, i = 0; p < tripleIndex; p++)
        fprintf(fi, "P%-5d -> (%d)\n", i++, p);
    fprintf(fi, "----------------------\n");

    fclose(fin);
    fclose(fq);
    fclose(ft);
    fclose(fi);
    return 0;
}
