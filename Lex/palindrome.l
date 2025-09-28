%{
 	#include<stdio.h>
 	#include<string.h>
 	void palCheck();
%}
%%
[ \s\n\t] {}
[^ \n\t]* {palCheck();}
%%
int yywrap(){
	return 1;
}
void palCheck(){
	int i = 0, j = strlen(yytext) - 1;
	while(i < j){
		if(yytext[i] != yytext[j]){
			printf("%s is not a palindrome\n", yytext);
			return;
		}
		i++;
		j--;
	}
	printf("%s is a palindrome\n", yytext);
}
int main(){
	yylex();
	fclose(yyin);
}
