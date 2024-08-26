#include <stdio.h>
#include <string.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;


    node* trees[5]; //there may be max 5 trees
    int i;
    for ( i = 0; i < 5; i++) trees[i]=NULL;
    
    char treenames[5][20];

    do
    {
        
        printf("\n\nMain menu:\n");
        printf( "1. Add Family Tree\n"
                "2. Remove Family Tree\n"
                "3. Load Family Tree\n"
                "4. Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':

            char addtreename[20];
            printf("Enter tree name(family.txt):");
            scanf(" %s",addtreename);

            node **temproot;
            for (i = 0; i < 5; i++)
            {
                if (trees[i]==NULL){
                    temproot=&(trees[i]);
                    strcpy(treenames[i],addtreename);
                    break;
                }
            }

            addFT(temproot,addtreename);
            break;
        
        case '2':

            char treename[15];
            printf("Enter filename to be removed:");
            scanf(" %s",treename);

            removeFT(treename);
            break;
        
        case '3':
            int opt;
            printf("family trees:\n");
            for (i = 0; i < 5; i++)
            {
                if (trees[i]!=NULL) printf("%d. %s\n",i,treenames[i]);
            }
            printf(">");
            scanf("%d",&opt);
            node *loadroot =NULL;
            if (trees[opt] != NULL){
                    loadroot = trees[opt];
                    printf("%s has been selected...\n", treenames[opt]);
                    loadFT(&loadroot, treenames[opt]);
                } else {
                    printf("Invalid option selected.\n");
                }

            loadFT(&loadroot,treenames[i]);
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
    
    return 0;
}

