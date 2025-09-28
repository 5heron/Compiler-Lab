%{
 	#include<stdio.h>
 	int l = 0,s = 0,t = 0;
%}
%%
[\n] {l++;}
[ ] {s++;}
[\t] {t++;}
. {}
%%
int yywrap(){
	return 1;
}
int main(){
	yyin = fopen("input.txt","r");
	yylex();
	printf("Number of lines   : %d \n",l);
	printf("Number of spaces  : %d \n",s);
	printf("Number of tabs    : %d \n",t);
	fclose(yyin);
}
