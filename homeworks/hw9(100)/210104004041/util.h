#ifndef _UTIL_H_
#define _UTIL_H_


//the cells of the board
typedef struct 
{
    char type;
    int value;
}block;

//the points of the snake
typedef struct 
{
    int row,col;
}point;


block *** init_board();
void play(block ***board);

void draw_board(block ***board,point *snake,const int snk_len);
void move(point **snake,const int snk_len,point* prev_head);
int check_status(const point *snake,block ***board,const int snk_len);
void update(point **snake,block ***board,int *snk_len,int move_count,point prev_head );

#endif /* _UTIL_H_ */
