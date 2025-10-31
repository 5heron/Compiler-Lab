#include<stdio.h>
#include<string.h>
struct{
    char op, isdead, arg1[10], arg2[10], result[10];
} q[20];
int main(){
    char line[100];
    int n = 0,i;
    FILE *fin = fopen("input.txt", "r");
    while(fgets(line, sizeof(line), fin)){
        if(sscanf(line, "%s = %s %c %s\n",q[n].result, q[n].arg1, &q[n].op, q[n].arg2) != 4)
            if(sscanf(line, "%s %c %s\n", q[n].result, &q[n].op, q[n].arg1)) strcpy(q[n].arg2,"-");
        n++;
    }
    for(int i = 0; i < n; i++){
        if(q[i].op == '=')
            printf("MOV %s,%s\n",q[i].result, q[i].arg1);
        else{
            printf("MOV R0,%s\n",q[i].arg1);
            if(q[i].op == '+') printf("ADD R0,%s\n",q[i].arg2);
            else if(q[i].op == '-') printf("SUB R0,%s\n",q[i].arg2);
            else if(q[i].op == '*') printf("MUL R0,%s\n",q[i].arg2);
            else printf("DIV R0,%s\n",q[i].arg2);
            printf("MOV %s,R0\n",q[i].result);
        }
    }
}