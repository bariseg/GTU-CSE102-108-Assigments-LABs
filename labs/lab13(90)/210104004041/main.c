#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){
    
    char *filename= "input.txt";

    BST * tree= generateBST(filename);

    char option;
    int menu_flag=1;

    do
    {
        printf( "\n\na) addnode\n"
                "b) removenode\n"
                "c) searchnode\n"
                "d) statictics\n"
                "e) exit\n"
                ">  ");
        scanf(" %c",&option);



        switch (option)
        {
        case 'a':
            int newval;
            printf("Enter value:");
            scanf(" %d",&newval);

            addNode(tree,newval);
            printf("added\n");
            break;
        
        case 'b':
            int r_value;
            printf("Enter value:");
            scanf(" %d",&r_value);

            removeNode(tree,r_value);
            break;
        
        case 'c':
            int s_value;
            printf("Enter value:");
            scanf(" %d",&s_value);

            Node * result= searchNode(tree,s_value);

            if (result==NULL)
            {
                printf("Doesnt exist!!\n");
            }else{
                printf("%d found!!\n",result->value);
            }
            break;
        
        case 'd':
            printf("Tree : ");
            printTree(tree);

            printf("\nNode count: %d\n",countNodes(tree));
            printf("leaf count: %d\n",countLeafNodes(tree));

            break;
        case 'e':
            printf("exiting\n");
            menu_flag=0;
        break;
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);

    return 0;
}

