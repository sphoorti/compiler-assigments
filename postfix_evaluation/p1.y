%{
#include<stdio.h>
%}
%union
{
	int val;
}

%token <val>NUM
%type <val>E
%left '+' '-'
%left '*' '/'
%right NEGATIVE

%%
S:  E {printf("\nResult is %d",$1);}
    ;
E:  E '+' E {$$=$1+$3;printf("+");}
    |   E '*' E {$$=$1*$3;printf("*");}
    |   E '-' E {$$=$1-$3;printf("-");}
    |   E '/' E {$$=$1/$3;printf("/");}
    |   '(' E ')'{$$=$2;}
    |   '-' E %prec NEGATIVE {$$=-$2;printf("-");}
    |   NUM     {$$=$1;printf("%d", yylval);}
    ;
%%

int main(){
    yyparse();
}

int yyerror (char *msg) {
    return printf ("error YACC: %s\n", msg);
}
