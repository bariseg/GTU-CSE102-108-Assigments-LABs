#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;
    int list_free_flag=0;
    int ordercount=0;

    Order* list=NULL;

    do
    {
        printf("Please select an option:\n");
        printf( "1. Enqeue\n"
                "2. Deqeue\n"
                "3. Update order\n"
                "4. Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            list_free_flag=1;
            ordercount++;
            char custname[20];
            char items[50];
            char ordertime[50];
            printf("Enter Customer name:");
            scanf(" %[^\n]s",custname);
            printf("Enter items(Burger, Fries ...):");
            scanf(" %[^\n]s",items);
            printf("Enter order time(08.42):");
            scanf(" %[^\n]s",ordertime);

            list=enqueue(list,custname,ordercount,items,ordertime);
            display(list);
            break;
        
        case '2':
            list_free_flag=1;

            list=dequeue(list);
            display(list);
            break;
        
        case '3':
            int updateorderid;
            char newitems[50];
            printf("Enter orderid:");
            scanf("%d",&updateorderid);
            printf("Enter new items:");
            scanf(" %[^\n]s",newitems);
            
            updateOrder(list,updateorderid,newitems);
            display(list);
            break;

        case '4':
            printf("Exiting!!\n");
            menu_flag=0;
            break;
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);
    

    if (list_free_flag)
    {
        free(list);
    }
    


    return(0);
}

