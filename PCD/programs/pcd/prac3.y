%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node {
	char name[3];
	struct node *lptr;
	struct node *rptr;
     int no_reg;
     char *code;
     char *reg_name;
     int RightOrLeft;
//struct node *mkleaf(char *s);
};

int count=0;
struct node * mknode(char *s,struct node *lptr, struct node *rptr);
void traverse(struct node *);
void generate_code(struct node *,int );
int max(int,int);

%}

%union
{
     struct node *ptr;
};


%token ID 

%%

S : E '\n'  {  printf("Tree in inorder is:\n");generate_code($<ptr>1,1);printf("\n\n\n");traverse($<ptr>1);}
	| ;

E : E '+' T      {    $<ptr>$ = mknode("+",$<ptr>1,$<ptr>3);  }
     
     | T       {    $<ptr>$ = $<ptr>1;  }
    	;  

T : T '*' F    {    $<ptr>$ = mknode("*",$<ptr>1,$<ptr>3); }

     | F       {    $<ptr>$ = $<ptr>1;  }
     ;
F : ID         {    $<ptr>$ = $<ptr>1;  }
     ;

%%

struct node * mknode(char *s, struct node *lptr,struct node *rptr)
     {
     	struct node *p;
          p = (struct node *)malloc(sizeof(struct node));
          strcpy(p->name,s);
          p->lptr = lptr;
          p->rptr = rptr;
          return p;

     }	

void traverse(struct node *p)
{
     if(p == NULL)
          return;
     printf("%s registers required are %d\n",p->name,p->no_reg);
     traverse(p->lptr);
     traverse(p->rptr);
}


void generate_code(struct node *p,int count){

	
	if(p->lptr==NULL){
		p->no_reg=count;
		return;
	}
	
	generate_code(p->lptr,1);
	generate_code(p->rptr,0);
	
	if(p->lptr->no_reg != p->rptr->no_reg)
		p->no_reg = max(p->lptr->no_reg,p->rptr->no_reg);
	else
		p->no_reg=p->lptr->no_reg+1;
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
