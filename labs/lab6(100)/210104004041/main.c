#include <stdio.h>


//part1
void part1(); //main func of part1
int *reader_function(int *nums,int *lenght); //returns the array of inputs
int *label_func(int *nums,int *odd_even ,int lenght); //labels numbers 0 for odd 1 for even returns the array of result
void result_printer(int numbers[],int labels[],int lenght); //prints the result arrays

//part2
void part2();



int main(){

    //part1
    //part1();

    //part2
    part2();
    
    return(0);
}


//part1

void part1(){

    int num_array[30];
    int *numbers;
    int o_e_array[30];
    int *labels;
    
    int lenght;
    
    

    numbers=reader_function(num_array, &lenght);

    labels= label_func(numbers,o_e_array,lenght);
    
    result_printer(numbers,labels,lenght);
    


}
//part1
int *reader_function(int *nums,int *lenght){

    int num;
    int index_num=0;

    do
    {
        
        printf("Input integer (-100 for exit):");
        scanf("%d", &num);

        if (num!=-100)
        {
            nums[index_num]=num;
            index_num++;
        }
        
    } while (num!=-100);

    *lenght=index_num;
    return nums;
    

}

int *label_func(int *nums,int *odd_even ,int lenght){
    
    int num;

    for (int i = 0; i < lenght; i++)
    {
        if (nums[i]%2==0)
        {
            num=1;

        }else{
            num=0;

        }
        odd_even[i]= num;
        //printf("%d",odd_even[i]);
    }
    
    return odd_even;

}

void result_printer(int numbers[],int labels[], int lenght){

    char label;

    for (int i = 0; i < lenght; i++)
    {
        if (labels[i]==1)
        {
            label= 'e';
        }else{
            label= 'o';
        }
        
        
        printf("%d %c\n",numbers[i],label);


    }
    

}

//part2
void part2(){

    FILE *fpt= fopen("table.txt","r");

    int raw_count;
    int ages[10];
    double salaries[10];
    char teams[10],occupations[10];
    
    char linebuffer; //to read \n 

    fscanf(fpt,"%d\n",&raw_count); //reads raw counts

    for (int i = 0; i < raw_count; i++)
    {
        fscanf(fpt,"%d ",&ages[i]);
        fscanf(fpt,"%c ",&occupations[i]);
        fscanf(fpt,"%lf ",&salaries[i]);
        fscanf(fpt,"%c ",&teams[i]);
        fscanf(fpt,"\n",&linebuffer);
        //printf("%d %c %d %c \n",ages[i],occupations[i],salaries[i],teams[i]);
    }



    fclose(fpt);

    char selection;
    int team_exist=0;

    printf("Please select a team:");
    scanf("%c",&selection);

    for (int i = 0; i < raw_count; i++)
    {
        if (teams[i]==selection)
        {
            team_exist=1;
            printf("average salaries of fans(age:%d occ:%c) of %c: %lf\n",ages[i],occupations[i],selection,salaries[i]);
        }
        
    }
    
    if (!team_exist)
    {
        printf("there no fabs of %c in the databe!!\n",selection);
    }
    



}

