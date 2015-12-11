%{
#include<stdlib.h>
#include "y.tab.h"
#define LOOKUP 0
/*enum {LOOKUP = 0, TYPE, VAR};*/
int state;
int add_word(int type, char *word);
int lookup_word(char *word);
void disp();
%}
%%
\n	{state = LOOKUP;}
","	{return ',';}
;\n	{state = LOOKUP; return 0;}
^type	{state = TYPE;}
^var	{state = VAR;}
^show	{disp();}
[a-zA-Z]+	{
			if(state != LOOKUP){
				add_word(state,yytext);
			}
			else{
				switch(lookup_word(yytext)){
					case TYPE:
						return(TYPE);
					case VAR:
						return(VAR);
					default:
						printf("%s : Unrecognized text\n",yytext); break;	
				}
			}
		}		
%%
struct word{
	char *word_name;
	int word_type;
	struct word *next;
}*temp;
struct word *word_list=NULL;
int add_word(int type, char *word){
	struct word *wp;
	if(lookup_word(word) != LOOKUP){
		printf("%s word already exist!", word);
		return(0);
	}	
		wp = (struct word*)malloc(sizeof(struct word));
		wp->word_type = state;
		wp->word_name = (char *)malloc(strlen(word)+1);
		strcpy(wp->word_name,word);
	 	wp->next = word_list;	
		word_list = wp;
		return(1);	
}

void disp(){
    if(word_list==NULL){
        printf("No entry");
    }
    else{
      temp=word_list;
      while(temp!=NULL){
        printf("\nWord type:%d Word:%s",temp->word_type,temp->word_name);
        temp = temp->next;
      } 
    }   
}

int lookup_word(char *word){
	struct word *wp=word_list;
	for(;wp;wp=wp->next){
		if(strcmp(wp->word_name,word)==0)
			return(wp->word_type);	
	}
	return(LOOKUP);
}
/*
main(){
	yylex();
}*/
