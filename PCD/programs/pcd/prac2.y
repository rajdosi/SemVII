%{
#include<stdio.h>
%}

%token TYPE VAR

%%
input	:	TYPE varlist 	{printf("VALID SENTENCE\n");}
		;
varlist	: 	VAR','varlist | VAR ;

%%
extern FILE *yyin;

main(){
	do{
		yyparse();
	}while(!feof(yyin));
}
yyerror(char *err){
	fprintf(stdout,"Error is %s\n",err);
}
