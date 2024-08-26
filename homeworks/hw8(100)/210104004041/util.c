#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <time.h>


//just saves the board to the txt files
void file_saver(board *brdp){

    FILE* fpt=fopen("board_saves.txt","a");
    fprintf(fpt,"*********\n");
    fprintf(fpt,"%c %c %c\n",brdp->table[0][0],brdp->table[0][1],brdp->table[0][2]);
    fprintf(fpt,"%c %c %c\n",brdp->table[1][0],brdp->table[1][1],brdp->table[1][2]);
    fprintf(fpt,"%c %c %c\n",brdp->table[2][0],brdp->table[2][1],brdp->table[2][2]);
    fprintf(fpt,"*********\n");

    fclose(fpt);
}

void puzzle_generator(board *brdp,int*zero_row,int*zero_col){

    
    int elements[]={1,2,3,4,5,6,7,8,0}; //0 corresponds to '_'.
    int temp_element;
    int r_index;
    srand(time(NULL));
    do
    {
        for (int i = 0; i < 9; i++) //mixes up the elements randomly
        {
            
            r_index= rand()% 9;
            temp_element=elements[i];
            elements[i]=elements[r_index];
            elements[r_index]=temp_element;
        }
    } while (!is_solvable(elements));

    //assigns the elements to the board
    int e_index=0;
    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            if (elements[e_index]!=0)
            {
                brdp->table[i][a]=(char)(elements[e_index]+48);//ascii table
            }else{
                brdp->table[i][a]='_'; //0 is passed as '_'
            }
            
            e_index++;
        }
        
    }
    //also outputs the information of the _ element to be used later
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (brdp->table[row][col]=='_')
            {
                *zero_col=col;
                *zero_row=row;
            }
            
        }
        
    }
    
    
}
//checks the number of inversions that must be even number in order to confirm that the given puzzle is solvable
int is_solvable(int puzzle[]){

    int inversions=0;

    for (int i = 0; i < 9; i++)
    {
        for (int a = i+1; a < 9; a++)
        {
            if (puzzle[i]>puzzle[a] && puzzle[a]!=0)//0 must be ignored
            {
                inversions++;
            }
            
        }
        
    }
    //printf("inversions:%d\n",inversions);
    int result=0;
    if (inversions%2==0 && inversions!=0)
    {
        result=1;
    }
    
    return result;

}
//just prints the given board when called
void board_print(board *brdp){

    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            printf("%c ",brdp->table[i][a]);
        }
        printf("\n");
    }
    printf("\n");
}
//if returns 1,the game ends
int end_check(board *brdp){

    int result=1;
    //the wanted table that ends the game
    char table[3][4]= {{'1','2','3'},{'4','5','6'},{'7','8','_'}};

    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            if (brdp->table[i][a]!=table[i][a]) result=0;
        }
    }
    return result;
}

void best_score_saver(int new_best){

    FILE*fpt=fopen("best_score.txt","w");
    fprintf(fpt,"%d",new_best);
    fclose(fpt);
}

int best_score_checker(){
    int best_scr=0;
    FILE*fpt=fopen("best_score.txt","r");

    if (fpt!=NULL)
    {
        
        fscanf(fpt, "%d",&best_scr);
        return best_scr;

    }else{
        printf("Best score file opening error!\n\n\a");
    }

    fclose(fpt);
}

void user_plays(){

    board curr_board;
    board *brd_p= &curr_board;

    int move_count=0;
    char input[4];
    int move_row,move_col;
    int zero_row,zero_col;
    int end_flag=1;

    puzzle_generator(brd_p,&zero_row,&zero_col);//generates random, solvable puzzle with some infoes about it
    board_print(brd_p);
    file_saver(brd_p);

    do
    {
        printf("movecount:%d\n",move_count);
        printf("Enter your move (number-direction, e.g., 2-R):");
        scanf("%s",input);

        //finds the coordinates of the move to check if it is legal
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (curr_board.table[row][col]==input[0])
                {
                    move_col=col;
                    move_row=row;
                }   
            }   
        }
        
        switch (input[2])
        {
        case 'U':
            if (zero_col==move_col && zero_row==move_row-1)
            {
                curr_board.table[zero_row][zero_col]=input[0];
                curr_board.table[move_row][move_col]='_';
                zero_col=move_col;
                zero_row=move_row;
                move_count++;
                file_saver(brd_p);
            }else{
                printf("Invalid input!!\n\n");
            }
            break;
        case 'D':
            if (zero_col==move_col && zero_row==move_row+1)
            {
                curr_board.table[zero_row][zero_col]=input[0];
                curr_board.table[move_row][move_col]='_';
                zero_col=move_col;
                zero_row=move_row;
                move_count++;
                file_saver(brd_p);
            }else{
                printf("Invalid input!!\n\n");
            }
            break;
        case 'R':
            if (zero_col==move_col+1 && zero_row==move_row)
            {
                curr_board.table[zero_row][zero_col]=input[0];
                curr_board.table[move_row][move_col]='_';
                zero_col=move_col;
                zero_row=move_row;
                move_count++;
                file_saver(brd_p);
            }else{
                printf("Invalid input!!\n\n");
            }
            break;
        case 'L':
            if (zero_col==move_col-1 && zero_row==move_row)
            {
                curr_board.table[zero_row][zero_col]=input[0];
                curr_board.table[move_row][move_col]='_';
                zero_col=move_col;
                zero_row=move_row;
                move_count++;
                file_saver(brd_p);
            }else{
                printf("Invalid input!!\n\n");
            }
            break;
        default:
            printf("Invalid input!\n\n");
            break;
        }

        board_print(brd_p);
        
        end_flag= end_check(brd_p);


    } while (!end_flag);
    
    printf("Congratulations you solved the puzzle!!\n%d moves made\n\n",move_count);
    int curr_score= 1000- 10*move_count;
    int best=best_score_checker();
    if (curr_score>best){
        best_score_saver(curr_score);
        printf("THE NEW BEST SCORE: %d !!!\n",curr_score);
    }


}

void computer_plays(){

    board curr_board;
    board *board_p= &curr_board;
    curr_board.move_count=0;
    

    int zero_row,zero_col; //useless here but necessary for the puzzlegenerator
    puzzle_generator(board_p,&zero_row,&zero_col);
    
    board initialboard; //to show the initial board at the end of the process
    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            initialboard.table[i][a]=curr_board.table[i][a];
        }
    }
    
    //clock_t start_t,end_t; //those were used in tests
    //start_t=clock();
    auto_finish(board_p); //the recursative function starts
    //end_t=clock();
    //printf("gecen sure: %lf\n",(double)(end_t-start_t)/ CLOCKS_PER_SEC);

    printf("Computer made %d moves\n",curr_board.move_count);
    printf("This was the first board:\n");
    board_print(&initialboard);

}
//those are some notes for myself, i didnt want to delete :D
//first find legal moves possible
//randomly do one
//if bittiyse printle
//if bitmediyse recursion
//yandan bir fonksiyon acip kapanirsa staack temiz kalir
void auto_finish(board *brdp){
    //srand(time(NULL));

    file_saver(brdp);
    if (end_check(brdp))
    {
        board_print(brdp);
    }else{
        rand_mover(brdp);//in order to use less stack, some processes are handled by this function
        //so the recursion before it exceed the stack limit is increased
        (brdp->move_count)++;
        //printf("works\n");
        //board_print(brdp); //were used in tests
        auto_finish(brdp);
    }
    


}

//makes legal random moves, and doesnt repeat the previous move
void rand_mover(board *brdp){

    //we need coordinates of '_'
    int zero_row,zero_col;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (brdp->table[row][col]=='_')
            {
                zero_col=col;
                zero_row=row;
            }
        }
    }
    //finding legal moves possible
    int legal_move_coordinates[4][2]; //there can be max 4 possible moves and each move 2 coordinate information
    int legal_move_count=0;
    //finds all legal moves except the previous one
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (brdp->table[row][col]!=brdp->prev_move)//ignores the previously moved element
            {
                if(row==zero_row-1 && col==zero_col){
                    legal_move_coordinates[legal_move_count][0]=row;
                    legal_move_coordinates[legal_move_count][1]=col;
                    legal_move_count++;
                }else if(row==zero_row+1 && col==zero_col){
                    legal_move_coordinates[legal_move_count][0]=row;
                    legal_move_coordinates[legal_move_count][1]=col;
                    legal_move_count++;
                }else if(col==zero_col-1 && row==zero_row){
                    legal_move_coordinates[legal_move_count][0]=row;
                    legal_move_coordinates[legal_move_count][1]=col;
                    legal_move_count++;
                }else if(col==zero_col+1 && row==zero_row){
                    legal_move_coordinates[legal_move_count][0]=row;
                    legal_move_coordinates[legal_move_count][1]=col;
                    legal_move_count++;
                }
            }
        }
    }

    //chooses randomly one of the legal moves
    int rand_index= rand() % (legal_move_count);
    //printf("randindex:%d lgmovecount:%d\n",rand_index,legal_move_count);
    int move_row= legal_move_coordinates[rand_index][0];
    int move_col= legal_move_coordinates[rand_index][1];
    //the move made is the new previous move that is going to be ignored during the next move
    brdp->prev_move=brdp->table[move_row][move_col];
    brdp->table[zero_row][zero_col]=brdp->prev_move;
    brdp->table[move_row][move_col]='_';

}

//210104004041