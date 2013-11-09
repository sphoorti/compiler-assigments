/* */
%{
#include<stdio.h>
#include<stdlib.h>

FILE *fp;
%}

%x CMT
%x SC

%%

"//"			BEGIN SC;
<SC>.			;
<SC>\n			BEGIN INITIAL;
"/*"			BEGIN CMT;
<CMT>.|<CMT>\n		;
<CMT>"*/"		BEGIN INITIAL;
.|\n			{fprintf(fp,"%s",yytext);}

%%

int main()
{
	FILE *in;

	fp=fopen("output.txt","w");
	
	in=fopen("input.txt","r");
	yyin=in;

	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}

