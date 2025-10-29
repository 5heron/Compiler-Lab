#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char result[10];
    char arg1[10];
    char op; 
    char arg2[10];
} Quadruple;

// Check if a string is a number
int isNumber(char *str) {
    for (int i = 0; str[i]; i++)
        if (!isdigit((unsigned char)str[i])) return 0;
    return 1;
}

int main() {
    FILE *fin, *fout;
    fin = fopen("inputExpressions.txt", "r");
    fout = fopen("opt1code.txt", "w");
    if (!fin) {
        printf("Error: Could not open input file\n");
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

    // Constant folding & propagation
    for(int i=0;i<n;i++){
        if(isNumber(q[i].arg1) && isNumber(q[i].arg2)){
            int val1 = atoi(q[i].arg1);
            int val2 = atoi(q[i].arg2);
            int res = 0;
            switch(q[i].op){
                case '+': res=val1+val2; break;
                case '-': res=val1-val2; break;
                case '*': res=val1*val2; break;
                case '/': res=val2? val1/val2:0; break;
            }
            sprintf(q[i].arg1,"%d",res);
            strcpy(q[i].arg2,"-");
            q[i].op='=';
        }
        // propagate constants
        if (q[i].op == '=' && isNumber(q[i].arg1)) {
            for(int j=i+1;j<n;j++){
                if(strcmp(q[i].result,q[j].arg1)==0) strcpy(q[j].arg1,q[i].arg1);
                if(strcmp(q[i].result,q[j].arg2)==0) strcpy(q[j].arg2,q[i].arg1);
                if(strcmp(q[i].result,q[j].result)==0) break; //
            }
        }
    }

    // Output optimized code
    printf("Optimized Intermediate Code:\n");
    printf("%-9s %-9s %-9s %-9s\n", "Operator", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------\n");
    for(int i=0;i<n;i++){
        printf("%-9c %-9s %-9s %-9s\n", q[i].op, q[i].arg1, q[i].arg2, q[i].result);
        fprintf(fout, "%-9c %-9s %-9s %-9s\n", q[i].op, q[i].arg1, q[i].arg2, q[i].result);
    }
    return 0;
}