#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <time.h>



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
                brdp->table[i][a]=(char)(elements[e_index]+48);
            }else{
                brdp->table[i][a]='_';
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

    board initialboard;

    int zero_row,zero_col; //useless but necessary for the puzzlegenerator
    puzzle_generator(board_p,&zero_row,&zero_col);

    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            initialboard.table[i][a]=curr_board.table[i][a];
        }
        
    }
    

    //board_print(board_p);
    char first_char='B';//necessary to fit the consept of auto_finish
    int move=0;
    auto_finish(board_p,&first_char,&move);

    printf("Computer made %d moves\n",move);
    printf("This was the first board:\n");
    board_print(&initialboard);

}
//first find legal moves possible
//randomly do one
//if bittiyse printle
//if bitmediyse recursion
//yandan bir fonksiyon açıp kapanırsa staack temiz kalır
void auto_finish(board *brdp,char *previous_move,int *movecount){
    //srand(time(NULL));

    file_saver(brdp);
    if (end_check(brdp))
    {
        board_print(brdp);
    }else{
        rand_mover(brdp,previous_move);
        (*movecount)++;
        //printf("works\n");
        //board_print(brdp);
        auto_finish(brdp,previous_move,movecount);
    }
    


}

void rand_mover(board *brdp,char *repeat){

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
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (brdp->table[row][col]!=*repeat)//ignores the previously moved element
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
    //choosing random move
    
    int rand_index= rand() % (legal_move_count);
    //printf("randindex:%d lgmovecount:%d\n",rand_index,legal_move_count);
    int move_row= legal_move_coordinates[rand_index][0];
    int move_col= legal_move_coordinates[rand_index][1];

    *repeat=brdp->table[move_row][move_col];
    brdp->table[zero_row][zero_col]=*repeat;
    brdp->table[move_row][move_col]='_';

}

