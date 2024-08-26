#include <stdio.h>
#include <math.h>

//part1
#define UPPER_TOP_NUM 90
#define UPPER_BOTTOM_NUM 65
#define LOWER_TOP_NUM 122
#define LOWER_BOTTOM_NUM 97

int letter_case_conversion(int ascii_num); //lowercase letters are converted into uppercase
void letter_frequency(); //main function of part1. reads file, converts letters(if necessary), and prints the result


//part2
typedef enum {RED,GREEN,BLUE,YELLOW,ORANGE} Color_type;

Color_type mixing_two_colors(Color_type color1,Color_type color2); //this function is goingto be the 3th argument of colorMixer
void colorMixer(Color_type color1,Color_type color2, Color_type mixer(Color_type f_color1,Color_type f_color2)); //this is one of the functions wanted
void part2_main_func();//main function of part2. takes color inputs and calls colorMixer with a function as a argument in it.

//part3
#define EMPTY 0
#define X 1
#define O 2
int winner_check(int current_board[][3]);//checks if there is a winner after each move
void board_printer(int current_board[][3]); //compiler said that 2d arrays has to have bounds for all dimensions except the first
void tic_tac_toe();

int main(){

    //part1
    letter_frequency();

    //part2
    part2_main_func();


    //part3
    tic_tac_toe();

    
    return 0;
}

//part1
int letter_case_conversion(int ascii_num){

    int upper_ascii_number= ascii_num- 32;

    return upper_ascii_number;

}

void letter_frequency(){

    char filename[30];

    printf("enter the file name: ");
    scanf("%s",filename);

    FILE *fp= fopen(filename,"r"); //file pointer
    
    
    char char_read; //the variable stores what code reads from file.
    int letter_counts[26]; //the array stores number of each letter frequency.
    int ascii_int_of_char;

    //fills every cell with 0
    for (int a = 0; a < 26; a++) //if i dont do this, the result for letter that dont exist is something like 18529158
    {
        letter_counts[a]=0;
    }
    
    while ((char_read= fgetc(fp))!=EOF){ //reads the file till the EOF

        ascii_int_of_char= (int)char_read; //converts chars into integers depending on ascii table

        if (ascii_int_of_char>=LOWER_BOTTOM_NUM && ascii_int_of_char<=LOWER_TOP_NUM){ //checks if the letter is ab..z and lower case
        
            ascii_int_of_char= letter_case_conversion(ascii_int_of_char); //lowercase letters are converted into uppercase

        }
        
        if(ascii_int_of_char>=UPPER_BOTTOM_NUM && ascii_int_of_char<=UPPER_TOP_NUM){ 
        //checks if the char_read is a letter ABCD..Z ; if it is, increases the number of the letter count in the array.
        // [65-ascii_int_of_char] corresponds the index of the letter. So i dont have to define them separately

            letter_counts[ascii_int_of_char-65]++ ;

        }

    }

    fclose(fp); //the file is not needed anymore
    
    for (int i = UPPER_BOTTOM_NUM ; i < UPPER_TOP_NUM; i++) // i moves from 65 to 90
    {
        char_read= (char) i; //char value of i

        printf("%c: %d\n",char_read,letter_counts[i-UPPER_BOTTOM_NUM]); // i-upper_bottom_num corresponds for ex. 75-65= 10 which is the index of the number of 'K' 
    }

}


//part2
Color_type mixing_two_colors(Color_type color1,Color_type color2){

    double vector1[3],vector2[3],vector_result[3];
    
    double all_colors_vectors[5][3]= {
        {1, 0, 0},        //red
        {0, 1, 0},        //green
        {0, 0, 1},        //blue
        {0.5, 0.5, 0},    //yellow
        {0.5, 0.4, 0.2}   //orange
    };

    Color_type result;


    switch (color1){ //assigns the vector depending on the color. each color is representing by a vector.
    case RED:

        for (int i = 0; i < 3; i++){
            vector1[i]=all_colors_vectors[0][i];
        }
        
        break;

    case GREEN:

        for (int i = 0; i < 3; i++){
            vector1[i]=all_colors_vectors[1][i];
        }
        break;

    case BLUE:
            
        for (int i = 0; i < 3; i++){
            vector1[i]=all_colors_vectors[2][i];
        }
        break;

    case YELLOW:
            
        for (int i = 0; i < 3; i++){
            vector1[i]=all_colors_vectors[3][i];
        }
        break;

    case ORANGE:
            
        for (int i = 0; i < 3; i++){
            vector1[i]=all_colors_vectors[4][i];
        }
        break;

    default:
        printf("Invalid color1 detected!!\n");

        break;
    }

    switch (color2){
    case RED:

        for (int i = 0; i < 3; i++){
            vector2[i]=all_colors_vectors[0][i];
        }
        
        break;

    case GREEN:

        for (int i = 0; i < 3; i++){
            vector2[i]=all_colors_vectors[1][i];
        }
        break;

    case BLUE:
            
        for (int i = 0; i < 3; i++){
            vector2[i]=all_colors_vectors[2][i];
        }
        break;

    case YELLOW:
            
        for (int i = 0; i < 3; i++){
            vector2[i]=all_colors_vectors[3][i];
        }
        break;

    case ORANGE:
            
        for (int i = 0; i < 3; i++){
            vector2[i]=all_colors_vectors[4][i];
        }
        break;

    default:
        printf("Invalid color2 detected!!\n");

        break;
    }




    vector_result[0]= (vector1[0]+vector2[0])/2;
    vector_result[1]= (vector1[1]+vector2[1])/2;
    vector_result[2]= (vector1[2]+vector2[2])/2;

    printf("The Mixed Color Vector is [%.2lf, %.2lf, %.2lf]\n",vector_result[0],vector_result[1],vector_result[2]);
    
    double distances[5]= {0,0,0,0,0} ; //the distance for each color is stored in this array
    double temp_distance;

    //this loop calculates the distances of each color from the result_color
    for (int colourindex = 0; colourindex < 5; colourindex++){ //for each color, distance is calculated

        temp_distance=0;

        for (int vectorindex = 0; vectorindex < 3; vectorindex++){ 

            temp_distance= all_colors_vectors[colourindex][vectorindex] - vector_result[vectorindex] ;
            
            distances[colourindex]= distances[colourindex] + (temp_distance*temp_distance);

        }

        distances[colourindex]= sqrt(distances[colourindex]) ;

        //printf("%.2lf\n",distances[colourindex]); 

    }

    int smallest_dist_index=0;
    double min=distances[0];
    for (int i = 1; i < 5; i++){ //finds the index of closest color

        if (distances[i]<min){
            min= distances[i];
            smallest_dist_index=i;
        }
        

    }
    

    switch (smallest_dist_index) //converts the index to color_type variable that is result
    {
    case 0:
        result=RED;
        break;
    
    case 1:
        result=GREEN;
        break;
    
    case 2:
        result=BLUE;
        break;
    
    case 3:
        result=YELLOW;
        break;
    
    case 4:
        result=ORANGE;
        break;
    
    default:
        printf("something went wrong in mixingtwocolors!\n");
        break;
    }


    return result; //returns color_type result

}

void colorMixer(Color_type color1,Color_type color2, Color_type mixer(Color_type f_color1,Color_type f_color2)){

    Color_type mixed_result;

    mixed_result= mixer(color1,color2); //calls mixer function from argument3

    switch (mixed_result){
    case RED:
        printf("closest or equal to RED \n");
        break;
    
    case GREEN:
        printf("closest or equal to  GREEN \n");
        break;
    
    case BLUE:
        printf("closest or equal to BLUE \n");
        break;
    
    case YELLOW:
        printf("closest or equal to YELLOW \n");
        break;
    
    case ORANGE:
        printf("closest or equal to ORANGE \n");
        break;
    
    }
    
    

}

void part2_main_func(){ //gets inouts , checks inputs , calls colormixer

    char c1,c2;
    Color_type color1,color2;
    int input1_checker,input2_checker;

    printf("\n\tCOLOR MIXER PROGRAM\n\n");

    do
    {
        input1_checker=0;
        input2_checker=0;

        printf("Enter Color 1 (r,g,b,y,o):");
        scanf(" %c",&c1);

        printf("Enter Color 2 (r,g,b,y,o):");
        scanf(" %c",&c2);

        switch (c1){
        case 'r':
            color1=RED;
            break;
        
        case 'g':
            color1=GREEN;
            break;
        
        case 'b':
            color1=BLUE;
            break;
        
        case 'y':
            color1=YELLOW;
            break;
        
        case 'o':
            color1=ORANGE;
            break;
        
        default:
            printf("Invalid color1 input detected!!\n\n");
            input1_checker=1;
            break;
        }

        switch (c2){
        case 'r':
            color2=RED;
            break;
        
        case 'g':
            color2=GREEN;
            break;
        
        case 'b':
            color2=BLUE;
            break;
        
        case 'y':
            color2=YELLOW;
            break;
        
        case 'o':
            color2=ORANGE;
            break;
        
        default:
            printf("Invalid color2 input detected!!\n\n");
            input2_checker=1;
            break;
        }

    } while (input1_checker || input2_checker);
    
    colorMixer(color1,color2,mixing_two_colors);
}


//part3***************
int winner_check(int current_board[][3]){
    int game_end_flag=0;


     //checks diagonal cells if they are the same and not 0
    if (current_board[0][0]!=0 && (current_board[0][0]==current_board[1][1] && current_board[0][0]==current_board[2][2]))
    {
        printf("Player%d WON!!\n\n",current_board[0][0]);
        game_end_flag=1;

    }else if (current_board[0][2]!=0 && (current_board[0][2]==current_board[1][1] && current_board[0][2]==current_board[2][0]))
    {
        printf("Player%d WON!!\n\n",current_board[0][2]);
        game_end_flag=1;
    }
    
    if (game_end_flag==0){ //if the conditions above are not satisfied yet, then i need to check rows and columns
    
        for (int i = 0; i < 3; i++){

            if (current_board[i][0]!=0 && (current_board[i][0]==current_board[i][1] && current_board[i][0]==current_board[i][2])){
                //checks the raw if all cells are the same and not 0
                printf("Player%d WON!!\n\n",current_board[i][0]);
                game_end_flag=1;
                break;

            }else if (current_board[0][i]!=0 && (current_board[0][i]==current_board[1][i] && current_board[0][i]==current_board[2][i])){
                //checks the column if all cells are the same and not 0
                printf("Player%d WON\n\n",current_board[0][i]);
                game_end_flag=1;
                break;
            }
            
        }
    
    }

    int tie_check=1;
    if (game_end_flag==0){

        for (int r = 0; r < 3; r++){ //looks for an empty cell to continue the game
            for (int c = 0; c < 3; c++){
                if (current_board[r][c]==0){ //if there is any 0 on the board then game needs to continue.
                    tie_check=0;
                    game_end_flag=0;
                    break;
                }
            }
        }

        if (tie_check){
        printf("Board is full! TIE!\n\n");
        game_end_flag=1;
        }
    
    }
    
    
    return game_end_flag;

}

void board_printer(int current_board[][3]){ //prints the current board

    printf("\n\n\n");

    for (int y = 0; y <= 2; y++)
    {
        for (int x = 0; x <= 2; x++)
        {
            switch (current_board[y][x])
            {
            case X:
                printf("X ");
                break;
            
            case O:
                printf("O ");
                break;
            
            case EMPTY:
                printf("_ ");
                break;
            
            }
            
        }
        printf("\n");


    }
    printf("\n\n\n");
    

}

void tic_tac_toe(){ //takes inputs, checks if the input is possible, updates and prints the board, checks if there is a winner.
                    //asks for a new game
    int board_array[][3]= {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };

    int player_y,player_x; //player_y for raw number, x for column number
    int input_check;
    int game_end_check=0;
    char new_game_check;
    
    printf("\t***TIC-TAC-TOE GAME***\n\n");
    do
    {
        
        do{ //getting input for player1 X

            printf("Player1(X) enter your move(row col):");
            scanf("%d %d",&player_y,&player_x);

            input_check= (player_y<=3 && player_y>=1) && (player_x<=3 && player_x>=1) ;

            player_y--; //user inputs 1 2 3 but index has to be 0 1 2
            player_x--;

            if ((board_array[player_y][player_x]!=0) || !input_check) {

                printf("\aInvalid input or the coordinates has been occupied!!!\n\n");
                
            }else{

                board_array[player_y][player_x]= X;
                board_printer(board_array);
                break;
            }

        } while (1);

        game_end_check= winner_check(board_array); //checks if the player1 won
    

        
        if(game_end_check==0){ //before player2 inputs. the game must be check if its finished. while(game_end_check) checks for player1

            do{
                printf("Player2(O) enter your move(row col):");
                scanf("%d %d",&player_y,&player_x);

                input_check= (player_y<=3 && player_y>=1) && (player_x<=3 && player_x>=1) ;

                player_y--; //user inputs 1 2 3 but index has to be 0 1 2
                player_x--;

                
                
                if ((board_array[player_y][player_x]!=0) || !input_check) {

                printf("\aInvalid input or the coordinates has been occupied!!!\n\n");
                
                }else{

                    board_array[player_y][player_x]= O;
                    board_printer(board_array);
                    break;
                }
                

            } while (1);
        
            game_end_check= winner_check(board_array);
        }
            

        //if the game has finished, resets tthe board, and asks for a new game
        if (game_end_check){ //if the game has finished. reset the board and ask for a new game
            
            for (int i = 0; i < 3; i++){ //reset the board
                for (int a = 0; a < 3; a++){
                    board_array[i][a]= 0;
                }
                
            }

            int invalid_check=0;
            do{
                printf("New game? (Y/N)");
                scanf(" %c",&new_game_check);

                switch (new_game_check){

                case 'Y':
                    printf("New game is starting!!\n\n");
                    game_end_check=0;
                    break;

                case 'N':
                    printf("Exiting!!\n\n");
                    
                    break;
                
                default:
                    printf("Invalid input!!\n\n");
                    invalid_check=1;
                    break;
                }

            } while (invalid_check);
            
        }
        
    } while (game_end_check==0);
    

}

