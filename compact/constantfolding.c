#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct quad{
    char arg1[10], arg2[10], op, result[10];
} q[20];
int main(){
    FILE *fin = fopen("input.txt", "r");
    char line[100];
    int n = 0;
    
    while(fgets(line, sizeof(line), fin)){
        if(sscanf(line, " %s = %s %c %s\n", q[n].result, q[n].arg1, &q[n].op, q[n].arg2) != 4)
            if(sscanf(line, " %s %c %s\n", q[n].result, &q[n].op, q[n].arg1)) strcpy(q[n].arg2,"-");
        printf(" %c %s %s %s\n",q[n].op, q[n].arg1, q[n].arg2, q[n].result);
        n++; 
    }

    for(int i = 0; i < n; i++){
        if(isdigit(q[i].arg1[0]) && isdigit(q[i].arg2[0])){
            int a = atoi(q[i].arg1);
            int b = atoi(q[i].arg2);
            int result = 0;
            if(q[i].op == '+')  result = a + b;
            else if(q[i].op == '-') result = a - b;
            else if(q[i].op == '*') result = a * b;
            else if(b) result = a / b;
            sprintf(q[i].arg1, "%d", result);
            q[i].op = '=';
            strcpy(q[i].arg2,"-");  
        }
        if(q[i].op == '=' && isdigit(q[i].arg1[0])){
            for(int j = i + 1; j < n; j++){
                if(strcmp(q[i].result, q[j].arg1) == 0) strcpy(q[j].arg1, q[i].arg1);
                if(strcmp(q[i].result, q[j].arg2) == 0) strcpy(q[j].arg2, q[i].arg1);
                if(strcmp(q[i].result, q[j].result) == 0) break;
            }
        }
    }
    printf("optimized\n\n");
    for(int i = 0; i < n; i++)
        printf(" %c %s %s %s\n",q[i].op, q[i].arg1, q[i].arg2, q[i].result);
}