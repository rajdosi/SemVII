%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mystruct.h"

int count=0,nameOfreg=1;
struct abstract_tree * mknode(char s,struct abstract_tree *lptr, struct abstract_tree *rptr);
//struct node *mkleaf(char *s);
void traverse(struct abstract_tree *);
void generate_code(struct abstract_tree *,int );
int max(int,int);

%}

%union
{
     struct abstract_tree *ptr1,*ptr2;
};


%token ID
%token END

%%

S : E '\n'  {  printf("abstract_tree in inorder is:\n");generate_code($<ptr1>1,1);printf("\n");traverse($<ptr1>1);}
	| ;

E : E '+' T      {    $<ptr1>$ = mknode('+',$<ptr1>1,$<ptr1>3);  }
     
     | T       {    $<ptr1>$ = $<ptr1>1;  }
    	;  

T : T '*' F    {    $<ptr1>$ = mknode('*',$<ptr1>1,$<ptr1>3); }

     | F       {    $<ptr1>$ = $<ptr1>1;  }
     ;
F : ID         {    $<ptr1>$ = $<ptr1>1;  }
     ;

%%

struct abstract_tree * mknode(char s, struct abstract_tree *lptr,struct abstract_tree *rptr)
     {
     	struct abstract_tree *p;
          p = (struct abstract_tree *)malloc(sizeof(struct abstract_tree));
	     p->node=(char*)malloc(sizeof(char)*2);
          p->node[0]=s;
          p->node[1]='\0';
          p->left = lptr;
          p->right = rptr;
          return p;

     }	

void traverse(struct abstract_tree *p)
{
     if(p == NULL)
          return;
     
     printf("%s  %d  %s  %s\n",p->node,p->no_reg,p->name_reg,p->code);
     traverse(p->left);
     traverse(p->right);

}


void generate_code(struct abstract_tree *p,int count){

	
	if(p->left==NULL){
	
		if(count!=0){
			p->name_reg[0]='R';
			char temp[2];
			sprintf(temp,"%d",nameOfreg);
			strcat(p->name_reg,temp);
			nameOfreg++;
			p->lines_code=1;
			strcpy(p->code,"MOV ");
			strcat(p->code,p->name_reg);
			strcat(p->code," ");
			sprintf(temp,"%s",p->node);
			strcat(p->code,temp);
			strcat(p->code,". ");
		}
		else{
			strcpy(p->name_reg,p->node);
			p->lines_code=0;
		}
		
		p->no_reg=count;
		return;
	}
	
	generate_code(p->left,1);
	generate_code(p->right,0);
	
	if(p->left->no_reg != p->right->no_reg){
		p->no_reg = max(p->left->no_reg,p->right->no_reg);
	}
	else{
		p->no_reg=p->left->no_reg+1;
	}	strcpy(p->name_reg,p->left->name_reg);
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
	strcat(p->code,p->left->name_reg);
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


main(){
	yyparse();
}

yyerror(char *err){
	fprintf(stdout,"Error is %s",err);
}
