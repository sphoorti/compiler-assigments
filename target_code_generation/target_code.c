#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20

struct ICODE
{
	char oper[MAX];
	char op1[MAX];
	char op2[MAX];
	char res[MAX];
};

struct ICODE ic[MAX];

int n=0;	//count of icode records

struct target
{
	char label[MAX];
	char ins[MAX];
	char op1[MAX];
	char op2[MAX];
};

struct target tg[MAX];

int tgno=0;  //target code entries

int flag;

struct label
{
	int line;
	char lab[MAX];
};

struct label l[MAX];

int lno=0;   //label entries

void insert_target(char *,char *,char *);

void read_ic()
{
	FILE *fp;

	int i=0;

	fp=fopen("input.txt","r");

	if(!fp)
	{
		printf("\nError opening the file");
		return ;
	}
	else
	{

		while(!feof(fp))
		{
			fscanf(fp,"%s%s%s%s",ic[n].oper,ic[n].op1,ic[n].op2,ic[n].res);
			n++;
		}

		printf("\nIc : %d",n);
		for(i=0;i<n-1;i++)
		{
			printf("\n%s %s %s %s",ic[i].oper,ic[i].op1,ic[i].op2,ic[i].res);
		}

	}

}

void display_target()
{
	int i=0;
	printf("\n\nTarget code");
	for(i=0;i<tgno;i++)
	{
		printf("\n%d  %s %s %s %s",i,tg[i].label,tg[i].ins,tg[i].op1,tg[i].op2);
	}
	

}

int main()
{

	int i=0,j=0;

	read_ic();

	for(i=0;i<n-1;i++)
	{
		//to discover labels
		if(strcmp(ic[i].oper,"IF")==0)
		{
			char loop[10];
			sprintf(loop,"l%d:",i+1);
			l[lno].line=atoi(ic[i].res);
			strcpy(l[lno].lab,loop);
			lno++;
			

		}

		if(strcmp(ic[i].oper,"GOTO")==0)
		{
			char loop[10];
			sprintf(loop,"l%d:",i+1);
			l[lno].line=atoi(ic[i].res);
			strcpy(l[lno].lab,loop);
			lno++;		
		}
	}
	

	for(i=0;i<lno;i++)
	{
		printf("\n%d %s",l[i].line,l[i].lab);
	}

	for(i=0;i<n-1;i++)
	{
		//insert the label at a previous line since counting actually starts from 0
		for(j=0;j<lno;j++)
		{
			if((l[j].line-1)==i)
			{
				strcpy(tg[tgno].label,l[j].lab);
				break;
			}
		}
		
		if(strcmp(ic[i].oper,"=")==0)
		{	
			insert_target("MOV",ic[i].res,ic[i].op1);
		}
		
		if(strcmp(ic[i].oper,"+")==0)
		{
			insert_target("MOV","AX",ic[i].op1);
			insert_target("MOV","BX",ic[i].op2);
			insert_target("ADD","AX","BX");
			insert_target("MOV",ic[i].res,"AX");
		
						
		}

		if(strcmp(ic[i].oper,"-")==0)
		{
			insert_target("MOV","AX",ic[i].op1);
			insert_target("MOV","BX",ic[i].op2);
			insert_target("SUB","AX","BX");
			insert_target("MOV",ic[i].res,"AX");
			
		}
		

		if(strcmp(ic[i].oper,"<")==0)
		{
			insert_target("CMP",ic[i].op1,ic[i].op2);			
			flag=1;
		}
		if(strcmp(ic[i].oper,"<=")==0)
		{
			insert_target("CMP",ic[i].op1,ic[i].op2);	
			flag=2;
		}	
		if(strcmp(ic[i].oper,">")==0)
		{
			insert_target("CMP",ic[i].op1,ic[i].op2);	
			flag=3;
		}	
		if(strcmp(ic[i].oper,">=")==0)
		{
			insert_target("CMP",ic[i].op1,ic[i].op2);	
			flag=4;
		}

		if(strcmp(ic[i].oper,"IF")==0)
		{
			
			if(flag==1)	// <
			{
			char loop[10];
			sprintf(loop,"l%d:",i+1);			
			insert_target("JGE",loop," ");
			}

			else if(flag==2)	// <=
				{
			char loop[10];
			sprintf(loop,"l%d",i+1);			
			insert_target("JG",loop," ");
			}
		
			else if(flag==3)	// >
				{
			char loop[10];
			sprintf(loop,"l%d",i+1);			
			insert_target("JLE",loop," ");
			}
	
			else if(flag==4)	// >=
				{
			char loop[10];
			sprintf(loop,"l%d",i+1);			
			insert_target("Jl",loop," ");
			}
		}

		if(strcmp(ic[i].oper,"GOTO")==0)
		{
						
			
			char loop[10];
			sprintf(loop,"l%d",i+1);			
			insert_target("JMP",loop," ");
				
			
		}
			
		

	}


	//display target code
	display_target();
	

return 0;
}

void insert_target(char in[],char oper1[], char oper2[])
{

			//strcpy(tg[tgno].label,lab);
			strcpy(tg[tgno].ins,in);
			strcpy(tg[tgno].op1,oper1);
			strcpy(tg[tgno].op2,oper2);
			tgno++;
}
