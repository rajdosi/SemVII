%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mystruct.h"

int IsAssign=1,nameOfreg=1;
struct abstract_tree * mknode(char s,struct abstract_tree *lptr, struct abstract_tree *rptr);
void traverse(struct abstract_tree *);
void generate_code(struct abstract_tree *,int );
int max(int,int);
void add_code(char * );
extern int yylex();
char temp_code[40];

bool flag=true;

%}

%union
{
     	struct abstract_tree *ptr_tree;
};


%token ID
%token END
%token IF
%token ELSE
%token WHILE
%token FOR
%token DIGIT

%%

	MAIN:	'{' START '}'	{	fclose(symbol_table);
					fclose(abstract_tree);
					fclose(code);
				;}	
	;

	START:	EXPRESSION  START
		| COMPARE	{if(if_depth_count==0) depth_count=0;	;}	START
		| LOOP_WHILE 		{if(while_depth_count==0) depth_count=0;	;}START
		|
	;
	
	
	LOOP_WHILE :	WHILE '('{	strcpy(temp_code,"Lable_");
				char temp[3];
				sprintf(temp,"%d",lable_count++);
				//depth_count++;
				strcat(temp_code,temp);
				strcat(temp_code," :");
				strcat(temp_code,". \0");
				add_code(temp_code);	
			;}
			 CONDITION {
					strcat(temp_code,", ");
					strcat(temp_code,"Lable_exit_");
					char temp[3];
					sprintf(temp,"%d",lable_exit_count);
					strcat(temp_code,temp);
					strcat(temp_code,". \0");
					add_code(temp_code);
					while_depth_count++;
					;} 
					')' '{' START {	
							strcpy(temp_code,"JMP ");
							strcat(temp_code,"Lable_");
							char temp[3];
							sprintf(temp,"%d",lable_count-depth_count-1);
							depth_count++;
							strcat(temp_code,temp);
							strcat(temp_code,". \0");
							add_code(temp_code); 
							strcpy(temp_code,"Lable_exit_");
							sprintf(temp,"%d",lable_exit_count++);
							strcat(temp_code,temp);
							strcat(temp_code," :");
							strcat(temp_code,". \0");
							add_code(temp_code); 
							add_code(". \0");
							;}
							'}'
	
	
	
	;
	COMPARE: IF '(' CONDITION	{
					strcat(temp_code,", ");
					strcat(temp_code,"Lable_");
					char temp[3];
					sprintf(temp,"%d",lable_count++);
					strcat(temp_code,temp);
					strcat(temp_code,". \0");
					add_code(temp_code);
					if_depth_count++;
					;} 
					')' '{' START 	{strcpy(temp_code,"JMP ");
							strcat(temp_code,"Lable_exit_");
							char temp[3];
							sprintf(temp,"%d",lable_exit_count);
							strcat(temp_code,temp);
							strcat(temp_code,". \0");
							add_code(temp_code); 
							add_code(". \0");
							;}
							'}'
							{strcpy(temp_code,"Lable_");
							char temp[3];
							sprintf(temp,"%d",lable_count-depth_count-1);
							depth_count++;
							strcat(temp_code,temp);
							strcat(temp_code," :");
							strcat(temp_code,". \0");
							add_code(temp_code); 
							;} 
							else_statement	{if_depth_count--;	;}
								
	;
	
	else_statement: ELSE COMPARE
			|ELSE '{' START '}'		{add_code(". \0");
							strcpy(temp_code,"Lable_exit_");
							char temp[3];
							sprintf(temp,"%d",lable_exit_count++);
							strcat(temp_code,temp);
							strcat(temp_code," :");
							strcat(temp_code,". \0");
							add_code(temp_code); 
							;}	
			|				{add_code(". \0");
							strcpy(temp_code,"Lable_exit_");
							char temp[3];
							sprintf(temp,"%d",lable_exit_count++);
							strcat(temp_code,temp);
							strcat(temp_code," :");
							strcat(temp_code,". \0");
							add_code(temp_code); 
							;}
	
	;
	
	CONDITION : E '>' E	{	strcpy(temp_code,"JMPLE ");
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>3->node);
				
				;}
		|E '<' E	{	strcpy(temp_code,"JMPGE ");
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>3->node);
					
				;}
		|E '>''=' E	{	strcpy(temp_code,"JMPL ");	
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>4->node);
				
				;}
		|E '<''=' E	{	strcpy(temp_code,"JMPG ");
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>4->node);
						
				;}
		|E '=''=' E	{	strcpy(temp_code,"JMPNE ");
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>4->node);
					
				;}
		|E '!''=' E	{	strcpy(temp_code,"JMPE ");
					strcat(temp_code,$<ptr_tree>1->node);
					strcat(temp_code,", ");
					strcat(temp_code,$<ptr_tree>4->node);
					
				;}
		|E		{	strcpy(temp_code,"JMPZ ");
					strcat(temp_code,$<ptr_tree>1->node);
					
				;}
		|
	
	;
	
	EXPRESSION:	ID '=' E END	{if(flag){
						if(type_of_symbol($<ptr_tree>1,$<ptr_tree>3)==false){
							printf("%s should be %s.\n",$<ptr_tree>1->node,$<ptr_tree>3->data_type);
							flag = false;
						}else {
							$<ptr_tree>$ = mknode('=',$<ptr_tree>1,$<ptr_tree>3);
							generate_code($<ptr_tree>$,1);
							traverse($<ptr_tree>$);
							fprintf(abstract_tree,"\n\n");
							strcat($<ptr_tree>$->code,"\0");
							add_code($<ptr_tree>$->code);
						}						
					} else{
						printf("FAIL\n");
					}
					flag=true;
					nameOfreg=1;
					IsAssign=1;
					;}
	;
	E: E '-' T 		{if(flag){
						if(type_of_symbol($<ptr_tree>1,$<ptr_tree>3)==false){
							printf("%s should be %s.\n",$<ptr_tree>3->node,$<ptr_tree>1->data_type);
							flag = false;
						}else {
							$<ptr_tree>$ = mknode('-',$<ptr_tree>1,$<ptr_tree>3);
						}
					}
				;}
		|T		{if(flag)	$<ptr_tree>$ = $<ptr_tree>1;	;}
		;

	T: T '+' F		{if(flag){
						if(type_of_symbol($<ptr_tree>1,$<ptr_tree>3)==false){
							printf("%s should be %s.\n",$<ptr_tree>3->node,$<ptr_tree>1->data_type);
							flag = false;
						}else {
							$<ptr_tree>$ = mknode('+',$<ptr_tree>1,$<ptr_tree>3);
						}
					};
				}
	|F		{if(flag)	$<ptr_tree>$ = $<ptr_tree>1;	;}
		;
	F: F '*' U 		{if(flag){
						if(type_of_symbol($<ptr_tree>1,$<ptr_tree>3)==false){
							printf("%s should be %s.\n",$<ptr_tree>3->node,$<ptr_tree>1->data_type);
							flag = false;
						}else {
							$<ptr_tree>$ = mknode('*',$<ptr_tree>1,$<ptr_tree>3);
						}
					}
				;}
	|U		{if(flag)	$<ptr_tree>$ = $<ptr_tree>1;	;}
		;

	U: U '/' V		{if(flag){
						if(type_of_symbol($<ptr_tree>1,$<ptr_tree>3)==false){
							printf("%s should be %s.\n",$<ptr_tree>3->node,$<ptr_tree>1->data_type);
							flag = false;
						}else {
							$<ptr_tree>$ = mknode('/',$<ptr_tree>1,$<ptr_tree>3);
						}
					};
				}
	|V		{if(flag)	$<ptr_tree>$ = $<ptr_tree>1;	;}
		;
 
	V: ID		{	$<ptr_tree>$ = $<ptr_tree>1;	;}
	
		

%%

struct abstract_tree * mknode(char s, struct abstract_tree *lptr,struct abstract_tree *rptr)
     {
     	struct abstract_tree *p;
          p = (struct abstract_tree *)malloc(sizeof(struct abstract_tree));
	  p->node=(char*)malloc(sizeof(char)*2);
          p->node[0]=s;
          p->node[1]='\0';
          
	  p->type=lptr->type;
	  strcpy(p->data_type,lptr->data_type);
	  
          p->left = lptr;
          p->right = rptr;
          return p;

     }	

void traverse(struct abstract_tree *p)
{
     if(p == NULL)
          return;
     
     fprintf(abstract_tree,"%s  %d  %s  %s\n",p->node,p->no_reg,p->name_reg,p->code);
     traverse(p->left);
     traverse(p->right);

}

void add_code(char * input){
	
	fclose(code);
	code=fopen("code.txt","a");
	int i=0;
	while(input[i]!='\0'){
		
		if(input[i]=='.'){
			fprintf(code,"\n");
			i=i+2;
			continue;
		}
		fprintf(code,"%c",input[i]);
		i++;
	}	
}

void generate_code(struct abstract_tree *p,int count){

	
	if(p->left==NULL){
	
		if(count!=0){
			if(IsAssign==1){
				strcpy(p->name_reg,p->node);	
				p->no_reg=0;
				IsAssign=0;
			}
			else{
				sprintf(p->name_reg,"R%d",nameOfreg);
				nameOfreg++;
				p->lines_code=1;

				strcpy(p->code,"MOV ");
				strcat(p->code,p->name_reg);
				strcat(p->code,",");
				strcat(p->code," ");
				char temp_2[10];
				sprintf(temp_2,"%s",p->node);
				strcat(p->code,temp_2);
				strcat(p->code,". ");
				p->no_reg=count;
			}
		}
		else{
			
			//strcpy(p->name_reg,"");
			strcpy(p->name_reg,p->node);	
			p->lines_code=0;
			p->no_reg=count;
		}
		
		return;
	}
	
	generate_code(p->left,1);
	generate_code(p->right,0);
	
	if(p->left->no_reg != p->right->no_reg){
		p->no_reg = max(p->left->no_reg,p->right->no_reg);
	}
	else{
		p->no_reg=p->left->no_reg+1;
	}	
	strcpy(p->name_reg,p->left->name_reg);
	p->lines_code=p->left->lines_code+p->right->lines_code+1;
	strcat(p->code,p->left->code);
	strcat(p->code,p->right->code);
	if(!strcmp(p->node,"*"))
		strcat(p->code,"MUL ");
	else if(!strcmp(p->node,"+"))
		strcat(p->code,"ADD ");
	else if(!strcmp(p->node,"-"))
		strcat(p->code,"SUB ");
	else if(!strcmp(p->node,"/"))
		strcat(p->code,"DIV ");
	else if(!strcmp(p->node,"="))
		strcat(p->code,"MOV ");
	strcat(p->code,p->left->name_reg);
	strcat(p->code,",");
	strcat(p->code," ");
	strcat(p->code,p->right->name_reg);
	strcat(p->code,". ");
}

int max(int i,int j){

	if(i>=j)
		return i;
	else
		return j;
}

bool type_of_symbol(struct abstract_tree* input_1,struct abstract_tree* input_2){

	if(input_1->type!=input_2->type){
			return false;
	}
	return true;
}




main(){
	symbol_table=fopen("symbol_table.txt","w");
	abstract_tree=fopen("abstract_tree.txt","w");
	code=fopen("code.txt","w");
	code=fopen("code.txt","a");
	yyparse();
}

yyerror(char *err){
	fclose(symbol_table);
	fclose(abstract_tree);
	fclose(code);
	fprintf(stdout,"Error in %s",err);
}
