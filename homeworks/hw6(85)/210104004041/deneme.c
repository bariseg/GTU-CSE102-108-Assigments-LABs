#include <stdio.h>
#include <stdlib.h>


#define MAX_LINE_LEN 100
#define MAX_PRODUCT 100
#define MAX_FEAT_NAME_LEN 15


int str_comparer(char str1[], char str2[]){
    int i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            return 1;
        }
        i++;
    }
    return 0;
}


void reader(int *feat_count,int *product_cnt,char feat_type_arg[MAX_LINE_LEN],int *stock_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]){

    FILE *fpt= fopen("products.txt","r");
    int index=0;
    int feat_counter=1;
    char line[MAX_LINE_LEN]="";

    fgets(line,MAX_LINE_LEN,fpt);

    while(line[index]!= '\0'){
        
        if(line[index]==','){
            feat_counter++;
        }
        
        index++;
    }
    *feat_count=feat_counter;

    rewind(fpt);
    char read;
    int product_count=0;
    while ((read=fgetc(fpt))!=EOF)
    {
        if (read=='\n')
        {
            product_count++;
        }
        
    }
    
    *product_cnt=product_count;
    fclose(fpt);


    FILE *typesfile=fopen("feat_types.txt","r");

    int i = 0;
    char c;
    while (fscanf(typesfile, "%c", &c) == 1) {
        if (c != ',') {
            feat_type_arg[i] = c;
            i++;
        }
    }
    
    fclose(typesfile);

    FILE* stocksfile=fopen("stocks.txt","r");

    char readchar;
    int stocks_count=0;

    while ((readchar=fgetc(stocksfile))!=EOF)
    {
        if (readchar=='\n')
        {
            stocks_count++;
        }
        
    }

    *stock_count=stocks_count;
    
    
    fclose(stocksfile);

    //reading all values into an array
    fpt=fopen("products.txt","r");

    for (int x = 0; x < feat_counter; x++) //features
    {
        if (x!=feat_counter-1)
        {
            fscanf(fpt,"%[^,]",all_in_one_array[0][x]);
            fgetc(fpt);
        }else{
            fscanf(fpt,"%[^\n]",all_in_one_array[0][x]);
            fgetc(fpt);
        }
    }

    for (int linenumber = 1; linenumber <= product_count; linenumber++)
    {
        for (int featnum = 0; featnum < feat_counter; featnum++)
        {
            if (featnum!=feat_counter-1)
            {
                fscanf(fpt,"%[^,]",all_in_one_array[linenumber][featnum]);
                fgetc(fpt);
            }else{
                fscanf(fpt,"%[^\n]",all_in_one_array[linenumber][featnum]);
                fgetc(fpt);
            }
        }
        
    }
    fclose(fpt);

    //printf("stc c:%d",stocks_count);
    stocksfile=fopen("stocks.txt","r");

    for (int x = 0; x < 4; x++) //features
    {
        if (x!=4-1)
        {
            fscanf(stocksfile,"%[^,]",allstocks[0][x]);
            fgetc(stocksfile);
        }else{
            fscanf(stocksfile,"%[^\n]",allstocks[0][x]);
            fgetc(stocksfile);
        }
    }

    for (int linenumber = 1; linenumber <= stocks_count; linenumber++)
    {
        for (int featnum = 0; featnum < 4; featnum++)
        {
            if (featnum!=4-1)
            {
                fscanf(stocksfile,"%[^,]",allstocks[linenumber][featnum]);
                fgetc(stocksfile);
            }else{
                fscanf(stocksfile,"%[^\n]",allstocks[linenumber][featnum]);
                fgetc(stocksfile);
            }
        }
        
    }
    /*
    for (int i = 0; i <= stocks_count; i++)
    {
        for (int a = 0; a < 4; a++)
        {
            printf("%s,",allstocks[i][a]);
        }
        printf("\n");
    }
    */

    fclose(stocksfile);

}



void brand_stock_control(){
    
    int stocks_count=0,feat_count=0,product_count=0;    
    char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char feat_types[MAX_LINE_LEN];
    reader(&feat_count,&product_count,feat_types,&stocks_count,all_in_one_array,allstocks);

    char brand[MAX_FEAT_NAME_LEN];
    
    double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN];


    printf("Enter the brand:");
    scanf("%s",brand);

    int j;
    int index=0;
    int result_product_count=0;
    int same_pid=0; //those 2 variables above are to check if the product has more than one stock entry
    int temp_same_pid;




    for (int pid = 1; pid <= product_count ; pid++)
    {
        
        if (str_comparer(all_in_one_array[pid][3],brand))
        {

            results[index][0]= pid;
            results[index][1]= atof(all_in_one_array[pid][4]);



            for (int stockid = 1; stockid <= stocks_count; stockid++)
            {
                if (str_comparer(all_in_one_array[pid][0],allstocks[stockid][1]))
                {   
                    
                    if (same_pid!=0)
                    {
                        same_pid=0;
                        index++;

                        results[index][0]= pid;
                        results[index][1]= atof(all_in_one_array[pid][4]);

                    }
                    
                    results[index][2]= atof(allstocks[stockid][3]);
                    
                    same_pid++;

                    
                }

            }
            same_pid=0;
            index++;
            
        }
    }
    

    printf("pIDs,prices and current_stocks by the brand %s\n",brand);

    for (int i = 0; i < index; i++)
    {
        for (int a = 0; a < 3; a++)
        {
            printf("%.2lf,",results[i][a]);
        }
        printf("\n");
    }
    

}



int main(){


    brand_stock_control();


    return 0;
}