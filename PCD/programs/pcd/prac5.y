%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "y.tab.h"
#include "mystruct.h"
extern int yylex();
struct node{
	struct node *left,*right;
	char name[10];
};
struct node * mknode(char *,struct node *,struct node *);
void traverse(struct node *);
bool lookup_var_from_entry(struct symbol* input);
bool flag=true;
%}
%union
{
     struct symbol *ptr;
};


%token ID
%token END

%%

	START:	S START
		| 
	;
	
	S:	E END	{if(flag){printf("SUCCESS\n");} else{printf("FAIL\n");}flag=true;;}
	;

	E: E '+' T 		{if(flag){if(type_of_symbol($<ptr>1,$<ptr>3)==false){printf("Mismatch Type\n");flag = false;}else {$<ptr>$=$<ptr>1;}};}
		|T		{if(flag){$<ptr>$=$<ptr>1;};}
		;
	T: T '*' F		{if(flag){if(type_of_symbol($<ptr>1,$<ptr>3)==false){printf("Mismatch Type\n");flag = false;}else {$<ptr>$=$<ptr>1;}};}
		|F		{if(flag){$<ptr>$=$<ptr>1;};}
		;
	F: ID		{if(lookup_var_from_entry($<ptr>1)==false){printf("Undefined symbol\n");flag = false;}else {$<ptr>$=$<ptr>1;};}
	
		
%%

main(){
	yyparse();

}
yyerror(char *err){
	fprintf(stdout,"Error is in  %s",err);
}


bool lookup_var_from_entry(struct symbol * input){

	if(input==NULL){
		return false;
	}
	return true;
}


bool type_of_symbol(struct symbol* input_1,struct symbol* input_2){

	if(input_1->var_type!=input_2->var_type){
			return false;
	}
	return true;
}




struct node * mknode(char *str,struct node *lptr,struct node *rptr){
	struct node *node_1=(struct node *)malloc(sizeof(struct node));
	node_1->left=lptr;
	node_1->right=rptr;
	strcpy(node_1->name,str);
	return node_1;
}

void  traverse(struct node *a){
	if(a == NULL)
		return;
	printf("%s\n", a->name);
	traverse(a->left);
	traverse(a->right);
}
