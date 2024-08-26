#include <stdio.h>
#include <math.h>
#include "util.h"


void surface_area_volume_func(){

    double pi = 3.14;

    //cube

    int cube_a;
    double cube_area,cube_volume;

    printf("\nEnter the edge length for cube: ");
    scanf("%d",&cube_a);

    cube_area= 6*cube_a*cube_a;
    cube_volume=  cube_a*cube_a*cube_a;

    printf("\nSurface Area = %.2lf ,Volume = %.2lf\n",cube_area,cube_volume);

    ////rectangular prism

    int rec_a,rec_b,rec_c;
    double rec_area,rec_volume;

    printf("\nEnter side length for rectangular prism:");
    scanf("%d",&rec_a);

    printf("\nEnter side width:");
    scanf("%d",&rec_b);

    printf("\nEnter side height:");
    scanf("%d",&rec_c);

    rec_area= 2*((rec_a*rec_b) + (rec_b*rec_c) + (rec_a*rec_c)); //calculates each surface area and multiplies with 2 because there are two the same surfaces for each
    rec_volume= rec_a*rec_b*rec_c;

    printf("\nSurface Area = %.2lf ,Volume = %.2lf\n",rec_area,rec_volume);

    //cone

    int cone_r,cone_h;
    double cone_b,cone_area,cone_v; //cone_b is the slant height of the cone

    printf("\nEnter the radius for cone:");
    scanf("%d",&cone_r);

    printf("\nEnter the height:");
    scanf("%d",&cone_h);

    cone_b = sqrt((cone_r*cone_r) + (cone_h*cone_h)); //there is a right triangle so r**2 + h**2 = b**2

    cone_area = pi*cone_r*(cone_r+cone_b);
    cone_v = (pi*cone_h*cone_r*cone_r)/3;

    printf("\nSurface Area = %.2lf ,Volume = %.2lf\n",cone_area,cone_v);

    //sphere

    int sphere_r;
    double sphere_area,sphere_volume;

    printf("\nEnter the radius for sphere:");
    scanf("%d",&sphere_r);
    
    sphere_area= 4*pi*sphere_r*sphere_r;

    sphere_volume= (4.0*(pi*sphere_r*sphere_r*sphere_r))/3.0;

    printf("\nSurface Area = %.2lf ,Volume = %.2lf\n",sphere_area,sphere_volume);


}



//part2
void BMI_calculator(){
    
    double height,weight,bmi;

    printf("\nEnter height:");
    scanf("%lf",&height);

    printf("\nEnter weight:");
    scanf("%lf",&weight);

    bmi= weight/(height*height);

    if(bmi<18.5){
        
        printf("\nBMI: %.2lf less than 18.5:underweight",bmi);

    }else if(bmi<25){

        printf("\nBMI: %.2lf between 18.5 and 24.9 :average weight",bmi);

    }else if(bmi<30){

        printf("\nBMI: %.2lf between 25 and 30:overweight",bmi);

    }else if (bmi>=30){

        printf("\nBMI: %.2lf is 30 or greater:obese",bmi);

    }

    printf("\n");

}
