#include<stdio.h>
#include<string.h>

#define MAX 20

struct target_code
{
   char keyword[10];
   char op1[10];
   char op2[10];
}tc[MAX];


int n=0;  // index for target code

void display()
{
    int i=0;	
	
		for(i=0;i<n-1;i++)
		{
		    printf("\n%s %s %s",tc[i].keyword,tc[i].op1,tc[i].op2);
		}
}

void remove_redundant(int ptr)
{
     int i;	
	for(i=ptr;i<n-1;i++)
	{
		tc[i]=tc[i+1];	
	}	
	
}

int main()
{
	FILE *fp;
	char ch;
	int i=0,flag_dup=0;

	fp=fopen("tc2.txt","r");

	if(!fp)
	{
		printf("\nError opening the file");
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
		   fscanf(fp,"%s %s %s",tc[n].keyword,tc[n].op1,tc[n].op2);
		   n++;
		}

		for(i=0;i<n-1;i++)
		{
		    printf("\n%s %s %s",tc[i].keyword,tc[i].op1,tc[i].op2);
		}

	
	//fast instruction selection

		for(i=0;i<n-1;i++)
		{
		    if((strcmp(tc[i].keyword,"IMUL")==0) && (strcmp(tc[i].op2,"2")==0)) 
		      {
			strcpy(tc[i].keyword,"ASHL");
			strcpy(tc[i].op2,"1");
			
		      }
		    if((strcmp(tc[i].keyword,"IDIV")==0) && (strcmp(tc[i].op2,"2")==0)) 
		      {
			strcpy(tc[i].keyword,"ASHR");
			strcpy(tc[i].op2,"1");
			
		      }
		}

	
	//machine idioms
		for(i=0;i<n-1;i++)
		{
		    if((strcmp(tc[i].keyword,"ADD")==0) && (strcmp(tc[i].op2,"1")==0)) 
		      {
			strcpy(tc[i].keyword,"INC");
			strcpy(tc[i].op2,"");
			
		      }
		    if((strcmp(tc[i].keyword,"SUB")==0) && (strcmp(tc[i].op2,"1")==0)) 
		      {
			strcpy(tc[i].keyword,"DEC");
			strcpy(tc[i].op2,"");
			
		      }
		}

	

	//remove redundant code

		for(i=0;i<n-1;i++)
		{
			flag_dup=0;
	
			if((strcmp(tc[i].keyword,tc[i+1].keyword)==0) && (strcmp(tc[i].op1,tc[i+1].op1)==0) && (strcmp(tc[i].op2,tc[i+1].op2)==0))
			{
				strcpy(tc[i+1].keyword,"dup");
				strcpy(tc[i+1].op1,"");
				strcpy(tc[i+1].op2,"");
				flag_dup=1;
			}
			
			else if((strcmp(tc[i].keyword,tc[i+1].keyword)==0) && (strcmp(tc[i].op1,tc[i+1].op2)==0) && (strcmp(tc[i].op2,tc[i+1].op1)==0))
			{
				remove_redundant(i+1);
				n--;
				//printf("\n%d",i);
			}

		}

	//algebraic simplifications
		for(i=0;i<n-1;i++)
		{
		    if((strcmp(tc[i].keyword,"ADD")==0) && (strcmp(tc[i].op2,"0")==0)) 
		      {
			remove_redundant(i);
			
		      }
		    else if((strcmp(tc[i].keyword,"MUL")==0) && (strcmp(tc[i].op2,"1")==0)) 
		      {
			remove_redundant(i);
			
		      }
		    else if((strcmp(tc[i].keyword,"SUB")==0) && (strcmp(tc[i].op2,"0")==0)) 
		      {
			remove_redundant(i);
		      }
		    else if((strcmp(tc[i].keyword,"DIV")==0) && (strcmp(tc[i].op2,"1")==0)) 
		      {
			remove_redundant(i);
		      }
		}

		printf("\n\n Optimized Target code is :\n");
		display();

	} //end of else
	return 0;
}

//OUTPUT
[sphoorti@inspiron peephole_optimization]$ gcc peephole.c
[sphoorti@inspiron peephole_optimization]$ ./a.out

MOV b R0
ADD c R0
MOV R0 a
MOV a R0
ADD e R0
MOV R0 d
ADD d 0
MOV a R1
MUL R1 1
ADD R1 b
IDIV ax 2
ADD R0 1
SUB R0 1
SUB R0 1
IMUL ax 2


 Optimized Target code is :


MOV b R0
ADD c R0
MOV R0 a
ADD e R0
MOV R0 d
MOV a R1
ADD R1 b
ASHR ax 1
INC R0 
DEC R0 
dup  
ASHL ax 1
  
[sphoorti@inspiron peephole_optimization]$ 

