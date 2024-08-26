#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct
{
    char table[3][4];
    char prev_move; //is used in auto_finish
    int move_count; //is also used in auto_finish
}board;


void file_saver(board *brdp);//saves the board to the file
void puzzle_generator(board *brdp,int*zero_row,int*zero_col);//generates random puzzle, and returns some infos about it
int is_solvable(int puzzle[]);//checks if the puzzle given is solvable
void board_print(board *brdp);//jsut prints the given board
int end_check(board *brdp);//check if the given board is the final board that ends the game
void best_score_saver(int new_best);//just saves the new best score
int best_score_checker();//checks if the score given is bigger than the present

void user_plays();//main function of option 1

void computer_plays();//main function of option 2

//recursative function that solves the given puzzle
//optimized to use less stack as much as possible
void auto_finish(board *brdp);
//in order to use less stack in auto_finish,some process are handled by this one
//so when this function ends,there are more stacks to use
void rand_mover(board *brdp);
#endif /* _UTIL_H_ */
