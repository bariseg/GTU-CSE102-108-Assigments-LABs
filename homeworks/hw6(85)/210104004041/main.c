#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


int main(){

    int menu_flag=1;
    char option;
    double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN];
    int size=0;
    int matched_products=0;

    do
    {
        printf("\n\tWelcome operator,please select a option to continue:\n");
        printf("1- File Operations\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n");
        printf("Option:");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            file_operations();
            break;
        case '2':
            query_products();
            break;
        case '3':
            check_stock_status();
            break;
        case '4':
            brand_stock_control(results,&size,&matched_products);
            break;
        case '5':
            printf("%d",matched_products);
            stock_report(results,size,matched_products);
            menu_flag=0;
            break;
        
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }



    } while (menu_flag);
    
    

    
    return(0);
}

