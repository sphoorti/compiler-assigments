/* */
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"y.tab.h"

int line_no=0;

%}
Alphabet [a-zA-Z]
Digit	 [0-9]

%%

"main()"				{return MAIN;}
"if"					{return IF;}
"else"					{return ELSE;}
"for"					{return FOR;}
"while"					{return WHILE;}
"int"|"float"|"char"|"double"		{strcpy(yylval.fchar,yytext);return TYPE;}
[\n]					{line_no++;}
[ \t]+					;
{Digit}+				{yylval.intval=atoi(yytext);return NUMBER;}
{Alphabet}({Alphabet}|{Digit})*		{strcpy(yylval.fchar,yytext);return ID;}
"<"|"<="|">"|">="|"=="|"!="		{return RELOP;}
"++"					{return INC;}
"--"					{return DEC;}
"+"|"-"|"*"|"/"|"="			{return yytext[0];}
.					{return yytext[0];}
%%

int yywrap()
{
	return 1;
}
