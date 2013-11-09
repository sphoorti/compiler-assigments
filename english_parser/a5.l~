/* */
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"y.tab.h"


enum 
{
	LOOKUP=0,VERB,NOUN,PRONOUN,CONJ,ADJ
};

int add_word(int ,char *);
int lookup_word(char []);

int state;
%}

%%
[\n] {state = LOOKUP;}
^verb	{state = VERB;}
^noun	{state = NOUN;}
^pronoun	{state = PRONOUN;}
^adj	{state = ADJ;}
^conj	{state = CONJ;}

[a-zA-Z]+	{
			if(state != LOOKUP)
			{
				add_word(state,yytext);
			}
			else
			{
				switch(lookup_word(yytext))
				{
					case VERB : printf("\n%s - Verb",yytext); return Verb; break;
					case NOUN : printf("\n%s - Noun",yytext); return Noun;break;
					case PRONOUN : printf("\n%s - Pronoun",yytext);return Pronoun;break;
					case ADJ : printf("\n%s - Adjective",yytext);return Adj;break;
					case CONJ : printf("\n%s - Conjunction",yytext);return Conj;break;
					default : printf("\nUnrecognized word"); break;
	
				}
			}
		

		}

.  	{;}

%%


struct word
{
	char word_name[10];
	int word_type;
	struct word *next;
};

struct word *word_list=NULL;

extern void *malloc();

int add_word(int type,char word[])
{
	struct word *wp;
	
	if(lookup_word(word)!= LOOKUP)
	{
		printf("\n%s is defined",word);
		return 0;	
	}
	else
	{
		if(word_list==NULL)
		{
			word_list = (struct word *)malloc(sizeof(struct word));
			strcpy(word_list->word_name,word);
			word_list->word_type=type;
			word_list->next=NULL;
		}		
		else
		{
			
			wp = (struct word *)malloc(sizeof(struct word));
			strcpy(wp->word_name,word);
			wp->word_type=type;
			wp->next=word_list;
			word_list=wp;
			return 1;
	
		}
		
		
	}

}

int lookup_word(char word[])
{
	struct word *wp = word_list;
	
	for(; wp; wp = wp->next)
	{
		if(strcmp(wp->word_name,word)==0)
			return wp->word_type;
	}

	return LOOKUP;	/*not found*/
}


int yywrap()
{
	return 1;
}
