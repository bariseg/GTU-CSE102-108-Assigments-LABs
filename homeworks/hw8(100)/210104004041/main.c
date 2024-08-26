#include <stdio.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;

    do
    {
        printf("Welcome to the 8-Puzzle Game!\n\n");
        printf("Please select an option:\n");
        printf( "1. Play game as a user\n"
                "2. Finish the game with PC\n"
                "3. Show the best score\n"
                "4. Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            user_plays();
            break;
        
        case '2':
            computer_plays();
            break;
        
        case '3':
            int best_scr=best_score_checker();
            printf("Best Score: %d\n\n",best_scr);
            break;
        
        case '4':
            printf("Thanks for playing!!\n");
            menu_flag=0;
            break;
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);
    
    return(0);
}

