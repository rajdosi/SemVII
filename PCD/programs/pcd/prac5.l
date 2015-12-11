%{
#include<stdlib.h>
#include "y.tab.h"
#include "mystruct.h"
#define LOOKUP 0
#define INT 1
#define FLOAT 2


struct symbol * mkleaf(char *);
int entry_count=0;
int temp_2;
int state=LOOKUP;
int add_var(int type, char *var);
struct symbol* lookup_var(char *var);

%}

%%

" " {;}
"."	{return END;}
\n {;}
[+*] {return *yytext;}
;	{state = LOOKUP;}
^int	{state = INT;}
^float	{state = FLOAT;}

[a-zA-Z]+	{
			if(state != LOOKUP){
				add_var(state,yytext);
			}
			else{
				
				yylval.ptr=lookup_var(yytext);
				return ID;
			}
		}		
%%

int add_var(int type, char *var){
	struct symbol *temp;
	if(lookup_var(var) != NULL){
		printf("%s var already exist!", var);
		return(0);
	}	
		temp = (struct symbol*)malloc(sizeof(struct symbol));
		temp->var_type = state;
		temp->var_name = (char *)malloc(strlen(var)+1);
		temp->entry=entry_count++;
		strcpy(temp->var_name,var);
	 	temp->next = head;	
		head = temp;
		return(1);	
}
struct symbol* lookup_var(char *var){
	struct symbol *temp=head;
	for(;temp;temp=temp->next){
		if(strcmp(temp->var_name,var)==0){
			return(temp);	
			}
	}
	return(NULL);
}
