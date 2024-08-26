#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct
{
    char table[3][4];
}board;


void file_saver(board *brdp);
void puzzle_generator(board *brdp,int*zero_row,int*zero_col);
int is_solvable(int puzzle[]);
void board_print(board *brdp);
int end_check(board *brdp);
void best_score_saver(int new_best);
int best_score_checker();

void user_plays();

void computer_plays();
void auto_finish(board *brdp,char *previous_move,int*movecount);
void rand_mover(board *brdp,char *repeat);
#endif /* _UTIL_H_ */
