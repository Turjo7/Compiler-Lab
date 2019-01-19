

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 67


struct SymbolInfo{
    char name[20];
    char class_type[20];
    int val;
    SymbolInfo *next;
};

struct SymbolInfo *SymbolTable[max];

int hash(char *name);
int search(char *name,char *class_type);
void insert(char *name,char *class_type,int val);
void del(char *name,char *class_type);
void update(char *name,char *class_type);
void show();
void operation();
void insert2t(char *name,char *class_type);


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
    printf("Press 4 To Delete\n");
    printf("Press 5 To Update\n");
    printf("Press 6 To Insert<-> If Multiple Of 10\n");
    printf("Press 7 To Close\n\n\n");
    printf("Enter Your Choice : ");
    scanf("%d",&n);

    char name[20];
    char class_type[20];
    int val;

    switch(n){

   case 1:
   printf("Input Name: \n");
   scanf("%s",name);
   printf("Input class Type: \n");
   scanf("%s",class_type);
   printf("Enter A val\n");
   scanf("%d",&val);
   insert(name,class_type,val);
   break;

   case 2:
   show();
   break;

   case 3:
                printf("Input Search Name\n");
                scanf("%s",name);

                printf("Input Search Class Type\n");
                scanf("%s",class_type);

                printf("Enter A val\n");
                scanf("%d",&val);

                index = search(name,class_type);

                printf("Position ---- Name ----- Class Type ---------- A val \n\n");

                if(index == -1)
                {
                    printf(" Data ---- Not ----- Match \n\n");
                }
                else{
                    struct SymbolInfo *temp;
                    temp = SymbolTable[index];

                    if(SymbolTable[index]->next == NULL)
                    {
                        printf("  %d  -->    ",index);

                        printf("%s",temp->name);

                        printf("   -->    ");

                        printf("%s",temp->class_type);

                        printf("%d",temp->val);
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
    printf("Enter Name\n");
    scanf("%s",name);
    printf("Enter Class Type\n");
    scanf("%s",class_type);
    printf("Enter A val\n");
    scanf("%d",&val);
    del(name,class_type);
    break;

    case 5:
    printf("Input Name\n");
    scanf("%s",name);
    printf("Input Class Type\n");
    scanf("%s",class_type);
    printf("Enter A val\n");
    scanf("%d",&val);

    update(name,class_type);

    break;

   case 6:
   printf("Input Name: \n");
   scanf("%s",name);
   printf("Input class Type: \n");
   scanf("%s",class_type);
   insert2t(name,class_type);

   break;


   case 7:
   exit(0);
   break;

  default:
   printf("Wrong Input Option From Menu\n");


  }





  }
}

void insert(char *name,char *class_type,int val){

    int check = search(name,class_type);

    if(check==-1){ /*newly added*/

    int key = hash(name);
    if(SymbolTable[key] == NULL){
      SymbolTable[key] = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));
     int x = strlen(name);
     for(int i=0;i<=x ;i++){
      SymbolTable [key]->name[i] = name[i];
    }
    x = strlen(class_type);
    for(int i=0;i<=x;i++){
      SymbolTable[key]->class_type[i] = class_type[i];
  }
      SymbolTable[key]->val=val;
      SymbolTable[key]->next = NULL;

 }
    else{
            struct SymbolInfo * temp,*temp2;

            temp = SymbolTable[key];

        for(int i = 0; temp->next != NULL; i++)
        {
            temp = temp->next;
        }

        temp2 = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));

        int x=strlen(name);
        for(int i=0; i <= x ; i++){

            temp2->name[i] = name[i];
        }

        x=strlen(class_type);
        for(int i=0; i <= x; i++){

            temp2->class_type[i] = class_type[i];
        }


        temp2->val=val;
        temp2->next = NULL;

        temp->next = temp2;

    }
   }
   else{
    printf("\t\t\tYou Can Not Input\n");
   }
}


void show(){
    printf(" Hash  ----  Name  ---  Class Type ----- A val \n\n");

    int i;
    int test = 0;
    for(i = 0; i <max;i++)
    {


        if(SymbolTable[i] != NULL){

            struct SymbolInfo * temp;
            temp = SymbolTable[i];
        do
        {

            test = 1;

            printf("  %d  --   ",i);

            printf("%s",temp->name);

            printf("  --   ");

            printf("%s ----- ",temp->class_type);

            printf(" %d",temp->val);

            printf("\n\n");

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

        struct SymbolInfo *temp;
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

void del(char *name,char *class_type){
     int index = hash(name);

        int test = 0;

        if(SymbolTable[index] != NULL){

            struct SymbolInfo * temp;
            temp = SymbolTable[index];

            while(temp != NULL){


                int name_compare = strcmp(temp->name,name);
                int class_type_compare = strcmp(temp->class_type,class_type);


                if(name_compare == 0 && class_type_compare == 0)
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


                    int name_compare = strcmp(temp->next->name,name);
                    int class_type_compare = strcmp(temp->next->class_type,class_type);


                    if(name_compare == 0 && class_type_compare == 0)
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


        }

        if(test==0){
            printf("\t\t <<Not Found>>\n\n\n");
        }

}

void update(char *name,char *class_type){

        int index = search(name,class_type);

        if(index == -1){

          printf("Not Found\n");
        }

        else{

        char new_class_type[20];
        printf("Enter New Class Type\n");
        scanf("%s",new_class_type);

        if(SymbolTable[index]->next == NULL){
            strcpy(SymbolTable[index]->class_type,new_class_type);
            }

            else{
             struct SymbolInfo *temp;
             temp = SymbolTable[index];

              while(temp->next != NULL){

              int m1 = strcmp(temp->name,name);
              int m2 = strcmp(temp->name,name);

              if(m1 == 0 && m2==0){
                strcpy(temp->class_type,new_class_type);
                break;
                }
                else{
                    temp=temp->next;
                    }
                }
                }

        }



}

void insert2t(char *name,char *class_type){

    int val;   // newly added
    printf("Enter Val: \n");
    scanf("%d",&val);
    char test[20]="number";
    if(strcasecmp(class_type,test)==0&&((val%10)==0)){                       /* strcasecmp(class_type,test)==0&&((val%10)==0  this perameter did the problem to me */

    int key = hash(name);
    if(SymbolTable[key] == NULL){
      SymbolTable[key] = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));
     int x = strlen(name);
     for(int i=0;i<=x ;i++){
      SymbolTable [key]->name[i] = name[i];
    }
    x = strlen(class_type);
    for(int i=0;i<=x;i++){
      SymbolTable[key]->class_type[i] = class_type[i];
  }
      SymbolTable[key]->val=val;
      SymbolTable[key]->next = NULL;

 }
    else{
            struct SymbolInfo * temp,*temp2;

            temp = SymbolTable[key];

        for(int i = 0; temp->next != NULL; i++)
        {
            temp = temp->next;
        }

        temp2 = (struct SymbolInfo *)malloc(sizeof(struct SymbolInfo));

        int x=strlen(name);
        for(int i=0; i <= x ; i++){

            temp2->name[i] = name[i];
        }

        x=strlen(class_type);
        for(int i=0; i <= x; i++){

            temp2->class_type[i] = class_type[i];
        }


        temp2->val=val;
        temp2->next = NULL;

        temp->next = temp2;




    }



show();
}

 else{
   printf("Class Type Is Not  <number>!!!!\n\n");
 }


}








