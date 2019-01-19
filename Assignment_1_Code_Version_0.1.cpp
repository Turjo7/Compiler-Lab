/*
   </> Assignment_1_Code_Version_0.1 <\>
   This Version Of The Code has
   1. Input Function
   2. Show Function
   3. Search Function

   Last Modified
   Date : 12 / 10 / 2017
   Day : Thursday
   Time : 10 : 49 P.M
   Turjo 86
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 10


struct SymbolTable{
    char name[20];
    char class_type[20];
    SymbolTable *next;
};

struct SymbolTable *SymbolTable[max];

int hash(char *name);
int search(char *name,char *class_type);
void insert(char *name,char *class_type);
void show();
void operation();

int main(){


    operation();

    return 0;
}


void operation(){


    int n,x,index;
    while(true){

    fflush(stdin);
    printf("\nMenu: \n\n");
    printf("Press 1 To Insert\n");
    printf("Press 2 To Show\n");
    printf("Press 3 To Search\n");
    printf("Press 4 To Close\n\n\n");
    scanf("%d",&n);

    char name[20];
    char class_type[20];

    switch(n){

   case 1:
   printf("Input Name: \n");
   scanf("%s",name);
   printf("Input class Type: \n");
   scanf("%s",class_type);
   insert(name,class_type);
   break;

   case 2:
   show();
   break;

   case 3:
       printf("Input Search Name\n");
                scanf("%s",name);

                printf("Input Search Class Type\n");
                scanf("%s",class_type);

                index = search(name,class_type);

                printf(" HashingPosition ---- Name ----- Class Type \n\n");

                if(index == -1)
                {
                    printf(" Data ---- Not ----- Match \n\n");
                }
                else{
                    struct SymbolTable *temp;
                    temp = SymbolTable[index];

                    if(SymbolTable[index]->next == NULL)
                    {
                        printf("  %d  -->    ",index);

                        printf("%s",temp->name);

                        printf("   -->    ");

                        printf("%s",temp->class_type);
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

                                printf("%s",temp->class_type);
                                printf("\n\n");

                                break;
                            }
                            else
                                temp = temp->next;
                        }
                    }
                }
    break;

   case 4:
   exit(0);
   break;

  default:
   printf("Wrong Input Option From Menu\n");


  }





  }
}

void insert(char *name,char *class_type){

    int key = hash(name);
    if(SymbolTable[key] == NULL){
      SymbolTable[key] = (struct SymbolTable *)malloc(sizeof(struct SymbolTable));
     int x = strlen(name);
     for(int i=0;i<=x ;i++){
      SymbolTable [key]->name[i] = name[i];
    }
    x = strlen(class_type);
    for(int i=0;i<=x;i++){
      SymbolTable[key]->class_type[i] = class_type[i];
  }
      SymbolTable[key]->next = NULL;

 }
    else{
            struct SymbolTable * temp,*temp2;

            temp = SymbolTable[key];

        for(int i = 0; temp->next != NULL; i++)
        {
            temp = temp->next;
        }

        temp2 = (struct SymbolTable *)malloc(sizeof(struct SymbolTable));

        int x=strlen(name);
        for(int i=0; i <= x ; i++){

            temp2->name[i] = name[i];
        }

        x=strlen(class_type);
        for(int i=0; i <= x; i++){

            temp2->class_type[i] = class_type[i];
        }

        temp2->next = NULL;

        temp->next = temp2;

    }
}


void show(){
printf(" Hash Number -----  VariableName ----- DataType \n\n");

    int i;
    int test = 0;
    for(i = 0; i <max;i++)
    {


        if(SymbolTable[i] != NULL){

            struct SymbolTable * temp;
            temp = SymbolTable[i];
        do
        {

            test = 1;

            printf("  %d  -->   ",i);

            printf("%s",temp->name);

            printf("  -->   ");

            printf("%s",temp->class_type);

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
        printf(" Empty \n");
    }
}

int hash(char *name){
    int index,ascii=0;
   for(int i=0;i<strlen(name);i++){
       ascii = ascii + name[i];

 }
       index = ascii % max;
       return index;
}

int search(char *name,char *class_type){
    int index = hash(name);


    if(SymbolTable[index] == NULL)
    {
        return -1;
    }
    else{

        struct SymbolTable *temp;
        temp = SymbolTable[index];



        if(temp->next == NULL)
        {

            int name_comp = strcmp(name,temp->name);
            int type_comp = strcmp(class_type,temp->class_type);

            if(name_comp == 0 && type_comp == 0)
            {
                return index;
            }
            else{
                while(temp->next != NULL)
                {
                    int name_comp = strcmp(name,temp->name);
                    int type_comp = strcmp(class_type,temp->class_type);

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
