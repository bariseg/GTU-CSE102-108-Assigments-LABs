#include <stdio.h>

void scientific_result_printer(double result,int m,int n){
    double temp_result= result;
    int digits_before_dot=0,digits_after_dot=0;
    int pow_of_ten=0;
    int before_dot= result;
    double after_dot= result-before_dot;
    int after_dot_int;
    double final_result;

    if(temp_result<0){
        temp_result= temp_result*-1;
    }
    //digit counter
    while(!(temp_result<1)){
        digits_before_dot++;
        temp_result= temp_result/10;
    }

    //sağdakileri sola çekiyor
    for (int a=0;a<6;a++){
        after_dot= after_dot*10;
    }
    printf("%lf\n",after_dot);
    after_dot_int= after_dot;
    printf("a%d\n",after_dot_int);

    double temp2= result;
    while(temp2!=before_dot){
        digits_after_dot++;
        temp2=temp2*10;
        printf("%d",digits_after_dot);
    }




    for(int i=1; i<=(6-n);i++){ // 6-n kadar kaydırıldı - olack
        temp_result= temp_result*10;
    }

    printf("%d\n%lf\n",digits_before_dot,temp_result);

    


}
int main(){

    scientific_result_printer(123.456789,2,2);

}


/*
noktadan önce ve sonrasını int e çevir
sonra birleştir 
sonra noktayı kaydırarak e nin üssünü bul
sonra yapıştır gitsin

*/