/* */
%{
#include<stdio.h>
#include<math.h>

double memory;

%}

%union
{
	double val;
}

%token SIN COS TAN LOG CLEAR STORE

%token <val>NUMBER
%token <val>MEM

%type <val>E

%left '-' '+'
%left '*' '/'

%left SIN COS TAN 

%nonassoc UNIMINUS

%%

Statement : E '\n'		    {printf("\nExpression evaluated %g ",$1);}
	  |
	    Statement E '\n'        {printf("\nExpression evaluated %g ",$2);}
	  |
	   MEM '=' E '\n'           {memory=$3;printf("\nMemory %g ",memory);}
	  |
           Statement MEM '=' E '\n' {memory=$4;printf("\nExpression evaluated %g ",$4);}
          |
           Statement CLEAR '\n'		{memory=0;printf("\nMemory %g ",memory);}
           ;


E : E '+' E		{$$=$1+$3;}
    |
    E '-' E		{$$=$1-$3;}
    |
    E '*' E		{$$=$1*$3;}
    |
    E '/' E		{
				if($3==0)
				{
					yyerror("divide by zero");
				}
				else
					$$=$1/$3;
			}
    |
    '(' E ')'		{$$=$2;}
    |	
    '-' E		%prec UNIMINUS{$$=-$2;}
    |
    SIN E               {$$=sin($2 * 3.1412/180);}
    |
    COS E               {$$=cos($2 * 3.1412/180);}
    |
    TAN E               {$$=tan($2 * 3.1412/180);}
    |
    NUMBER		{$$=$1;}
    |
    MEM			{$$=memory;}	//memory
    ;


%%

int main()
{
	yyparse();
}


int yyerror()
{
	printf("\nError at line %d");
}
