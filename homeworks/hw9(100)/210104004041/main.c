#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

#define MAX_HEIGHT 20
#define BOARD_LIM_X 10
#define BOARD_LIM_Y 10


int main(){

    srand(time(NULL));
    //printf("WASD keys are to move.\nYou can not go through an obstacle that is bigger than your snake\n\n");
    block ***board;

    board=init_board();

    play(board);


    //cleaning starting from the end
    for (int i = 0; i < BOARD_LIM_X; i++)
    {
        for (int a = 0; a < BOARD_LIM_Y; a++)
        {
            free(board[i][a]);
        }
        free(board[i]);
    }
    free(board);


    return 0;
}

