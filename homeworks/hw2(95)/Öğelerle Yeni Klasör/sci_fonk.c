#include <stdio.h>
#include "math.h"


int main(){
    double result= 3.0;
    double temp_result;
    int m=9,n=5;
    int m_minus_n= m-n;
    int digits_before_dot=0;
    int power_of_e=0;

    printf("result:%lf\nm:%d\nn:%d\n",result,m,n);

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
            for(int a=0; a< n-total_meaningful_digits;a++){
                temp_result= temp_result/10;
                power_of_e++;
                digits_before_dot--;
                digits_after_dot++;
            }
            }else {    
                if(n>digits_after_dot){
                    for(int a=0; a< n-digits_after_dot;a++){
                        temp_result= temp_result/10;
                        power_of_e++;
                        digits_before_dot--;
                        digits_after_dot++;
                    }
                    
                }else if(n<digits_after_dot){
                    for(int i=0;i<(digits_after_dot-n);i++){
                        temp_result= temp_result*10;
                        power_of_e--;
                        digits_after_dot--;
                        digits_before_dot++;
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
                digits_before_dot--;
                digits_after_dot++;
            }
        }else if(n<digits_after_dot){
            for(int i=0;i<(digits_after_dot-n);i++){
                temp_result= temp_result*10;
                power_of_e--;
                digits_after_dot--;
                digits_before_dot++;
            }
        }

        printf("%.*lfe%d",n,temp_result,power_of_e);
    }else{ //when the number total meaningful digits is greater than m. for ex: 12345.67 m:5 n:whatever
        printf("\n**Error**\nResult=%lf\nm:%d\nthe number of total meaningful digits of the result(%d) is greater than m\nthere would be lost digits if the program continued.",result,m,total_meaningful_digits);
    }


}
