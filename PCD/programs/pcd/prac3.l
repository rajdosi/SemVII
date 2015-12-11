%{
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include "y.tab.h"
#include<stdlib.h>
struct node * mkleaf(const char *);

%}
%%
[+*\n]	{
               return *yytext;	
		}		
[a-z]+    {
               char* s;
               s=(char*)malloc(sizeof(char)*strlen(yytext));
               strcpy(s,yytext);
               yylval.ptr = mkleaf(s);
               return ID;
          }
          
%%

struct node{
     char name[3];
     struct node *lptr, *rptr;
};

struct node *mkleaf(const char *txt)
     {
          struct node *p;
          printf("size of struct %ld\n", sizeof(struct node));
          p= (struct node *)malloc(sizeof(struct node));
           if(p==NULL){
               printf("malloc");
               exit(1);
          }
          strcpy(p->name,txt);
          p->lptr = NULL;
          p->rptr = NULL;
         
         return p;
     }
yywrap(){}
