#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;
    Customer * customers=NULL;

    do
    {
        printf("\nWelcome to the Bank system!\n\n");
        printf("Please select an option:\n");
        printf( "1. Insert new customer\n"
                "2. Remove customer\n"
                "3. Display customers in order\n"
                "4. Search a customer\n"
                "5.Change priority settings\n"
                "6.Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            char cname[20],group[10];
            int cage;
            printf("Enter customer name:");
            scanf(" %[^\n]s",cname);
            printf("enter customer age:");
            scanf("%d",&cage);
            printf("enter customer group:");
            scanf(" %[^\n]s",group);

            customers=insertcustomer(customers,cname,cage,group);

            break;
        
        case '2':
            
            char deletename[20];
            printf("Enter name:");
            scanf(" %[^\n]s",deletename);

            customers=removeCustomer(customers,deletename);

            break;
        
        case '3':
            display(customers);
            break;
        
        case '4':
            char searchname[20];
            printf("Enter name:");
            scanf(" %[^\n]s",searchname);

            searchingcustomers(customers,searchname);

            break;
        
        case '5':
            int newl;
            char nname[20];
            printf("customer name:");
            scanf(" %[^\n]s",nname);
            printf("new priority level:");
            scanf("%d",&newl);

            changePriority(customers,nname,newl);
            break;
        
        case '6':
            printf("Exiting\n");
            menu_flag=0;
            break;
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);
    
    return(0);
}

