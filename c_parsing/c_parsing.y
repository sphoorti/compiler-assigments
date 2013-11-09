/* */
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern FILE *yyin;
extern int line_no;

struct symtab
{
	int val;
        char type[10];
	char sym[10];
};

struct symtab s[10];

int sym_no=0;	//count of entries

void add_sym(char *, int );
void add_type(char *);
void display();


%}

%union
{
	int intval;
	char fchar[10];
}


%token MAIN IF ELSE FOR WHILE RELOP DEC INC
%token <fchar>ID 
%token <intval>NUMBER	
%token <fchar>TYPE


%%
Program : MAIN	Block		{printf("\nSuccessful implementation");}
	  ;

Block   : '{' Code '}'
	  ;

Code    : Statement
	 |
	  Statement Code
	 ;

Statement : Declarative ';'
	  |
	    Conditional
	  |
	    While
	  |
	    For
	  |
	    Assignment ';'
          ;

Declarative : TYPE Varlist	{printf("\n%s",$1);add_type($1);}
	   ;

Varlist   : ID ','  Varlist	{printf("\n%s",$1);add_sym($1,0);}
	   |	
	    ID			{printf("\n%s",$1);add_sym($1,0);}
	   |
	    ID '=' NUMBER ',' Varlist    {add_sym($1,$3);}  
	   |
            ID '=' NUMBER	{add_sym($1,$3);}
	   ;

Assignment : ID '=' NUMBER 
	    |
	     ID '=' ID 
	    ;

Conditional : IFST
	    |
	      ELST
	    ;

cond  : ID RELOP ID
	|
	ID RELOP NUMBER
	;

incdec : ID INC	{printf("\nIncrement");}
	|
	 ID DEC	{printf("\nDecrement");}
	 ;

While 	   : WHILE '(' E ')' Block	{printf("\nWHILE statement");}
	     ;

E : ID RELOP ID
   |		
    ID RELOP NUMBER
   |
    ID
   |
    NUMBER
    ;

For :  FOR '(' Assignment ';' cond ';' incdec ')' Block	{printf("\nFor statement");}
	   ;


IFST	   : IF '(' E ')' Block 	{printf("\nIF statement");}
	     ;

ELST : ELSE Block				{printf("\nElse statement");}
	|
	ELSE IFST
	;

%%

int main()
{

	FILE *fp;

	fp= fopen("input.c","r");

	yyin=fp;

	yyparse();
	
	display();
}

void add_sym(char symbol[],int value)
{
  int i=0;

	for(i=0;i<sym_no;i++)
   	{
		if(strcmp(s[i].sym,symbol)==0)
		{
			return;
		}
   	}


  strcpy(s[sym_no].sym,symbol);
  s[sym_no].val=value;
  strcpy(s[sym_no].type,"-1");
  sym_no++;
}

void add_type(char type[])
{
   int i=0;

   for(i=0;i<sym_no;i++)
   {
	if(strcmp(s[i].type,"-1")==0)
	{
		strcpy(s[i].type,type);
	}
   }
}

void display()
{
	int i=0;

	printf("\n\nType\tSymbol\tValue");
	for(i=0;i<sym_no;i++)
	{
		printf("\n%s\t%s\t%d",s[i].type,s[i].sym,s[i].val);
	}
}

int yyerror()
{
	printf("\nError at line : %d",line_no);
	
}

