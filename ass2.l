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
    int sum=0;
    for(i=0;str[i];i++)
    {
        printf("-%c-",str[i]);
        sum+=str[i];

    }
    printf("= %d",sum);
    sum=sum%MAX;
    return sum;
}

void insertToTable(char name[],char classType[])
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

void showTable()
{
    int i;
    node *temp;
    temp = new node;
    for(i=0;i<MAX;i++)
    {
        temp=head[i];
        printf("\n%d) ",i);
        while(temp!=NULL)
        {
            printf("<%s,%s> ",temp->name,temp->classType);
            temp=temp->next;
        }
    }
}

int searchFromTable(char name[],char classType[])
{
    node *temp = NULL;
    int hashValue;
    hashValue = hashFunction(name);

    if( head[hashValue] == NULL )
    {
        printf("Not Found\n");
        return -1;
    }

    temp = new node;
    temp = head[hashValue];

    while(temp)
    {


        if(strcmp(temp->name,name)==0&&strcmp(temp->classType,classType)==0)
        {
            printf("\nFound\n");
            return 1;
        }
        temp=temp->next;
    }
    printf("Not Found\n");

}

int update(char name[],char classType[],char newClassType[])
{
    node *temp = NULL;
    int hashValue;
    hashValue = hashFunction(name);

    if( head[hashValue] == NULL )
    {
        printf("Not Found\n");
        return -1;
    }

    temp = new node;
    temp = head[hashValue];

    while(temp)
    {


        if(strcmp(temp->name,name)==0&&strcmp(temp->classType,classType)==0)
        {
            strcpy( temp->classType,newClassType );
            return 1;
        }
        temp=temp->next;
    }

}

void deleteFromTable(char name[],char classType[])
{
    node *prev = NULL;
    node *temp = NULL;
    int hashValue;

    hashValue = hashFunction(name);

    if(head[hashValue]==NULL )
    {
        printf("Nothing to Delete");
        return;
    }

    temp = new node;
    temp = head[hashValue];
    if( strcmp(temp->name,name)==0&&strcmp(temp->classType,classType)==0 )
    {
        head[hashValue] = head[hashValue]->next;
        free(temp);
        printf("\nData Deleted\n");
        return;
    }
    prev=new node;
    prev=temp;

    while(temp!=NULL)
    {
        if(strcmp(temp->name,name)==0&&strcmp(temp->classType,classType)==0)
        {
            prev->next=temp->next;
            free(temp);
            printf("\nData Deleted\n");
            return;
        }
        prev=temp;
        temp=temp->next;
    }
    printf("Data not not Found\n");

    return;
}


int options()
{
    int option;
    printf("Press 1 to Insert\nPress 2 to Search\nPress 3 to Delete\nPress 4 to Show\nPress 5 to update\nPress 6 to exit");
    printf("\n\n");

    scanf("%d",&option);

    if((option>0) && (option<7))
    {
        return option;
    }
    else
        printf("Wrong Input\n");
}

void detection(int option)
{
    if(option == 1)
    {
        char name[SIZE];
        char classType[SIZE];
        printf("Enter name:  ");
        fflush(stdout);
        scanf("%s",name);
        fflush(stdin);

        printf("\nClass Type : ");
        fflush(stdout);
        gets(classType);
        fflush(stdin);

        insertToTable(name,classType);
        printf("\n\n");
    }
    if(option == 2)
    {
        char name[SIZE];
        char classType[SIZE];
        printf("Enter name :  ");
        fflush(stdout);
        scanf("%s",name);
        fflush(stdin);

        printf("\nClass Type : ");
        fflush(stdout);
        gets(classType);
        fflush(stdin);

        searchFromTable(name,classType);
        printf("\n\n");
    }
    if(option == 3)
    {
        char name[SIZE];
        char classType[SIZE];
        printf("Enter name :  ");
        fflush(stdout);
        scanf("%s",name);
        fflush(stdin);

        printf("\nClass Type : ");
        fflush(stdout);
        gets(classType);
        fflush(stdin);

        deleteFromTable(name,classType);
        printf("\n\n");
    }
    if(option == 4)
    {
        showTable();
        printf("\n\n");
    }
    if(option == 5)
    {
        char name[SIZE];
        char classType[SIZE];
        char newClassType[SIZE];

        printf("Enter name : ");
        fflush(stdout);
        scanf("%s",name);
        fflush(stdin);

        printf("\nClass Type : ");
        fflush(stdout);
        gets(classType);
        fflush(stdin);

        printf("\nNewClass Type : ");
        fflush(stdout);
        gets(newClassType);
        fflush(stdin);

        update(name,classType,newClassType);
        printf("\n\n");
    }
    if(option == 6)
    {
        exit(0);
    }
}


int line = 0;

%}


%%

"/*"[a-z*/]*"*/"	{ printf("found multiline comment: %s\n", yytext); }
_?[a-zA-Z][A-Za-z0-9_]*				{ printf("found id: %s\n", yytext); insertToTable(yytext, "ID"); }
"program"|"if"|"not"|"end"|"begin"|"else"|"then"|"do"|"while"|"function"|"Procedure"|"integer"|"real"|"var"|"or"|"array"|"write"		{ printf("keyword found: %s @line_number: %d\n", yytext, line+1); }

[+-]?[1-9][0-9]*				{ printf("found integer number: %s\n", yytext); insertToTable(yytext, "INT"); }

"//".*		{ printf("singleline comment found: %s\n", yytext); }

["].+["]	{ printf("found double quoted string: %s\n", yytext); }

[+-]?[0-9]*"."[0-9]+				{ printf("found float number: %s\n", yytext); insertToTable(yytext, "FLOAT"); }
[+-]?[1-9]("."[0-9]+)?"E"[+-]?[1-9][0-9]*	{ printf("found exponent number: %s\n", yytext); insertToTable(yytext, "EXPONENTIAL"); }

"="|"<>"|"<"|"<="|">="|">"	{ printf("RELOP found: %s\n", yytext); insertToTable(yytext, "RELOP"); }

[+-]		{ printf("found ADDOP: %s\n", yytext); insertToTable(yytext, "ADDOP"); }
[*/%]		{ printf("found MULOP: %s\n", yytext); insertToTable(yytext, "MULOP"); }


":="		{ printf("found ASSIGNMENTOP: %s\n", yytext); insertToTable(yytext, "ASSIGNOP"); }
"[]"|"()"|".."		{ printf("found dotdot: %s\n", yytext); insertToTable(yytext, "DOTDOT"); }

","		{ printf("found comma: %s\n", yytext); insertToTable(yytext, "COMMA"); }
";"		{ printf("found semicolon: %s\n", yytext); insertToTable(yytext, "SEMICOLON"); }
":"		{ printf("found colon: %s\n", yytext); insertToTable(yytext, "COLON"); }



[\n]		{ line++; }

%%


int main()
{
	yylex();
	printf("TOtal Line Number: %d\n", line);
	return 0;
}

