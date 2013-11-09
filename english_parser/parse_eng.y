%{
#include<stdio.h>
#include<stdlib.h>

%}
%token Verb Noun Pronoun Conj Adj

%%
sentence : simple	{printf("\nSimple");}
	   |
	   compound	{printf("\nCompound");}
	   ;

simple :  subject Verb object  {printf("\nValid sentence");}
		;

compound : simple Conj simple {printf("\nValid compound sentence");}

subject : Noun
	  |
	  Pronoun
	  ;

object  : Noun
	  ;

%%

int main()
{
	yyparse();

}

int yyerror()
{
	printf("\nError");
}
