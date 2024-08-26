#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int ID,age;
    float gpa;
}Student;

float part3();


int * part1(int size);

int main(){


    
    int *array;
    int size;
    printf("Enter the size of the array:");
    scanf("%d",&size);

    array=part1(size);

    //WHEN PART2 IS TESTED YOU CAN UNCOMMENT ABOVE PART

    int min=array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i]<min) min=array[i];
    }

    printf("The min value is :%d\n\n",min); 

    //PART2
    printf("\n\n\n\nPART2*****\n\n\n");
    int *sec_array= (int *)calloc(size,sizeof(int));

    int sum=0;
    printf("first array:");
    for (int i = 0; i < size; i++){
        printf("%d ",array[i]);
        sum=sum+array[i];
        sec_array[i]=sum;
    }

    printf("\n\nsecond array:");
    for (int i = 0; i < size; i++) printf("%d ",sec_array[i]);

    free(sec_array);
    free(array);

    //PART3
    printf("\n\n");    
    srand(time(NULL));

    float avg_gpa;

    float all_sums=0;
    for (int i = 0; i < 10000; i++)
    {
        avg_gpa=part3();
        all_sums= all_sums+ avg_gpa;
    }
    
    float final_avg;
    final_avg=all_sums/10000;

    printf("Average GPA of 10.000 x 10.000 students: %.8f\n",final_avg);
    

    return 0;
}

float part3(){

    Student *stu_array= (Student* )malloc(10000* sizeof(Student));
    float avg=0;

    int temp;
    float temp_gpa;
    for (int i = 0; i < 10000; i++)
    {
        temp= rand() % 10000; //random id
        stu_array[i].ID=temp;

        temp= rand() % 50; //18-67
        temp=temp+18;
        stu_array[i].age=temp;

        temp_gpa= rand() % 4;   //before the comma
        temp_gpa= temp_gpa + (rand() % 100)*0.01; //after the comma
        
        stu_array[i].gpa=temp_gpa;

        //printf("id:%d   age:%d  gpa:%.3f  \n",stu_array[i].ID,stu_array[i].age,stu_array[i].gpa);
    }
    
    float sum=0;
    for (int a = 0; a < 10000; a++) sum= sum+ stu_array[a].gpa;
    
    avg= sum/10000;


    free(stu_array);
    return  avg;
}



int * part1(int size){

    int *array= (int * )malloc(size* sizeof(int));


    int temp_value;
    printf("enter %d elements of the array:",size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d",&temp_value);
        array[i]=temp_value;
    }
    return array;

}