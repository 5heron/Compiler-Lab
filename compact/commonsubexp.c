#include<stdio.h>
#include<string.h>
#include<ctype.h>
struct{
    char arg1[10], arg2[10], op, result[10], dead;
} q[20];
int main(){
    char line[100];
    int n = 0, i;
    FILE *fin = fopen("input.txt", "r");
    while(fgets(line, sizeof(line), fin)){
        if(sscanf(line, "%s = %s %c %s\n", q[n].result, q[n].arg1, &q[n].op, q[n].arg2) != 4)
            if(sscanf(line, "%s %c %s\n", q[n].result, &q[n].op, q[n].arg1)) strcpy(q[n].arg2, "-");
        q[n].dead = '0';
        printf("%c %s %s %s\n",q[n].op, q[n].arg1, q[n].arg2, q[n].result);
        n++;
    }
    for(i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(strcmp(q[i].arg1, q[j].arg1) == 0 && strcmp(q[i].arg2, q[j].arg2) == 0 && q[i].op == q[j].op){
                for(int k = j + 1; k < n; k++){
                    if(strcmp(q[k].arg1, q[j].result) == 0) strcpy(q[k].arg1, q[i].result);
                    if(strcmp(q[k].arg2, q[j].result) == 0) strcpy(q[k].arg2, q[i].result);
                    if(strcmp(q[i].result, q[k].result) == 0 || strcmp(q[j].result, q[k].result) == 0) break;
                    if(strcmp(q[k].result, q[i].arg1) == 0 || strcmp(q[k].result, q[i].arg2) == 0) break;
                }
                q[j].dead = '1';
            }
            if(strcmp(q[j].result, q[i].arg1) == 0 || strcmp(q[j].result, q[i].arg2) == 0) break;
            if(strcmp(q[i].result, q[j].result) == 0) break;
        }
    }
    printf("optimized\n\n");
    for(int i = 0; i < n; i++)
        if(q[i].dead == '0')printf(" %c %s %s %s\n",q[i].op, q[i].arg1, q[i].arg2, q[i].result);
}