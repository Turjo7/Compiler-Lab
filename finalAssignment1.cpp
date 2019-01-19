#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 10

struct SymbolInfo
{
    char name[50];
    char type[50];
    SymbolInfo * next;

};

struct SymbolInfo *SymbolTable[MAX];

int getHashKey(char *name);
void testing();
void insertEntry(char *name,char *type);
void showEntry();
void deleteEntry(char *name,char *type);
int searchEntry(char *name,char *type);
int primeNumber(char *name);
void updateEntry(char *name,char *type);

int main()
{
    testing();
    return 0;
}

void testing()
{

    char choice;
    int x,index ;

    while(true)
    {
        fflush(stdin);
        printf("Select option .\n\n");

        printf("    => 1 = Insert Entry .\n");
        printf("    => 2 = Delete Entry .\n");
        printf("    => 3 = Show Entry .\n");
        printf("    => 4 = Update Entry .\n");
        printf("    => 5 = Search Entry .\n");
        printf("    => 6 = Exit .\n");

        scanf("%c",&choice);

        char name[50];
        char type[50];

        switch(choice)
        {
            case '1':

                printf("-->Input entry name .\n");
                scanf("%s",name);

                printf("-->Input entry type .\n");
                scanf("%s",type);

                insertEntry(name,type);

                break;


            case '2':

                printf("-->Input delete entry name .\n");
                scanf("%s",name);

                printf("-->Input delete entry type .\n");
                scanf("%s",type);

                deleteEntry(name,type);
                break;

            case '3':
                showEntry();
                break;

            case '4':
                printf("-->Input entry name .\n");
                scanf("%s",name);

                printf("-->Input entry old type .\n");
                scanf("%s",type);

                updateEntry(name,type);

                break;

            case '5':
                printf("-->Input search entry name .\n");
                scanf("%s",name);

                printf("-->Input search entry type .\n");
                scanf("%s",type);

                index = searchEntry(name,type);

                printf(" HashingPosition ---- VariableName ----- DataType \n\n");

                if(index == -1)
                {
                    printf(" Data ---- Not ----- Match \n\n");
                }
                else{
                    struct SymbolInfo * temp;
                    temp = SymbolTable[index];

                    if(SymbolTable[index]->next == NULL)
                    {
                        printf("  %d  -->    ",index);

                        printf("%s",temp->name);

                        printf("   -->    ");

                        printf("%s",temp->type);
                        printf("\n\n");

                    }
                    else{

                        while(temp->next != NULL)
                        {
                            int match1 = strcmp(temp->name,name);
                            int match2 = strcmp(temp->name,name);
                            if(match1 == 0 && match2 ==  0)
                            {
                                printf("  %d  -->    ",index);

                                printf("%s",temp->name);

                                printf("   -->    ");

                                printf("%s",temp->type);
                                printf("\n\n");

                                break;
                            }
                            else
                                temp = temp->next;
                        }
                    }
                }

                break;

            case '6':
                exit(0);
                break;

            default :

                printf("Select valid option .\n");

        }


    }

}
int getHashKey(char *name)
{
    int index, ascii = 0;

    for(int i=0; i < strlen(name); i++)
    {
        ascii = ascii + name[i];
    }

    index = ascii % MAX;

    return index;

}


void insertEntry(char *name,char *type)
{
    int index = getHashKey(name);

    if(SymbolTable[index] == NULL)
    {

        SymbolTable[index] = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));

        int x=strlen(name);
        for(int i=0; i <= x ; i++){

            SymbolTable[index]->name[i] = name[i];
        }

        x=strlen(type);
        for(int i=0; i <= x; i++){

            SymbolTable[index]->type[i] = type[i];
        }

        SymbolTable[index]->next = NULL;




    }
    else{
        struct SymbolInfo * temp,*temp2;

        temp = SymbolTable[index];

        for(int i = 0; temp->next != NULL; i++)
        {
            temp = temp->next;
        }

        temp2 = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));

        int x=strlen(name);
        for(int i=0; i <= x ; i++){

            temp2->name[i] = name[i];
        }

        x=strlen(type);
        for(int i=0; i <= x; i++){

            temp2->type[i] = type[i];
        }

        temp2->next = NULL;

        temp->next = temp2;

    }
}
void showEntry()
{

    printf(" HashingPosition -----  VariableName ----- DataType \n\n");

    int i;
    int test = 0;
    for(i = 0; i <MAX;i++)
    {


        if(SymbolTable[i] != NULL){

            struct SymbolInfo * temp;
            temp = SymbolTable[i];
        do
        {

            test = 1;

            printf("  %d  -->   ",i);

            printf("%s",temp->name);

            printf("  -->   ");

            printf("%s",temp->type);

            if(temp->next != NULL){
                temp = temp->next;

            }
            else{
                printf("\n\n");
                break;
            }

            printf("\n\n");



        }while(true);


        }
    }
    if(test == 0){
        printf(" Empty ---- Empty ----- Empty \n\n");
    }
}


void deleteEntry(char *name,char *type)
{

        int index = getHashKey(name);

        int test = 0;

        if(SymbolTable[index] != NULL){

            struct SymbolInfo * temp;
            temp = SymbolTable[index];

            while(temp != NULL){


                int name_comp = strcmp(temp->name,name);
                int type_comp = strcmp(temp->type,type);


                if(name_comp == 0 && type_comp == 0)
                {
                    test = 1;

                   if(temp->next == NULL)
                   {
                       SymbolTable[index] = NULL;
                       break;
                   }
                   else
                   {
                       SymbolTable[index] = temp->next;
                       break;
                   }


                }


                while(temp->next != NULL){


                    int name_comp = strcmp(temp->next->name,name);
                    int type_comp = strcmp(temp->next->type,type);


                    if(name_comp == 0 && type_comp == 0)
                    {
                        test = 1;
                        if(temp->next->next != NULL){
                            temp->next = temp->next->next;
                            break;
                        }

                        else{
                            temp->next = NULL;
                            break;
                        }

                    }

                    if(temp->next != NULL){
                        temp = temp->next;

                    }
                    else{

                        break;
                    }

                }



            }

            printf(" # Data not match .\n\n");
        }

}


int searchEntry(char *name,char *type)
{
    int index = getHashKey(name);


    if(SymbolTable[index] == NULL)
    {
        return -1;
    }
    else{

        struct SymbolInfo * temp;
        temp = SymbolTable[index];



        if(temp->next == NULL)
        {

            int name_comp = strcmp(name,temp->name);
            int type_comp = strcmp(type,temp->type);

            if(name_comp == 0 && type_comp == 0)
            {
                return index;
            }
            else{
                while(temp->next != NULL)
                {
                    int name_comp = strcmp(name,temp->name);
                    int type_comp = strcmp(type,temp->type);

                    if(name_comp == 0 && type_comp == 0)
                    {
                        return index;
                    }
                    else{
                        temp = temp->next;
                    }
                }
                return -1;
            }
        }


    }


}
void updateEntry(char *name,char *type)

{
     int index = searchEntry(name,type);
    if(index == -1)
    {
        printf("Data no match\n\n");

    }
    else{
        char new_type[50];
        printf("-->Input new type .\n");
        scanf("%s",new_type);

        if(SymbolTable[index]->next == NULL)
        {
            strcpy(SymbolTable[index]->type,new_type);
        }
        else{
            struct SymbolInfo * temp;
            temp = SymbolTable[index];

            while(temp->next != NULL)
            {
                int match1 = strcmp(temp->name,name);
                int match2 = strcmp(temp->name,name);
                if(match1 == 0 && match2 ==  0)
                {
                    strcpy(temp->type,new_type);
                    break;
                }
                else{
                    temp = temp->next;
                }
            }
        }

    }

}



