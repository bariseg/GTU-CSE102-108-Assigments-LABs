#include <stdio.h>
#include "util.h"



void median_finder(){

    int num1,num2,num3;
    int median;

    printf("Enter 3 integers: ");
    scanf("%d %d %d",&num1,&num2,&num3);

    if(num1>=num2){
        if (num1<=num3){
            median=num1;
        }
    }else if(num1>=num3){
        if(num1<=num2){
            median=num1;
        }
    
    }
    if(num2>=num3){
        if(num2<=num1){
            median=num2;
        }
    }else if(num2>=num1){
        if(num2<=num3){
            median=num2;
        }

    }
    if(num3>=num1){
        if(num3<=num2){
            median=num3;
        }
    }else if(num3>=num2){
        if(num3<=num1){
            median=num3;
        }
    }
    printf("Median number is %d\n",median);


}


void grade_func(){

    double ex1,ex2,ex3,average;
    char ex1_grade,ex2_grade,ex3_grade;

    printf("Enter your scores:");
    scanf("%lf %lf %lf",&ex1,&ex2,&ex3);

    average = (ex1+ex2+ex3)/3;

    int ex1_digit= ex1/10;
    int ex2_digit= ex2/10;
    int ex3_digit= ex3/10;
    

    switch (ex1_digit)
    {
    case 10:
    case 9:
        printf("Your letter grades are A+,");

        break;
    case 8:
        printf("Your letter grades are A,");

        break;
    case 7:
        printf("Your letter grades are B+,");
        break;
    case 6:
        printf("Your letter grades are B,");

        break;
    case 5:
        printf("Your letter grades are C,");
        break;
    case 4:
        printf("Your letter grades are D,");
        break;
    case 3:
    case 2:
    case 1:
    case 0:
        printf("Your letter grades are F,");
        break;
    default:
        printf("Invalid input");
        break;
    }

    switch (ex2_digit)
    {
    case 10:
    case 9:
        printf(" A+");

        break;
    case 8:
        printf(" A");

        break;
    case 7:
        printf(" B+");
        break;
    case 6:
        printf(" B");

        break;
    case 5:
        printf(" C");
        break;
    case 4:
        printf(" D");
        break;
    case 3:
    case 2:
    case 1:
    case 0:
        printf(" F");
        break;
    default:
        printf("Invalid input");
        break;
    }

    switch (ex3_digit)
    {
    case 10:
    case 9:
        printf(" and A+ with an %.2lf average.\n",average);

        break;
    case 8:
        printf(" and A with an %.2lf average.\n",average);

        break;
    case 7:
        printf(" and B+ with an %.2lf average.\n",average);

        break;
    case 6:
        printf(" and B with an %.2lf average.\n",average);

        break;
    case 5:
        printf(" and C with an %.2lf average.\n",average);

        break;
    case 4:
        printf(" and D with an %.2lf average.\n",average);

        break;
    case 3:
    case 2:
    case 1:
    case 0:
        printf(" and F with an %.2lf average.\n",average);
        break;
    default:
        printf("Invalid input");
        break;
    }


}



void calculate(){

    char operator;
    int num1,num2;
    double result_guess;
    double result;
    double num1_lf,num2_lf;

    printf("\nEnter an arithmetic operation(+,-,*,/):");
    scanf(" %c",&operator);

    printf("Enter two integers:");
    scanf("%d %d",&num1,&num2);

    printf("Result:");
    scanf("%lf",&result_guess);

    switch (operator)
    {
    case '+':
        result= num1 + num2;
        break;
    case '-':
        result= num1 - num2;
        break;
    case '*':
        result= num1 * num2;
        break;
    case '/':
        num1_lf=num1;
        num2_lf=num2;
        result= num1_lf / num2_lf;
        break;
    
    default:
        printf("Invalid operation\n");
        break;
    }

    printf("%lf is the result\n",result);

    if(result==result_guess){
        printf("Bravo,correct answer!\n");
    }else{
        printf("Wrong answer,try again\n.");
    }

}

