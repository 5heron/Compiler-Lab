%{
 	#include<stdio.h>
 	int vow = 0, con = 0;
%}
%%
[aeiouAEIOU] {vow++;}
[a-zA-Z] {con++;}
. ;
[\n] ;
%%
int yywrap(){
	return 1;
}
int main(){
	yyin = fopen("input.txt","r");
	yylex();
	printf("Number of Vowels     : %d \n", vow);
    printf("Number of Consonants : %d\n", con);
	fclose(yyin);
}

