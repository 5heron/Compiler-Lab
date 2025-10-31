#include<stdio.h>
char input[100];
int i = 0;
int S();
int A();
int B();
int match(char c){
    if(input[i] == c){
        i++;
        return 1;
    }
    return 0;
}
//S->aA
int S(){
    if(match('a')){
        if(A())
            return 1;
    }
    return 0;
}
//A->bB | #
int A(){
    if(match('b')){
        if(B())
            return 1;
        return 0;
    }
    return 1;
}

int B(){
    if(match('c'))
        return 1;
    return 0;
}

int main(){
    printf("Enter the input string :");
    scanf("%s", input);
    if(S() && input[i] == '\0')
        printf("%s Accepted\n",input);
    else
        printf("%s Rejected\n",input);
}
