#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 =  d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = n2*d1;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    
    int neg_flag_n = 0;  //I need to convert negative number into pozitive for the while loop to work
    int neg_flag_d = 0;  //and those flags are to remember that if the number is negative
    
    
    if(*n<0){
        neg_flag_n=1;
        *n = (*n) * -1;
    }
    if(*d<0){
        neg_flag_d=1;
        *d= (*d) * -1;
    }


    if(*n!=0){ //this line checks if the numerator is 0, if so there is nothing to do about GCD
        
        int divisor=1; //this variable is our divisor which will be modified by temp_divisor
        int temp_divisor=1; // this variable is to try each number until the gcd

        while(temp_divisor<=*n || temp_divisor<=*d){ //if the temp_divisor reaches any of numerator or denominator, the loop stops

            if((*n) % temp_divisor==0 && (*d) % temp_divisor==0){ //this line checks if the temp_divisor is a divisor of both dominator and numerator
                divisor=temp_divisor; //saves the temp_divisor into divisor, if the temp_divisor is a common divisor
            }
            
            temp_divisor++;
            
        }

        *n = *n / divisor;
        *d = *d / divisor;

        if(neg_flag_n==1){
            *n = (*n) * -1;
        }
        if(neg_flag_d==1){
            *d = (*d) * -1;
        }
    }

} /* end fraction_simplify */
