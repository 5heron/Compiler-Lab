#include<string.h>
#include<stdio.h>

struct{
    char lhs,rhs[20];
}prods[20];

int main(){
    int n, i, choice, top = -1;
    char stack[100], input[100];
    printf("Enter the no of prods : ");
    scanf("%d",&n);
    printf("Enter the prods (E->E+E):\n");
    for(i = 0; i < n; i++)
        scanf(" %c->%s", &prods[i].lhs,prods[i].rhs);
    
    do{
        i = 0;
        printf("Enter the input string :");
        scanf("%s",input);
        strcpy(stack, "$");
        top++;
        strcat(input, "$");
        while(1){
            stack[++top] = input[i++];
            stack[top + 1] = '\0';
            printf("%-20s %-20s Shift\n",stack, input);
            int reduced = 1;
            while(reduced){
                reduced = 0;
                for(int j = 0; j < n; j++){
                    int len = strlen(prods[j].rhs);
                    if(strncmp(stack + top - len + 1, prods[j].rhs, len) == 0){
                        top = top - len + 1;
                        stack[top] = prods[j].lhs;
                        stack[top + 1] = '\0';
                        reduced = 1;
                        printf("%-20s %-20s Reduce\n",stack, input);
                        break;
                    }
                }
            }
            if(input[i] == '$' && top == 1 && stack[top] == prods[0].lhs){
                printf("%s accepted\n",input);
                break;
            }
            if(input[i] == '$'){
                printf("%s rejected\n",input);
                break;
            }
        }
        printf("1:continue 2:exit :");
        scanf("%d",&choice);
    }while(choice != 2);
}