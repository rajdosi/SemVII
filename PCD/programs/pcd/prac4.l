%{
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include "mystruct.h"
#include "y.tab.h"
#include<stdlib.h>
struct abstract_tree * mkleaf(const char *);
#define LOOKUP 0
#define INT 1
#define FLOAT 2



int entry_count=0;
int temp_2;
int state=LOOKUP;
int add_var(int type, char *var);
struct symbol* lookup_var(char *var);

%}
%%
 
" " {;}
"."	{return END;}
;	{state = LOOKUP;}
"int"	{state = INT;}
"float"	{state = FLOAT;}

[+*\n]	{
               return *yytext;	
		}	

[a-zA-Z]+	{
			if(state != LOOKUP){
				add_var(state,yytext);
			}
			else{
				
				char* s;
	               s=(char*)malloc(sizeof(char)*strlen(yytext));
     	          strcpy(s,yytext);
     	          yylval.ptr1 = mkleaf(s);
				
				return ID;
			}
		}         
%%



struct abstract_tree *mkleaf(const char *txt)
{
          struct abstract_tree *p;
          p = (struct abstract_tree *)malloc(sizeof(struct abstract_tree));
          p->node=(char*)malloc(sizeof(char)*strlen(txt+1));
          if(p==NULL){
               printf("malloc");
               exit(1);
          }
          strcat(p->node,txt);
          p->left = NULL;
          p->right = NULL;
         
         return p;
}
     
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
yywrap(){}
