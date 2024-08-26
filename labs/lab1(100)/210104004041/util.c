#include <stdio.h>
#include "util.h"



void fizz_buzz_or_both(){

    int num;

    int flag=0; //i need flags to avoid using more if-else conditions
    int flag2=0;

    printf("Enter an integer:");
    scanf("%d",&num);
    printf("\n");

    for(int i=0; i<2; i++){// for loops twice. therefore, i use the if statements twice :)

        if(num%3==0 && flag==0 ){
        
            printf("Fizz");

            flag=1;

        }else{
            if((num<=50 && num>=5) && flag2==0){ //flag2 remembers "Buzz" is already printed
                printf("Buzz\n");
                flag2=1;
            }
        }


    }

}



void finding_z(){

    double x,y,z,divison,max,sum;

    printf("\nEnter x :");
    scanf("%lf",&x);

    while (1){

    printf("\nEnter y :");
    scanf("%lf",&y);

    if(y!=0){
        break;
    }else{
        printf("y cant equal to 0\n");
    }

    }
    


    divison = x/y;
    sum= x+y;

    //finding max
    if (x>=y){
        max=x;
    }else{
        max=y;
    }

    z= max/sum;
    z= z + divison;

    printf("Z= %lf",z);



}



void salary_func(){

    int age,exp;

    int sal1= 10000;
    int sal2= 15000;
    int sal3= 20000;
    int sal4= 25000;


    printf("\nEnter your age:");
    scanf("%d",&age);

    printf("\nEnter your years of experience:");
    scanf("%d",&exp);

    if(age<20){
        if(exp<=10 && exp>=0){
            printf("Your salary is %d\n",sal1);
        }else {
            printf("Error:invalid experience or age\n"); //user couldnt start working younger than 10
        }

    }else if(age>=20 && age<=50){
        if(exp<=10 && exp>=0){
            printf("Your salary is %d\n",sal2);
        }else if(age-exp<10){
            printf("Error:invalid experience or age\n");//user couldnt start working younger than 10
        }else{
            printf("Your salary is %d\n",sal3);
        }

    }else if(age>50){
        if(exp<=10 && exp>=0){
            printf("Your salary is %d\n",sal3);
        }else if(age-exp<10){
            printf("Error:invalid experience or age\n");//user couldnt start working younger than 10
        }else {
            printf("Your salary is %d\n",sal4);
        }      
    }

}