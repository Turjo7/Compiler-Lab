%{

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#define MAX 30
#define SIZE 10

struct symbolTable
{
    char name[SIZE];
    char classType[SIZE];
    struct symbolTable *next;
}
*head[MAX];
typedef struct symbolTable node;

int hashFunction(char str[])
{
    int i;
    int ascii=0;
    for(i=0;str[i];i++)
    {
        printf("%-",str[i]);
        ascii=str[i]+ascii;

    }
    printf("= %d",ascii);
    ascii=ascii%MAX;
    return ascii;
}

void insert(char name[],char classType[])
{
    int hashValue;
    node *temp=NULL;
    hashValue = hashFunction(name);

    if( head[hashValue] == NULL )
    {
        head[hashValue] = new node;

        strcpy( head[hashValue]->name,name);
        strcpy( head[hashValue]->classType,classType );
        head[hashValue]->next = NULL;
    }
    else
    {
        temp = new node;

        strcpy( temp->name,name );
        strcpy( temp->classType,classType );
        temp->next = head[hashValue];
        head[hashValue] = temp;
    }
}



int n = 0;

%}


%%
"/*"[a-z*/]*"*/"	{ printf("Multi Line Comment Found :  %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*  { printf("Found Identifier : %s\n", yytext); insert(yytext, "id"); }
"program"|"if"|"not"|"end"|"begin"|"else"|"then"|"do"|"while"|"function"|"Procedure"|"integer"|"real"|"var"|"oh"|"array"|"write"		         				{ printf("Found KeyWord : %s at Line Number : %d\n", yytext, n+1); }
[+-]?[1-9][0-9]*	{ printf("Integer Number Found : %s\n", yytext); insert(yytext, "int"); }
"//".*			{ printf("Single Line Command Found : %s\n", yytext); }
"="|"<>"|"<"|"<="|">="|">"	{ printf("Found Relational Operator : %s\n", yytext); insert(yytext, "RELOP"); }
[+-]			{ printf("Found Additional Operator: %s\n", yytext); insert(yytext, "ADDOP"); }
[*/]			{ printf("Found Multiplier Operator: %s\n", yytext); insert(yytext, "MULOP"); }

":="			{ printf("Found Relational Operator : %s\n", yytext); insert(yytext, "ASSIGNOP"); }



[\n]		{ n++; }

%%


int main()
{
	yylex();
	printf("Total Number Of Lines: %d\n", n);
	return 0;
}

