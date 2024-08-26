#include <stdio.h>
#include "util.h"

void menu(){

    int selection;
    int part2_flag=0;
    int exit_flag=1;
    
    while (exit_flag){
        printf("Welcome to Shape Reader!\n");
        printf("Generate a shape file (1)\n");

        if (part2_flag)
        {
            printf("Read and draw a shape file (2)\n");
        }
        
        printf("Terminate the program (3)\n\n");

        scanf("%d",&selection);



        switch (selection)
        {
        case 1:
            get_input_write_file();
            part2_flag=1;
            break;
        case 2:
            if (part2_flag)
            {
                read_file_and_call_drawers();
            }else{
                printf("You have no txt file!\n");
            }
            
            break;
        case 3:
            printf("Thanks...\n");
            exit_flag=0;
            break;
        
        default:
            printf("Invalid input\n");
            break;
        }
    }

}

void get_input_write_file(){

    char user_type,comma;
    int user_size;
    FILE *fp;

    printf("Enter type and size (s,5) (t,7) size must be between 3-10, to end the writing type (e):");

    fp= fopen("user_inputs.txt","w+");

    do
    {
        
        scanf(" %c",&user_type);
        if (user_type=='e')
        {
            break;
        }

        scanf(" %c",&comma); //cleaning scanf
        scanf(" %d",&user_size);
        
        fprintf(fp,"%c,%d\n", user_type,user_size);

    } while (user_type!='e');
    fprintf(fp,"%c,%d",'b',0);

    fclose(fp);
    
}

void read_file_and_call_drawers(){

    FILE *txtfile;

    char shape_type;
    int shape_size;

    txtfile = fopen("user_inputs.txt","r+");
    
    do{
        fscanf(txtfile, "%c,%d\n" , &shape_type,&shape_size);
    
        switch (shape_type){
        case 't':
            triangle_drawer(shape_size);
            break;
        
        case 's':
            square_drawer(shape_size);
            break;
        
        default:
            break;
        }
    }while(shape_type!= 'b');
    fclose(txtfile);

}


void triangle_drawer(int size){


    
    

}


void square_drawer(int size){

    for(int i=1; i<=size; i++){
            printf("* ");
    }
    printf("\n");
    for(int i=1; i<=(size-2); i++){
        
        for(int j=1; j<=size; j++){
            if(j==1 || j==size){
                printf("* ");
            }
            else{
                printf("  ");
            }
        }
        printf("\n");
    }

    for(int i=1; i<=size; i++){
            printf("* ");
    }
    printf("\n\n");
}