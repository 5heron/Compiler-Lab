%{
 	#include<stdio.h>
 	void prime();
%}
%%
[0-9]+ {prime();}
. ; 
%%
int yywrap(){
	return 1;
}
void prime(){
	int n = atoi(yytext);
	int flag = 0;
	for(int i = 2; i < n / 2; i++){
		if(n % i == 0){
			flag = 1;
			break;
		}
	}
	if(!flag) printf("%d is Prime\n",n);
	else printf("%d is not Prime\n",n);
}
int main(){
	yylex();
	fclose(yyin);
}
