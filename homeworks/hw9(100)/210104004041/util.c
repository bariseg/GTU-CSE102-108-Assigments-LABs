#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"


#define MAX_HEIGHT 9
#define BOARD_LIM_X 10
#define BOARD_LIM_Y 10

#define EMPTY 'e'
#define OBSTACLE 'o'
#define BAIT 'b'

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'



block *** init_board(){

    //allocating memory for the board
    block ***initial_board;
    initial_board= (block***)malloc(BOARD_LIM_X * sizeof(block**));
    for (int i = 0; i < BOARD_LIM_X; i++)
    {
        initial_board[i] = (block**)malloc(BOARD_LIM_Y * sizeof(block*));
        for (int a = 0; a < BOARD_LIM_Y; a++)
        {
            initial_board[i][a]= (block*)malloc(1 * sizeof(block)); //initially only 1 place is hold for possible block
        }
    }

    //all cells are empty at first
    for (int x = 0; x < BOARD_LIM_X; x++)
    {
        for (int y = 0; y < BOARD_LIM_Y; y++)
        {
            initial_board[x][y]->type=EMPTY;
            initial_board[x][y]->value=0;
            
        }
    }

    srand(time(NULL));

    int bait_rand_x=0;
    int bait_rand_y=0;
    //preventing the leftop corner from being bait
    while (bait_rand_x==0 && bait_rand_y==0)
    {
        bait_rand_x= rand() % 10;
        bait_rand_y= rand() % 10;
    }

    int obs_rand_x=0;
    int obs_rand_y=0;
    //preventing the leftop corner from being obstacle.
    while ((obs_rand_x==0 && obs_rand_y==0) || (obs_rand_x==bait_rand_x && obs_rand_y==bait_rand_y))
    {
        obs_rand_x= rand() % 10;
        obs_rand_y= rand() % 10;
    }

    int obs_height= (rand() % (MAX_HEIGHT)) +1 ;
    

    //printf("bait:%dx %dy\nobs:%dx %dy\n",bait_rand_x,bait_rand_y,obs_rand_x,obs_rand_y);

    //assigning bait and obstacle
    initial_board[bait_rand_x][bait_rand_y]->type=BAIT;
    initial_board[bait_rand_x][bait_rand_y]->value=0;


    initial_board[obs_rand_x][obs_rand_y][0].type=OBSTACLE;
    initial_board[obs_rand_x][obs_rand_y][0].value=obs_height;//value holds total block count in the cell
    //allocating new memory cells
    initial_board[obs_rand_x][obs_rand_y]=(block*)realloc(initial_board[obs_rand_x][obs_rand_y],obs_height*sizeof(block));
    for (int i = 1; i < obs_height; i++)
    {   //nesting blocks
        initial_board[obs_rand_x][obs_rand_y][i].type=OBSTACLE;
        initial_board[obs_rand_x][obs_rand_y][i].value=1;
    }

    
    return initial_board;

}

void draw_board(block ***board,point *snake,const int snk_len){

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");

    //top line
    for (int i = 0; i < 10; i++) printf(" -");
    
    printf("\n");

    int no_snake_part;
    for (int row = 0; row < 10; row++)
    {
        printf("|");
        for (int col = 0; col < 10; col++)
        {
            no_snake_part=1;
            
            if (row==snake[0].row && col==snake[0].col)
            {
                printf("O ");
                no_snake_part=0;
            }else{
                //checks if there is any snake body part in the coordinates
                for (int i = 1; i < snk_len; i++)
                {
                    if (snake[i].row==row && snake[i].col==col)
                    {
                        printf("X ");
                        no_snake_part=0;
                    }
                }
            }
            if (no_snake_part){
                if(board[row][col]->type==EMPTY){
                    printf("  ");
                }else if (board[row][col]->type==OBSTACLE){
                    printf("%d ",board[row][col]->value);
                }else if(board[row][col]->type==BAIT){
                    printf(". ");
                }
            }
            
        }
        printf("|\n");
    }

    for (int i = 0; i < 10; i++) printf(" -");

    printf("\n");
}

void move(point **snake, const int snk_len, point* prev_head) {

    char move;
    printf(">");
    scanf(" %c", &move);

    point temp_head;
    temp_head.row = (*snake)[0].row;
    temp_head.col = (*snake)[0].col;

    switch (move) {
        case UP:
            temp_head.row--;
            break;
        case DOWN:
            temp_head.row++;
            break;
        case LEFT:
            temp_head.col--;
            break;
        case RIGHT:
            temp_head.col++;
            break;
        default:
            printf("Invalid input!!\n");
            return;
    }

    //if snake len is 1 then there is no body to compare
    prev_head->row=(*snake)[0].row ;
    prev_head->col=(*snake)[0].col;
    if (snk_len == 1 || (temp_head.row != (*snake)[1].row || temp_head.col != (*snake)[1].col)) {
        (*snake)[0].col = temp_head.col;
        (*snake)[0].row = temp_head.row;
    }

    //printf("%d %d\n%d %d\n", (*snake)[0].row, (*snake)[0].col, (*snake)[1].row, (*snake)[1].col);


}

//kendine değerse, duvara vurursa, büyükeşit engele vurursa
int check_status(const point *snake,block ***board,const int snk_len){

    int result=0;
    //for easier reading
    int head_row= snake[0].row;
    int head_col= snake[0].col;

    //wall check //obstacle check //body check
    if (head_row<0 || head_row>9 || head_col<0 || head_col>9)
    {
        result=1;
        printf("You bumped into the walls!!!\n\a");
    }else if(board[head_row][head_col]->type==OBSTACLE && board[head_row][head_col]->value >= snk_len){
        result=1;
        printf("You bumped an obstacle that is bigger than you!!!\n\a");
    }else{
        int b_row,b_col; //body parts coordinates
        for (int i = 1; i < snk_len; i++)
        {
            b_row= snake[i].row;
            b_col= snake[i].col;
            if (head_col==b_col && head_row==b_row){
                result=1;
                printf("You bumped into yourself!!!\n\a");
            }
        }
    }

    return result;
}

void update(point **snake,block ***board,int *snk_len,int move_count,point prev_head ){

    

    //if move function ignored the move user tried to do, update shouldnt do anything
    if (prev_head.row!=(*snake)[0].row || prev_head.col!=(*snake)[0].col)
    {
        //just shifting the body
        if (board[(*snake)[0].row][(*snake)[0].col]->type==EMPTY)
        {
            for (int i = (*snk_len)-1; i > 1 ; i--)
            {
                (*snake)[i].row=(*snake)[i-1].row;
                (*snake)[i].col=(*snake)[i-1].col;
            }
            (*snake)[1].row= prev_head.row;
            (*snake)[1].col= prev_head.col;

        //the new body part is added between head and the first part of the body    
        }else if(board[(*snake)[0].row][(*snake)[0].col]->type==BAIT){ 

            board[(*snake)[0].row][(*snake)[0].col]->type=EMPTY;
            board[(*snake)[0].row][(*snake)[0].col]->value=0;

            (*snk_len)++;
            (*snake)=(point*)realloc((*snake),(*snk_len)*sizeof(point));

            //tranferring rows and cols to the next element of the body of the snake
            for (int i = (*snk_len)-1; i > 1 ; i--)
            {
                (*snake)[i].row=(*snake)[i-1].row;
                (*snake)[i].col=(*snake)[i-1].col;
            }
            // snake[1] is the new part of the body
            (*snake)[1].row= prev_head.row;
            (*snake)[1].col= prev_head.col;

            //adding new bait that is not on the snakes body
            int new_bait_row,new_bait_col;
            int valid_bait=1;
            do
            {   
                valid_bait=1;
                new_bait_row=rand()%10;
                new_bait_col=rand()%10;

                for (int i = 0; i < *snk_len; i++)
                {
                    if ((*snake)[i].row==new_bait_row && (*snake)[i].col==new_bait_col)
                    {
                        valid_bait=0;
                        break;
                    }
                }
                //bait cant be created on a obstacle
                if (board[new_bait_row][new_bait_col][0].type==OBSTACLE) valid_bait=0;
                
            } while (!valid_bait);
            board[new_bait_row][new_bait_col]->type=BAIT;
            board[new_bait_row][new_bait_col]->value=0;
            


        //destroying the obstacle little than the snake
        }else if(board[(*snake)[0].row][(*snake)[0].col]->type==OBSTACLE && board[(*snake)[0].row][(*snake)[0].col]->value < *snk_len){
            board[(*snake)[0].row][(*snake)[0].col]->type=EMPTY;
            board[(*snake)[0].row][(*snake)[0].col]->value=0;
            //shifting part
            for (int i = (*snk_len)-1; i > 1 ; i--)
            {
                (*snake)[i].row=(*snake)[i-1].row;
                (*snake)[i].col=(*snake)[i-1].col;
            }
            (*snake)[1].row= prev_head.row;
            (*snake)[1].col= prev_head.col;

        }


        int obstacle_count=0; // i didnt want to use this value in function parameters
        for (int i = 0; i < BOARD_LIM_X; i++)
        {
            for (int a = 0; a < BOARD_LIM_Y; a++)
            {
                if (board[i][a]->type==OBSTACLE) obstacle_count++;
            }
        }
        //printf("obstacle count: %d\n",obstacle_count);

        if (move_count%5==0)
        {
            if (obstacle_count<3)
            {
                int valid_coordinates;
                int obs_row,obs_col;
                do
                {   
                    valid_coordinates=1;
                    obs_row= rand() % 10;
                    obs_col= rand() % 10;
                    //printf("r:%d c:%d\n",obs_row,obs_col);
                    //avoiding the new obstacle to destroy the bait
                    if (board[obs_row][obs_col]->type==BAIT){
                        valid_coordinates=0;
                    }else{
                        for (int i = 0; i < (*snk_len); i++)
                            {
                                if ((*snake)[i].row==obs_row && (*snake)[i].col==obs_col)
                                {
                                    valid_coordinates=0;
                                    break;
                                }
                            }
                    }    
                } while (!valid_coordinates);

                int obs_height=(rand()% MAX_HEIGHT)+1;
                board[obs_row][obs_col][0].type=OBSTACLE;
                board[obs_row][obs_col][0].value= obs_height;
                board[obs_row][obs_col]=(block*)realloc(board[obs_row][obs_col],obs_height*sizeof(block));
                for (int i = 1; i < obs_height; i++)
                {
                    board[obs_row][obs_col][i].type=OBSTACLE;
                    board[obs_row][obs_col][i].value=1;
                }
                


            }else{ //if there are 3 obstacles, the heights are incremented starting from the closest to leftop corner
                int break_flag=0;
                int curr_heigth=0;
                for (int i = 0; i < BOARD_LIM_X; i++)
                {
                    for (int a = 0; a < BOARD_LIM_Y; a++)
                    {
                        if (board[i][a]->type==OBSTACLE && board[i][a]->value<MAX_HEIGHT){
                            curr_heigth=board[i][a][0].value;
                            curr_heigth++;
                            board[i][a][0].value=curr_heigth;
                            board[i][a]= (block*)realloc(board[i][a],curr_heigth*sizeof(block));
                            board[i][a][curr_heigth-1].type=OBSTACLE;
                            board[i][a][curr_heigth-1].value=1; //adding new block
                            break_flag=1;
                            break;
                        }
                    }
                    if (break_flag) break;
                }
            }
            
        }
    }
}


void play(block ***board){
    
    int move_count=0;
    int snake_len=1;
    point *snake=(point*)malloc(snake_len*sizeof(point));
    point previous_head; //this is used to update the snakes body,shifting the body 
    //initially snake is at the left top corner
    snake[0].row=0;
    snake[0].col=0;

    int end_flag=0;

    draw_board(board,snake,snake_len);
    
    while (!end_flag)
    {    
        move(&snake,snake_len,&previous_head);
        move_count++;
        
        end_flag= check_status(snake, board, snake_len);
        
        if (!end_flag){
            update(&snake,board,&snake_len,move_count,previous_head);
            draw_board(board,snake,snake_len);
        }  
        

    }

    free(snake);

}

