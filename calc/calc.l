/* */
%{
#include<stdio.h>
#include<math.h>
#include"y.tab.h"

%}

Digit	[0-9]
Alphabet	[a-zA-Z]

%%
"sin"|"SIN"			{printf("\nSIN");return SIN;}
"cos"|"COS"			{printf("\nCOS");return COS;}
"tan"|"TAN"			{printf("\nTAN");return TAN;}
"log"|"LOG"			{printf("\nLOG");return LOG;}
{Digit}+\.{Digit}*|{Digit}+	{yylval.val=atof(yytext);return NUMBER;} //atof function
mem				{return MEM;}
clr				{return CLEAR;}
str				{return STORE;}
[ \t]				;
\$				{return 0;}				//terminal element
[\n]				{return yytext[0];}
.				{return yytext[0];}

%%


int yywrap()
{
return 1;
}
