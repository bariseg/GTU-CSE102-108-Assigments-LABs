#include <stdio.h>
#include "util.h"


void euclid_gcd(){    //part1
    
    printf("Part-1 GCD\n");

    int gcd,num1,num2;

    printf("Enter the first number:");
    scanf("%d",&num1);
    
    printf("\nEnter the second number:");
    scanf("%d",&num2);

    int big_num,small_num;
    
    if(num1>num2){    // the big one must be determined because big number is divided by the small ones
        big_num=num1;
        small_num=num2;
    }else{
        big_num=num2;
        small_num=num1;
    }

    int temp_num,temp_divisor,remainder;

    temp_num=big_num;
    temp_divisor=small_num; //the first number and divisor are the numbers came from the user

    while (1){

        remainder=temp_num%temp_divisor;

        if(remainder==0){ //if the remainder is 0 then gcd is the small number given by user if not process goes on
            gcd=temp_divisor;
            break;
        }else{ 

            temp_num=temp_divisor; //divisor becames number and remainder becames divisor
            temp_divisor=remainder;
            
        }//the process continues again again untill the remainder is 0
    }

    printf("\nGDC(%d,%d)=%d\n",num1,num2,gcd);

}

void sum_function(){  //part2

    printf("Part-2 Sum\n");

    int result,num1,num2;

    printf("Enter the first number:");
    scanf("%d",&num1);
    
    printf("\nEnter the second number:");
    scanf("%d",&num2);

    result = num1 + num2;

    printf("\nResult:\n     %5d\n     %5d\n    +\n    ------\n     %5d\n",num1,num2,result);

    //we assumed the numbers have at most 4 digits. so result can have at most 5 digits. therefore, i used %5d


}

void mult_function(){ //part3

    printf("Part-3 Multiplation\n");

    int result,num1,num2;
    int num2_digit_count;

    printf("Enter the first number:");
    scanf("%d",&num1);
    
    printf("\nEnter the second number:");
    scanf("%d",&num2);

    printf("\nResult:\n\n");

    if(num2>99){ //we assumed that the numbers have at most 3 digits. this loop finds the digit count of num2
        num2_digit_count=3;
    }else if(num2>9){
        num2_digit_count=2;
    }else{
        num2_digit_count=1;
    }

    printf("%7d\n%7d\n*\n-------\n",num1,num2); 

    // *
    // ----------


    for(int i =1;i<=num2_digit_count;i++){ //digit count of the num2 is also the number of rows below the multiplation line
        
        int temp_digit,temp_num;
        
        temp_num=num2; //this line and the for loop below is for taking digits of num2

        for(int a=0;a<=(i-1);a++){ //takes the certain digit depending on the row number

            temp_digit= temp_num%10;
            temp_num= temp_num/10;

        }
        int temp_result=temp_digit*num1; //multiplies the digit with num1 in order to be printed 

        int temp_result_digit_count; 

        if(temp_result>999){ //the answer can have at most 4 digits. this loop find the digit count of the result of the each row
            temp_result_digit_count=4;
        }else if(temp_result>99){
            temp_result_digit_count=3;
        }else if(temp_result>9){
            temp_result_digit_count=2;
        }else{
            temp_result_digit_count=1;
        }
        
        printf("%*d\n",7-(i-1),temp_result); //prints the result of row and the alligns to the right depending on row number
        
        
        //printf("%d\n",temp_result);//prints the result for the row

    }//loop continues untill the each row is printed correctly

    printf("+\n-------\n");//sum line
    result= num1*num2;  
    printf("%7d\n",result);//prints the final result


}

void integer_check(){ //part4

    printf("Part-4 Integer interval check\n");

    int num;

    printf("Enter an integer between 1 and 10 (inclusive): ");
    scanf("%d",&num);
    printf("\n");

    if(num>10 || num<1){
        printf("\aInvalid input\n"); //alerts if the input is invalid
    }else if(num>5){
        printf("\"The integer you entered is greater than 5\"\n");
    }else if(num<=5){
        printf("The integer you entered is less than or equal to 5\n");
    }



}