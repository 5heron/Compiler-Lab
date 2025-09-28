%{
 	#include<stdio.h>
 	int positives = 0,negatives = 0;
%}
%%
-[0-9]+ {negatives++;}
[0-9]+ {positives++;}
. {}
[\n] {}
%%
int yywrap(){
	return 1;
}
int main(){
	yyin = fopen("inputNumbers.txt","r");
	yylex();
	printf("Number of positives   : %d \n",positives);
	printf("Number of negatives   : %d \n",negatives);
	fclose(yyin);
}
