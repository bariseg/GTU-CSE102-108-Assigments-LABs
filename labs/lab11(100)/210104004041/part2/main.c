#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;

    ExamPaper * exams= NULL;

    do
    {
        printf("\nPlease select an option:\n");
        printf( "1. Push\n"
                "2. Pop\n"
                "3. isempty\n"
                "4. display\n"
                "5. Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            char name[20];
            int no,score;
            printf("Name:");
            scanf(" %[^\n]s",name);
            printf("no:");
            scanf("%d",&no);
            printf("Score:");
            scanf("%d",&score);

            exams=push(exams,name,no,score);
            display(exams);
            break;
        
        case '2':
            exams=pop(exams);
            display(exams);
            break;
        
        case '3':
        
            if (!isEmpty(exams))
            {
                printf("Stack is not empty!!\n");
            }else{
                printf("Stack is empty!!\n");
            }
            

            break;
        
        case '4':
            display(exams);
            break;
        case '5':
            printf("Exiting!!\n");
            menu_flag=0;
            break;
        
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);

    if (!isEmpty(exams))
    {
        free(exams);
    }
    

    
    return(0);
}

