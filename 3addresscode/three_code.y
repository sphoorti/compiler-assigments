%{
#include<stdio.h>
#include<string.h>

extern line_no;

 void push(int);
 int pop();

struct Quadruple
  {
    char operator[10];
    char operand1[10];
    char operand2[10];
    char result[10];
  }quad[25];

struct symbol_table
  {
	char symbol[10];
	char type[10];
  }sym[25];

struct Stack
  {
    int items[25];
    int top;
  }stk;

%}
