#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

#define NEW_GAME '1'
#define HELP '2'
#define EXIT '3'

void menu_help(); //made in order to avoid multiple printf 
void menu(); //has menu and general algorithm inside
void map_drawer(int c_x,int c_y,int d_x,int d_y,int N,int error_flag,int input_error_flag); //draws the current game situation. Also prints the warnings if necessary
void map_cleaner(); //clears the previous map after an input.
int control_func(int c_x,int c_y,int d_x,int d_y); //checks if the game has to end.
void gameplay(int first_c_x,int first_c_y,int d_x,int d_y,int N); //includes gettin input and gameplay algorithm
void main_game_func(); //in order to transfer between functions and use some common variables, i need a main game function.

int main(){

    menu(); //menu has everything inside

    return(0);
}

void menu(){

    char selection;
    int exit_flag=0;

    while (!(exit_flag)){
    
        printf("(*_*) Welcome to the 2D puzzle game!! (*_*)\n\n");
        printf("(1) New Game\n(2) Help\n(3) Exit\nSelect Please:");
        
        scanf("%c",&selection);

        if(selection=='2'){ //there were a bug when '2' is taken as the input: \n was also got by the scanf. this 'if' fixes that bug
            char debugger_char;
            scanf("%c",&debugger_char);
            
        }

        switch (selection){
            case NEW_GAME:
                main_game_func(); //
                break;
            
            case HELP:
                menu_help(); //prints certain help instractions
                break;
            
            case EXIT:
                printf("** THANKS FOR PLAYING **\n** GOODBYE **\nBaris Eren Gezici 210104004041\n");
                exit_flag=1; //in order to terminate the program
                break;
            
            default:
                printf("Invalid input\n"); //selection must be 1,2 or 3
                break;
            }
        
    }
}   
//help option has too many prints,so it looks beter when it has itsown function
void menu_help(){

    printf("\n**HELP**\n");
    printf("*The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n");
    printf("*Diagonal moves are not allowed.\n");
    printf("*The user will input their desired move using the following keys:\n'a' for left, 'd' for right, 'w' for up, and 's' for down\n");
    printf("*The character's current position is indicated by a capital C, drawn at that location.\nThe current position of the door is indicated by a capital D at its location.\n");
    printf("*The game ends when the character reaches the door.\n\n");
}

void map_drawer(int c_x,int c_y,int d_x,int d_y,int N,int error_flag,int input_error_flag){
    //checks if it has to print some warnings
    if (error_flag){
        printf("Warning: You can't go through the borders\n\n");
    }
    if (input_error_flag){
        printf("Warning: Invalid input or diagonal move or multiple move tried\n\n");
    }

    printf("w:up s:down a:left d:right\n");//little instruction for each frame

    for(int i=0;i<2*N+1;i++){ //for the top of the map
        printf("-");
    }
    printf("\n");

    for(int y=1;y<=N;y++){ //main loops to draw the map. checks the coordinates to decide what to print

        for(int x=1;x<=N;x++){
            if(x==d_x && y==d_y){
                printf("|D");
            }else if(x==c_x && y==c_y){
                printf("|C");
            }else{
                printf("| ");
            }
        }
        printf("|");
        printf("\n");
    }

    for(int i=0;i<2*N+1;i++){ //for the bottom of the map
        printf("-");
    }
    printf("\n");


}

void map_cleaner(){ //just to make the previous map disappear.
    for(int a=0; a<30; a++){
        printf("\n");
    }
}

int control_func(int c_x,int c_y,int d_x,int d_y){
    
    int result=0;

    if(c_x==d_x && c_y==d_y){
        result=1;
    }
    //this is the condition for the gameplay to continue
    return result;
}

void gameplay(int first_c_x,int first_c_y,int d_x,int d_y,int N){
    //function to get user play the game for each frame
    int c_x= first_c_x;
    int c_y= first_c_y;
    int moves_count=0;
    char input,input_control_char;
    int error_flag=0;
    int input_error_flag=0;

    //the loop draws the map,takes input and decides depending on the input
    while (!(control_func(c_x,c_y,d_x,d_y))){
       

        map_cleaner(); //clears the terminal for each frame
        
        map_drawer(c_x,c_y,d_x,d_y,N,error_flag,input_error_flag); //draws the map with certain coordinates and errors

        error_flag=0; //resets the flags for each loop
        input_error_flag=0;

        scanf(" %c",&input);
        scanf("%c",&input_control_char); //to check if the user pressed 'enter' or tried to give multiple inputs at once
        
        if (input_control_char!='\n')//to check if the user presses 'enter' or tries to give multiple inputs at once
        {
            input_error_flag=1;
        } //if the user 
        
        if(input_error_flag==0){ //if user doesnt try to move diagonally just continues
            switch (input){
            case UP:
                c_y--;
                if (c_y==0 || c_y==N+1){ //all ifs above are to avoid moving through the borders
                    error_flag=1;
                    c_y++;
                }
                
                break;
            
            case DOWN:
                c_y++;
                if (c_y==0 || c_y==N+1){
                    error_flag=1;
                    c_y--;
                }
                break;
            
            case RIGHT:
                c_x++;
                if (c_x==0 || c_x==N+1){
                    error_flag=1;
                    c_x--;
                }
                break;
            
            case LEFT:
                c_x--;
                if (c_x==0 || c_x==N+1){
                    error_flag=1;
                    c_x++;
                }
                break;
            
            default:
                input_error_flag=1;
                break;
            }
        }
        //invalid inputs are not counted as a move
        if(error_flag==0 && input_error_flag==0){
            moves_count++;
        }

    }
    
    printf("\n\nGAME OVER\n%d moves made to the |D|oor.\n\n",moves_count);


}

void main_game_func(){
    //this function takes N value and gives first values of x and y coordinates of char and the door.
    srand(time(NULL));
    int N;

    while (1){

        printf("Please enter the map size between 5 and 10:");
        scanf(" %d",&N);

        if(N>=5 && N<=10){
            break;
        }else{
            printf("Invalid input\n");
        }

    }

    int first_c_x = (rand()%N)+1; 
    int first_c_y = (rand()%N)+1;
    
    int d_x=(rand()%N)+1;
    int d_y=(rand()%N)+1;
    
    
    /*
    +1 is needed because coordinates starts from 1 not 0.

    -  -  -  -  ->
    |1  2  3  4  5
    |2
    |3
    |4
    |5
    V

    */
    //starts the game frame by frame with first values of coordinates
   gameplay(first_c_x,first_c_y,d_x,d_y,N);



}

