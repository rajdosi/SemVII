%{
#include<stdlib.h>
#include "y.tab.h"
#define LOOKUP 0
/*enum {LOOKUP = 0, VERB, NOUN, ADJ, ADV,PREP,PRON,CONJ};*/
int state;
int add_word(int type, char *word);
int lookup_word(char *word);
%}
%%
\n	{state = LOOKUP;}
\.\n	{state = LOOKUP; return 0;}
^verb	{state = VERB;}
^adj	{state = ADJ;}
^adv	{state = ADV;}
^noun	{state = NOUN;}
^prep	{state = PREP;}
^pron	{state = PRON;}
^conj	{state = CONJ;}
[a-zA-Z]+	{
			if(state != LOOKUP){
				add_word(state,yytext);
			}
			else{
				switch(lookup_word(yytext)){
					case VERB:
						return(VERB);
					/*	printf("%s : verb\n",yytext); break;	*/
					case ADJ:
						return(ADJ);
					/*	printf("%s : Adjective\n",yytext); break; */
					case ADV:
						return(ADV);
					/*	printf("%s : Adverb\n",yytext); break;	*/
					case NOUN:
						return(NOUN);
					/*	printf("%s : Noun\n",yytext); break;	*/
					case PREP:
						return(PREP);
					/*	printf("%s : Preposition\n", yytext); break;	*/
					case PRON:
						return(PRON);
					/*	printf("%s : Pronoun\n", yytext); break;	*/
					case CONJ:
						return(CONJ);
					/*	printf("%s : Conjunction\n",yytext); break;	*/
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
};
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
