#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number */
    int num1, den1;

    printf("For the First Fractional Number\n");
    printf("Enter Numerator:");
    scanf("%d",&num1);
    printf("\n");
    while(1){
        printf("Enter Denominator:");
        scanf("%d",&den1);
        printf("\n");
        if(den1!=0){
            break;
        }else{
            printf("The Denominator must not equal to 0\nTry Again\n");
        }
    }

    /* A second fractional number */
    int num2, den2;

    printf("For the Second Fractional Number\n");
    printf("Enter Numerator:");
    scanf("%d",&num2);
    printf("\n");

    while(1){
        printf("Enter Denominator:");
        scanf("%d",&den2);
        printf("\n");
        if(den2!=0){
            break;
        }else{
            printf("The Denominator must not equal to 0\nTry Again\n");
        }
    }
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    return(0);
}
