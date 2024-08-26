#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//id for each product //those ids are sent to price_reader.
#define EXIT 0
#define CORBA 1
#define KEBAP 2
#define BEYTI 3
#define LAHMACUN 4
#define PIDE 5
#define DONER 6
#define KCITIR 7
#define KUNEFE 8
#define SUTLAC 9
#define TRILICE 10
#define KOLA 11
#define SU 12

//for the switch statement in part2
#define STONE '1'
#define PAPER '2'
#define SCISSORS '3'

//part1 functions
double price_reader(int product_id);//reads prices from the menu for each product ordered
void order_take_save(); //takes order and saves it simultaneously in the receipt.txt file created(if doesnt exits yet)
void menu_printer(); //just reads menu.txt and prints it
void restaurant_order_function();//main function of part1. calls other functions in order of algorithm.

//part2 functions
char computer_selection(); //returns the decision that computer makes.
void winner_finder(int comp_dec,int user_dec); //checks the winner and prints
void rock_paper_sci(); //main function of part2. takes user input, calls other functions in order of algorithm


int main(){ // main func includes main functions of each part,so that you can try them seperately.

    //part1
    restaurant_order_function();


    //part2
    //rock_paper_sci();


    return 0;
}



void receipt_printer(){ //prints the compleated receipt from receipt.txt

    FILE *receipt= fopen("receipt.txt","r");
    
    char c; //the receipt will be read char by char instead of string

    do{ //reads and prints the final receipt untill the EOF
        
        c= fgetc(receipt);
        printf("%c",c);

    } while (c!=EOF);
    printf("\n");
    fclose(receipt);

}

void menu_printer(){ //reads menu.txt and prints it
    FILE *menu= fopen("menu.txt","r");
    
    char c; //the menu will be read char by char

    do{//reads the menu untill the EOF
        
        c= fgetc(menu);
        printf("%c",c);

    } while (c!=EOF);
    printf("\n");
    fclose(menu);

}


double price_reader(int product_id){ //reads the price for the product indicated by its product_id
    double product_price,deneme;
    char space_chars;

    FILE *menu= fopen("menu.txt","r");

    
    for (int i = 0; i < 57; i++){ //gets the cursor in menu.txt to near the price of the first product.

        space_chars= fgetc(menu);
        
    }

    
    for (int a = 1; a <= product_id; a++){//depending on the product_id, reads prices and gets the cursor to the next price
        
        fscanf(menu,"%lf",&product_price);

        for (int b = 1; b <= 30; b++){//gets the cursor to the next price
        
            space_chars= fgetc(menu);
        }
        

    }
    fclose(menu);
    return product_price;

    
}


void order_take_save(){ //takes the users order and saves it simultaneously in the receipt.txt file

    FILE *receipt = fopen("receipt.txt","a+");

    int choice,serving_count;
    double total_price=0;

    time_t t = time(NULL);

    fprintf(receipt,"210104004041%28s\n",ctime(&t));
    fprintf(receipt,"---------------------------------------\n");
    fprintf(receipt,"Product                       Price(TL)\n");
    fprintf(receipt,"---------------------------------------\n\n");
    
    //this loop takes order untill the user finishes his/her order.
    do{ 
        printf("Please choose a product (1-12)(0 for exit):");
        scanf(" %d",&choice);

        if(choice!=0 && (choice<=12 && choice>= 0)){ //if the first input is 0, then program doesnt ask for servings count
            printf("How many servings do you want?:");
            scanf(" %d",&serving_count);
        }

        double temp_price;
        switch (choice){ //each order is saved simultaneously. Total price is also increased when a new order is added
        case CORBA:
            temp_price=serving_count*price_reader(CORBA);
            fprintf(receipt,"%2d*Çorba%30.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case KEBAP:
            temp_price=serving_count*price_reader(KEBAP);
            fprintf(receipt,"%2d*Kebap%30.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case BEYTI:
            temp_price=serving_count*price_reader(BEYTI);
            fprintf(receipt,"%2d*Beyti%30.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case LAHMACUN:
            temp_price=serving_count*price_reader(LAHMACUN);
            fprintf(receipt,"%2d*Lahmacun%27.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case PIDE:
            temp_price=serving_count*price_reader(PIDE);
            fprintf(receipt,"%2d*Pide%31.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case DONER:
            temp_price=serving_count*price_reader(DONER);
            fprintf(receipt,"%2d*Döner%30.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case KCITIR:
            temp_price=serving_count*price_reader(KCITIR);
            fprintf(receipt,"%2d*Kemiksiz Çıtır%21.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case KUNEFE:
            temp_price=serving_count*price_reader(KUNEFE);
            fprintf(receipt,"%2d*Künefe%29.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case SUTLAC:
            temp_price=serving_count*price_reader(SUTLAC);
            fprintf(receipt,"%2d*Sütlaç%29.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case TRILICE:
            temp_price=serving_count*price_reader(TRILICE);
            fprintf(receipt,"%2d*Triliçe%28.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case KOLA:
            temp_price=serving_count*price_reader(KOLA);
            fprintf(receipt,"%2d*Kola%31.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case SU:
            temp_price=serving_count*price_reader(SU);
            fprintf(receipt,"%2d*Su%33.2lf\n\n",serving_count,temp_price);
            total_price= total_price + temp_price;
            break;

        case EXIT:
            printf("Order has been taken...\n");
            break;

        default:
            printf("Invalid input!\n");
            break;
        }

    } while (choice!=EXIT);

    fprintf(receipt," Total:%31.2lf\n\n",total_price); //just the total price line in the receipt

    char is_student;
    if(total_price!=0){ //if total price is 0 then no need to ask
        do{ //asks if the user is student until the user inputs a valid answer

            printf("Are you a student? (Y/N):");
            scanf(" %c",&is_student);
            
        } while (!(is_student=='Y' || is_student=='N'));
    }


    double temp_total;
    if (total_price>=150.00){ //check for possible discount

        temp_total= total_price*0.10;
        fprintf(receipt," >150TL discount:%21.2lf\n\n",-temp_total);
        
        total_price= total_price-temp_total;
    }

    double temp2_total;
    if (is_student=='Y'){ //student discount check

        temp2_total= total_price*0.125;
        fprintf(receipt," Student Discount%21.2lf\n\n",-temp2_total);
        
        total_price= total_price- temp2_total;
    }



    fprintf(receipt,"---------------------------------------\n\n");
    if (total_price!=0){
        fprintf(receipt,"Price:%32.2lf\n\n",total_price);
        fprintf(receipt,"Price + VAT :%25.2lf\n\n",total_price*1.18);
    }

    fclose(receipt);


}

void restaurant_order_function(){ //main restaurant function calls other functions in order of algorithm.

    printf("\n\tWELCOME TO THE BEST RESTAURANT IN THE WORLD\a\n\n");

    menu_printer(); //shows the menu

    order_take_save(); //takes order and saves it in receipt.txt file

    receipt_printer(); //show the finak receipt
}

//part2
char computer_selection(){

    int comp_decision;
    char ch_comp_decision; //to be able to get char inputs from the user. so that invalid inputs can be detected
    srand(time(NULL));

    comp_decision= rand()%3; // decision can be 0,1,2
    comp_decision++; // line line makes decision 1,2 or 3
    
    switch (comp_decision)
    {
    case 1:
        ch_comp_decision= STONE;
        break;
    
    case 2:
        ch_comp_decision= PAPER;
        break;
    
    case 3:
        ch_comp_decision= SCISSORS;
        break;
    }


    return ch_comp_decision;

}

void winner_finder(int comp_dec,int user_dec){ //compares the moves of computer and the user. prints the winner

    if (user_dec==STONE){
        if(comp_dec==PAPER){
            printf("I chose Paper, you chose stone. I WON!\n");
            
            
        }else if (comp_dec==STONE){
            
            printf("I chose stone, you chose stone. TIE!\n");
            
        }else{
            
            printf("I chose scissors, you chose stone. YOU WON!\n");
            
        }
        


    }else if (user_dec==PAPER){
        if(comp_dec==SCISSORS){
            printf("I chose scissors, you chose paper. I WON!\n");
        }else if(comp_dec==STONE){
            printf("I chose stone, you chose paper. YOU WON!\n");
        }else{
            printf("I chose scissors, you chose paper. TIE!\n");
        }
        
    }else{
        if(comp_dec==SCISSORS){
            printf("I chose scissors, you chose scissors. TIE!\n");
        }else if(comp_dec==STONE){
            printf("I chose stone, you chose scissors. I WON!\n");
        }else{
            printf("I chose paper, you chose scissors. YOU WON!\n");
        }
        
    }
    

}

void rock_paper_sci(){ //main function of part2. includes getting input and calling other functions of part2.

    char comp_dec;
    char user_dec;
    char exit_dec='Y';
    int exit_dec_check,user_input_check; //these condition variables have been mentioned by Yakup hoca before


    do{
        comp_dec= computer_selection();

        do{
            printf("Please make a choice!\n1: Stone, 2: Paper, 3: Scissors :");
            scanf(" %c",&user_dec);

            user_input_check= user_dec==STONE || user_dec==PAPER || user_dec==SCISSORS;
            if(!user_input_check){
                printf("Invalid input!\n");
            }

        }while (!user_input_check);
    
        winner_finder(comp_dec,user_dec); //declares the winner

        do{ //makes sure that the answer is Y or N
            printf("Do you want to play again(Y/N)?:"); 
            scanf(" %c",&exit_dec);

            exit_dec_check= exit_dec=='Y' || exit_dec=='N';

            if(!exit_dec_check){
                printf("Invalid input!\n");
            }

        }while (!exit_dec_check);

    } while (exit_dec=='Y');
        
}