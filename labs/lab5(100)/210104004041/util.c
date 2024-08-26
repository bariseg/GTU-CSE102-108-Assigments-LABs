#include <stdio.h>
#include "util.h"





//part1
void FahtoCelc(){

    double tempF,resultC;

    printf("Enter the temperature value in F to convert: ");
    scanf("%lf",&tempF);

    resultC= ((tempF-32)*5)/9;

    printf("%.2lf Fahrenheit = %.2lf Celcius\n\n",tempF,resultC);
    
}

void CelctoFah(){

    double tempC,resultF;

    printf("Enter the temperature value in C to convert: ");
    scanf("%lf",&tempC);

    resultF= ((tempC*9)/5) + 32;

    printf("%.2lf Celcius = %.2lf Fahrenheit\n\n",tempC,resultF);

}

#define CtoF 'a'
#define FtoC 'b'
#define QUIT 'c'

void temperature_converter(){

    char user_selection;
    int quit_flag=1;

    printf("**TEMPERATURE CONVERTER**\n\n");

    do
    {
        
        printf("a)Convert Celcius to Fahrenheit\nb)Conver Fahrenheit to Celcius\nc)Quit\nSelect:");

        scanf(" %c", &user_selection);


        switch (user_selection)
        {
        case CtoF:
            CelctoFah();
            break;
        case FtoC:
            FahtoCelc();
            break;
        case QUIT:
            printf("Quiting...\n\n");
            quit_flag=0;
            break;
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }


    } while (quit_flag);


}


//part2
void number_reverser(){

    int num;
    int digit_count=0;
    int last_digit_zero=0;
    int result=0;

    printf("Enter a number (3,4 or 5 digits):");
    scanf("%d",&num);
    int zero_flag=0;
    if (num%10==0)
    {
        zero_flag=1;
    }
    


    int temp_num= num;
    while (temp_num!=0) //digit counter
    {
        digit_count++;
        temp_num=temp_num/10;
    }

    printf("%d\n",digit_count);

    //main part of reversing
    if (digit_count<=5 && digit_count>=3)
    {
        int result=0;
        while (num != 0) { //stop when there is no digits
            result = result *10; //last digit is for the next digit coming
            result= result + num%10; //adds the new digit
            num /= 10;
        }
        printf("Reversed number : ");
        if (zero_flag)
        {   
            printf("%d",0);
        }
        
        printf("%d\n",result);


    }else{
        printf("Invalid input!!!\n\n");
    }
    






}


//part3

void number_converter(){

    char selection;

    printf("a)Convert a number to decimal, binary, octal, and hexadecimal\nb) Quit\nselect:");
    scanf(" %c",&selection);
    if(selection=='a'){
        int num,remainder;

        printf("enter a number:");
        scanf("%d",&num);
        int binary_num=0;
        int temp_num=num;
        int multiplier=1;
        while (temp_num!=0) //binary converter
        {
            remainder = temp_num % 2;
            binary_num = binary_num + (remainder *multiplier);
            
            temp_num = temp_num/ 2;
            multiplier = multiplier*10;
        }
        int octal_num=0;
        int temp_num1=num;
        int multiplier1=1;
        while (temp_num1!=0) //octal converter
        {
            remainder = temp_num1 % 8;
            octal_num = octal_num + (remainder *multiplier1);
            
            temp_num1 = temp_num1/ 8;
            multiplier1 = multiplier1* 10;
        }
        
        
        printf("%d decimal to binary:%d, octal:%d, hex: %x\n",num,binary_num,octal_num,num);

    }else if(selection=='b'){
        printf("quiting..");
    }else{
        printf("invalid input\n");
    }


}

