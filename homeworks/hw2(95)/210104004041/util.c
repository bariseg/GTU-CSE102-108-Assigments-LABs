#include <stdio.h>
#include "util.h"

//part1
void leap_year_function(){

    int year;

    printf("Enter a year: ");
    scanf("%d",&year);

    if(year%4==0){ //there are some exceptions i searched from wikipedia.
        
        if(year%100==0 && year%400!=0){
            printf("\n%d is not a leap year.",year);
        }else if(year%4000==0){
            printf("\n%d is not a leap year.",year);
        }else{
            printf("\n%d is a leap year.",year);    
        }
    }else{
        printf("\n%d is not a leap year.",year);
    }

}


//part2
void enhanced_calculator(){

    char format,operation;
    int m,n;
    
    printf("\nEnter the format of output(S or I): ");
    scanf(" %c",&format);

    if(format=='S'){

        while (1){
            printf("\nEnter m and n values: ");
            scanf("%d %d",&m,&n);

            if(n>=m){
                printf("\nInvalid input: m must be greater than n");
            }else{
                break;
            }
        }
    }

    printf("\nEnter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c",&operation);

    switch (operation){
        //each operations calls its own function
    case '+':
        sum(format,m,n);
        break;
    
    case '-':
        minus(format,m,n);
        break;
    
    case '/':
        division(format,m,n);
        break;
    
    case '*':
        multiplier(format,m,n);
        break;
    
    case '%':
        mode(format,m,n);
        break;
    
    case '!':
        factorial(format,m,n);
        break;
    
    case '^':
        power(format,m,n);
        break;
    
    default:
        printf("Invalid operation %c.",operation);
        break;
    }


}


//here are functions for each operation and also a function for scientific result if prefered by user.
void sum(char format,int m,int n){
    //each function has similar structure.
    double op1,op2;

    printf("Enter the first operand: ");
    scanf("%lf",&op1);
    printf("Enter the second operand: ");
    scanf("%lf",&op2);

    if(format=='I'){//integer result
        int result= op1 + op2;
        printf("%.1lf+%.1lf=%d (I)",op1,op2,result);
    }else if(format=='S'){
        double result= op1+op2;
        printf("%lf+%lf=",op1,op2);
        scientific_result_printer(result,m,n); //call for scientific result
    }

}

void minus(char format,int m,int n){
    double op1,op2;

    printf("Enter the first operand: ");
    scanf("%lf",&op1);
    printf("Enter the second operand: ");
    scanf("%lf",&op2);

    if(format=='I'){
        int result= op1 - op2;
        printf("%.1lf-%.1lf=%d (I)",op1,op2,result);
    }else if(format=='S'){
        double result= op1- op2;
        printf("%lf-%lf=",op1,op2);
        scientific_result_printer(result,m,n);
    }
}

void division(char format,int m,int n){
    double op1,op2;

    printf("Enter the first operand: ");
    scanf("%lf",&op1);
    printf("Enter the second operand: ");
    scanf("%lf",&op2);

    if(format=='I'){
        int result= op1/op2;
        printf("%.1lf/%.1lf=%d (I)",op1,op2,result);
    }else if(format=='S'){
        double result= op1/ op2;
        printf("%lf/%lf=",op1,op2);
        scientific_result_printer(result,m,n);
    }

}

void multiplier(char format,int m,int n){
    double op1,op2;

    printf("Enter the first operand: ");
    scanf("%lf",&op1);
    printf("Enter the second operand: ");
    scanf("%lf",&op2);

    if(format=='I'){
        int result= op1*op2;
        printf("%.1lf*%.1lf=%d (I)",op1,op2,result);
    }else if(format=='S'){
        double result= op1*op2;
        printf("%lf*%lf=",op1,op2);
        scientific_result_printer(result,m,n);
    }

}

void mode(char format,int m,int n){

    int op1,op2;

    printf("Enter the first operand: ");
    scanf("%d",&op1);
    printf("Enter the second operand: ");
    scanf("%d",&op2);

    if(format=='I'){
        int result= op1%op2;
        printf("%d %% %d=%d (I)",op1,op2,result);

    }else if(format=='S'){
        double result= op1%op2;
        printf("res%lf",result);
        printf("%d %% %d=",op1,op2);
        scientific_result_printer(result,m,n);
    }


}

void factorial(char format,int m,int n){
    double op1;

    printf("Enter the operand: ");
    scanf("%lf",&op1);

    if(format=='I'){

        int result=1;

        for (int i = op1; i > 1; --i) {//calculates the factorial in int
            result = result * i;
            }

        printf("%.lf!=%d (I)",op1,result);

    }else if(format=='S'){

        double result=1;
        for (int i = op1; i > 1; --i) {
            result = result * i;
            }

        printf("%lf!=",op1);
        scientific_result_printer(result,m,n); //call for scientifi result
    }
}

void power(char format,int m,int n){
    double op1;
    int op2;

    printf("Enter the first operand: ");
    scanf("%lf",&op1);
    printf("Enter the second operand: ");
    scanf("%d",&op2);

    if(format=='I'){

        int result=1;

        for(int i=1; i<=op2;i++){ //calculates power
            result= result*op1;   
        }
        
        printf("%.1lf^%d=%d (I)",op1,op2,result);
    }else if(format=='S'){

        double result=1;
        for(int i=1; i<=op2;i++){
            result= result*op1;   
        }
        printf("%lf^%d=",op1,op2);
        scientific_result_printer(result,m,n);
    }



}
//in order to add zeros from left. I tried hard. just to do what you wanted me to do
void scientific_result_printer(double result,int m,int n){

    double temp_result;
    int m_minus_n= m-n;
    int digits_before_dot=0;
    int power_of_e=0;

    temp_result= result;
    while(!(temp_result<1)){
        digits_before_dot++;
        temp_result= temp_result/10;  
    }
 
    temp_result=result;
    int temp_int=result;
    int digits_after_dot=0;
    while (temp_result!=temp_int){   //noktadan sonraki son anlamlı digite kadar digit sayıyor
        digits_after_dot++;
        temp_result= temp_result*10;
        temp_int= temp_result;
        
    }

    int total_meaningful_digits= digits_after_dot+ digits_before_dot;
    
    if(total_meaningful_digits<m){ //in order to add zeros from left. we need to compare m and total meaningful digit count
        temp_result=result;

        if(n>total_meaningful_digits){
            
            for(int a=0; a< n-digits_after_dot;a++){
                temp_result= temp_result/10;
                power_of_e++;
                digits_before_dot--;
            }
            
            digits_before_dot=1;  //reminders the zero before the dot to the  "printf("%d",0);"
            }else {    
                if(n>digits_after_dot){
                    for(int a=0; a< n-digits_after_dot;a++){
                        temp_result= temp_result/10;
                        power_of_e++;
                        digits_before_dot--;
                        
                    }
                    
                }else if(n<digits_after_dot){
                    for(int i=0;i<(digits_after_dot-n);i++){
                        temp_result= temp_result*10;
                        power_of_e--;
                        digits_before_dot++;;
                        
                    }
                }
            
            }

        for(int i=0;i<(m_minus_n-digits_before_dot);i++){
            printf("%d",0);
        }
    
        

        printf("%.*lfe%d",n,temp_result,power_of_e);

    }else if(total_meaningful_digits==m){ //total meaningful digits greater or equal than m
        temp_result=result;
        if(n>digits_after_dot){
            for(int a=0; a< n-digits_after_dot;a++){
                temp_result= temp_result/10;
                power_of_e++;
            }
        }else if(n<digits_after_dot){
            for(int i=0;i<(digits_after_dot-n);i++){
                temp_result= temp_result*10;
                power_of_e--;
            }
        }

        printf("%.*lfe%d",n,temp_result,power_of_e);
    
    }else{ //when the number total meaningful digits is greater than m. for ex: 12345.67 m:5 n:whatever
        printf("\n**Error**\nResult=%lf\nm:%d\nthe number of total meaningful digits of the result(%d) is greater than m\nthere would be lost digits if the program continued.",result,m,total_meaningful_digits);
    }



}


//part3
void grade_calculator(){

    double ex1,ex2,ex3,assignment1,assigment2;
    double final_grade;

    printf("Enter 3 exam grades of student: ");
    scanf("%lf %lf %lf",&ex1,&ex2,&ex3);

    printf("\nEnter 2 assignment grades of student: ");
    scanf("%lf %lf",&assignment1,&assigment2);

    final_grade= (((ex1+ex2+ex3)/3)*0.6) + (((assignment1+assigment2)/2)*0.4);

    if(final_grade>=60){
        printf("\nFinal grade: %.1lf Passed!",final_grade);
    }else{
        printf("\nFinal grade: %.1lf Failed!",final_grade);
    }

}
