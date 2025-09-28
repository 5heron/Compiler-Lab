%{
 	#include<stdio.h>
 	void odd_even();
%}
%%
[0-9]+ {odd_even();}
. ; 
%%
int yywrap(){
	return 1;
}
void odd_even(){
	int n = atoi(yytext);
	if(n % 2 == 0) printf("%d is Even\n",n);
	else printf("%d is Odd\n",n);
}
int main(){
	yylex();
	fclose(yyin);
}
