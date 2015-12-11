%{
#include<stdio.h>
%}

%token NOUN PRON VERB ADV ADJ PREP CONJ

%%
sentence : subject VERB object {printf("Sentence is valid.\n");}
	 ;

subject : NOUN 
	| PRON
	;  
object : NOUN
       ;
%%
extern FILE *yyin;

main(){
	do{
		yyparse();
	}while(!feof(yyin));
}
yyerror(char *err){
	fprintf(stdout,"Error is %s",err);
}
