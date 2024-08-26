#include <stdio.h>
#include <stdlib.h>
#include "util.h"



#define MAX_LINE_LEN 100
#define MAX_PRODUCT 100
#define MAX_FEAT_NAME_LEN 15

//this is the helper function that counts some numbers
void reader(int *feat_count,int *product_cnt,int *stock_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]){

    FILE *fpt= fopen("products.txt","r");
    int index=0;
    int feat_counter=1;
    char line[MAX_LINE_LEN]="";

    fgets(line,MAX_LINE_LEN,fpt);

    while(line[index]!= '\0'){ //counts the feat count from file
        
        if(line[index]==','){
            feat_counter++;
        }
        
        index++;
    }
    *feat_count=feat_counter;

    rewind(fpt);
    char read;
    int product_count=0;
    while ((read=fgetc(fpt))!=EOF) //counts the products count from file
    {
        if (read=='\n')
        {
            product_count++;
        }
        
    }
    
    *product_cnt=product_count;
    fclose(fpt);




    FILE* stocksfile=fopen("stocks.txt","r");

    char readchar;
    int stocks_count=0;

    while ((readchar=fgetc(stocksfile))!=EOF) //counts the stock count from stocks.txt file
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


    //reads stock to an array

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


void file_operations(){

    char option;
    int feat_count=0;
    int product_count=0;
    int menu_flag=1;
    
    int stocks_count=0;

    char file_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char stocks_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    do
    {

        reader(&feat_count,&product_count,&stocks_count,file_array,stocks_array);
        //printf("produc count:%s\n",file_array[4][2]);
        printf("\n1.Add a new product\n2.Delete a product\n3.Update a product\n4.Add a feature to products\n");
        printf("5.Add a new stock entry\n6.Delete a stock entry\n7.Update a stock entry\n8.Back to main menu\n");
        printf("Option:");
        scanf(" %c",&option);


        switch (option)
        {
        case '1': //compleated
            add_new_product(&feat_count,&product_count);
            
            break;
        
        case '2': //compleated
            delete_product(&product_count);
            
            break;
        
        case '3':
            update_product(&feat_count,&product_count,file_array); //compleated
            break;
        
        case '4':
            add_feature(); //compleated
            
            break;
        
        case '5':
            add_stock(&stocks_count); //compleated
            
            break;
        
        case '6':
            delete_stock(&stocks_count); //compleated
            
            break;
        
        case '7':
            update_stock(&stocks_count,stocks_array);//compleated
            break;
        
        case '8':
            printf("Returning to main menu!\n\n");
            menu_flag=0;
            break;
        default:
            printf("Invalid input!\n\n");
            break;
        }


    } while (menu_flag);
    

}

void add_new_product(int *feat_count,int *product_count){

    FILE *fpt= fopen("products.txt","a");

    char inputs[MAX_LINE_LEN]=""; 

    printf("Give inputs for %d features:",*feat_count-1);

    scanf("%s",inputs);
    
    //printf("deneme:%s\n",inputs);

    fprintf(fpt, "\n%d,%s",*product_count+1,inputs);
    

    fclose(fpt);


}

void delete_product(int *product_count){

    FILE* fpt=fopen("products.txt","r");
    FILE* tempfile= fopen("temp.txt","w");
    int pid;
    int line_num=0;
    char line[MAX_LINE_LEN];
    char modified_pid[3];

    printf("Enter the pID of the product to be deleted:");
    scanf("%d",&pid);

    int temp_line_num=0;
    while (fgets(line, MAX_LINE_LEN, fpt) != NULL) {

        if (temp_line_num<pid)
        {   
            if (pid==*product_count && temp_line_num==pid-1)
            {
                char c;
                int n=0;
                do
                {
                    c=line[n];
                    printf("%c",c);
                    n++;
                } while (c!='\n');
                line[n-1]='\0';
                
            }
            fputs(line, tempfile);
            //printf("%s",modified_pid);
        }else if(temp_line_num>pid){
            
            if (temp_line_num==10)
            {
                line[0]='9';
                char c;
                int n1=2;
                do
                {
                    line[n1-1]=line[n1];
                    c=line[n1];
                    printf("%c",c);
                    n1++;
                } while (c!='\0');
                
            }else if(temp_line_num>10){
                sprintf(modified_pid,"%d",temp_line_num-1);
                line[0]=modified_pid[0];
                line[1]=modified_pid[1];
            }else{
                sprintf(modified_pid,"%d",temp_line_num-1);
                line[0]=modified_pid[0];
                
            }
            fputs(line,tempfile);

        }
  
        temp_line_num++;
    }

    fclose(tempfile);
    fclose(fpt);
    remove("products.txt");
    rename("temp.txt","products.txt");

}

void add_feature(){

    FILE* fpt= fopen("products.txt","r");
    FILE* tempfile= fopen("temp.txt","w");
    int line_counter=0;
    char read;
    //char line[MAX_LINE_LEN]="";
    char added_feat[MAX_FEAT_NAME_LEN]="";
    //char comma[MAX_FEAT_NAME_LEN]=",";
    //char newline[]="\n";


    printf("Enter a feature to be added:");
    scanf("%s",added_feat);

    while ((read=fgetc(fpt))!=EOF)
    {
        if (line_counter==0 && read=='\n')
        {
            ungetc(read,fpt);
            fprintf(tempfile,",%s",added_feat);
            fgetc(fpt);
            fputc(read,tempfile);
            line_counter++;

        }else if(read=='\n'){

            ungetc(read,fpt);
            fprintf(tempfile,",None");
            read=fgetc(fpt);
            fputc(read,tempfile);
        }else{

            fputc(read,tempfile);

        }
        
    }
    
    fprintf(tempfile,",None");

    fclose(fpt);
    fclose(tempfile);

    remove("products.txt");
    rename("temp.txt","products.txt");


}

void update_product(int *feat_count,int *product_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]){

    char pid[2];
    char feat_name[MAX_FEAT_NAME_LEN];
    char new_val[MAX_FEAT_NAME_LEN];
    int prdctid=-1;
    int featindx=-1;
    
    do{
        printf("Enter the pID of the product to be updated:");
        scanf("%s",pid);
        printf("Enter the name of the feature\n");

        for (int i = 1; i < *feat_count; i++)
        {
            printf("%s,",all_in_one_array[0][i]);
        }
        printf(":");
        scanf("%s",feat_name);

        printf("Enter the new value for %s:",feat_name);
        scanf("%s",new_val);

        
        for (int productid = 1; productid <= *product_count; productid++)//converts str pid into int pid
        {
            if (str_comparer(all_in_one_array[productid][0],pid))
            {
                prdctid=productid;
                break;
            }   
        }
        
        
        for (int featindex = 0; featindex < *feat_count; featindex++)//finds the index of the feature to be updated
        {
            if (str_comparer(all_in_one_array[0][featindex],feat_name))
            {
                featindx=featindex;
                break;
            }
        }
        if (prdctid==-1 || featindx==-1) //if this is not checked the file is written forever
        {
            printf("Invalid input!(Dangerous!!)\n");
        }
        

    }while (prdctid==-1 || featindx==-1);
    
    //printf("%d,%d",prdctid,featindx);

    //updating process

    FILE*fpt=fopen("products.txt","r");
    FILE*tempfile=fopen("temp.txt","w");
    
    char templine[MAX_LINE_LEN];
    char chr;
    int commacount=0;
    for (int line = 0; line < *product_count+1; line++)
    {
        if (line==prdctid)
        {
            
            do
            {
                chr=fgetc(fpt);
                fputc(chr,tempfile);

                if (chr==','){
                    commacount++;
                }
                
            } while (commacount!=featindx);
            
            fprintf(tempfile,"%s",new_val);

            do
            { //ignores the previous value from source file
                chr=fgetc(fpt);
            } while ((chr!=',' && chr!='\n')&& chr!=EOF);
            
            if (chr!=EOF)
            {   
                fputc(chr,tempfile);
                fgets(templine,MAX_LINE_LEN,fpt);
                fputs(templine,tempfile);
            }
            
        }else{

            if(fgets(templine,MAX_LINE_LEN,fpt))fprintf(tempfile,templine);
            //if there are not 'if' statement, the last product is printed twice.
        }
        
    }
    

    fclose(fpt);
    fclose(tempfile);

    remove("products.txt");
    rename("temp.txt","products.txt");

}

void add_stock(int *stock_count){

    FILE* stockfile= fopen("stocks.txt","a");

    char values[MAX_LINE_LEN]="";

    printf("Enter pID,Branch,Current Stock:");
    scanf("%s",values);
    
    fprintf(stockfile,"\n%d,%s",*stock_count+1,values);



    fclose(stockfile);

}

void delete_stock(int *stock_count){

    FILE* fpt=fopen("stocks.txt","r");
    FILE* tempfile= fopen("temp.txt","w");
    int sid;
    int line_num=0;
    char line[MAX_LINE_LEN];
    char modified_sid[3];

    printf("Enter the sID of the stock to be deleted:");
    scanf("%d",&sid);

    int temp_line_num=0;
    while (fgets(line, MAX_LINE_LEN, fpt) != NULL) {

        if (temp_line_num<sid)
        {   
            if (sid==*stock_count && temp_line_num==sid-1)
            {
                char c;
                int n=0;
                do
                {
                    c=line[n];
                    printf("%c",c);
                    n++;
                } while (c!='\n');
                line[n-1]='\0';
                
            }
            fputs(line, tempfile);
            //printf("%s",modified_pid);
        }else if(temp_line_num>sid){
            
            if (temp_line_num==10)
            {
                line[0]='9';
                char c;
                int n1=2;
                do
                {
                    line[n1-1]=line[n1];
                    c=line[n1];
                    printf("%c",c);
                    n1++;
                } while (c!='\0');
                
            }else if(temp_line_num>10){
                sprintf(modified_sid,"%d",temp_line_num-1);
                line[0]=modified_sid[0];
                line[1]=modified_sid[1];
            }else{
                sprintf(modified_sid,"%d",temp_line_num-1);
                line[0]=modified_sid[0];
                
            }
            fputs(line,tempfile);

        }
  
        temp_line_num++;
    }

    fclose(tempfile);
    fclose(fpt);
    remove("stocks.txt");
    rename("temp.txt","stocks.txt");


}

void update_stock(int *stock_count,char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]){

    char sid[2];
    char feat_name[MAX_FEAT_NAME_LEN];
    char new_val[MAX_FEAT_NAME_LEN];
    int stcid=-1;
    int featindx=-1;
    
    do{
        printf("Enter the sID of the product to be updated:");
        scanf("%s",sid);
        printf("Enter the name of the feature\n");

        for (int i = 1; i < 4; i++)
        {
            printf("%s,",allstocks[0][i]);
        }
        
            
        
        printf(":");
        scanf("%s",feat_name);

        printf("Enter the new value for %s:",feat_name);
        scanf("%s",new_val);

        
        for (int stockid = 1; stockid <= *stock_count; stockid++)//converts str pid into int pid
        {
            if (str_comparer(allstocks[stockid][0],sid))
            {
                stcid=stockid;
                break;
            }   
        }
        
        
        for (int featindex = 0; featindex < 4; featindex++)//finds the index of the feature to be updated
        {
            if (str_comparer(allstocks[0][featindex],feat_name))
            {
                featindx=featindex;
                break;
            }
        }
        if (stcid==-1 || featindx==-1)
        {
            printf("Invalid input!(Dangerous!!)\n");
        }
        

    }while (stcid==-1 || featindx==-1);
    
    //printf("%d,%d",prdctid,featindx);

    //updating process

    FILE*fpt=fopen("stocks.txt","r");
    FILE*tempfile=fopen("temp.txt","w");
    
    char templine[MAX_LINE_LEN];
    char chr;
    int commacount=0;
    for (int line = 0; line < *stock_count+1; line++)
    {
        if (line==stcid)
        {
            
            do
            {
                chr=fgetc(fpt);
                fputc(chr,tempfile);

                if (chr==','){
                    commacount++;
                }
                
            } while (commacount!=featindx);
            
            fprintf(tempfile,"%s",new_val);

            do
            { //ignores the previous value from source file
                chr=fgetc(fpt);
            } while ((chr!=',' && chr!='\n')&& chr!=EOF);
            
            if (chr!=EOF)
            {   
                fputc(chr,tempfile);
                fgets(templine,MAX_LINE_LEN,fpt);
                fputs(templine,tempfile);
            }
            
        }else{

            if(fgets(templine,MAX_LINE_LEN,fpt))fprintf(tempfile,templine);
            //if there are not 'if' statement, the last product is printed twice.
        }
        
    }
    

    fclose(fpt);
    fclose(tempfile);

    remove("stocks.txt");
    rename("temp.txt","stocks.txt");
    

}


void query_products(){

    char option;
    int feat_count=0;
    int product_count=0;
    int menu_flag=1;
    int stocks_count=0;

    char file_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char stocks_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];


    do
    {
        reader(&feat_count,&product_count,&stocks_count,file_array,stocks_array);
        printf("\n1.List all products\n2.Filter products\n3.Back to main menu\n");
        printf("Option:");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            list_all_products();//compleated
            break;
        
        case '2':
            filter_products(file_array,feat_count,product_count); //compleated
            break;
        
        case '3':
            printf("Returning to main menu!\n\n");
            menu_flag=0;
            break;
        
        default:
            printf("Invalid input!\n\n");
            break;
        }



    } while (menu_flag);

}

void list_all_products(){

    char line[MAX_LINE_LEN];

    FILE* fpt=fopen("products.txt","r");

    printf("\n");
    while (fgets(line,MAX_LINE_LEN,fpt)!=NULL)
    {
        printf("%s",line);
    }
    
    printf("\n\n");

    fclose(fpt);
}

//user can search by everyting he wants. all search criters are stored and compeared
void filter_products(char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int feat_num,int product_num){

    //char filtered_products[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char input[MAX_LINE_LEN];
    char filter_criters[MAX_PRODUCT][MAX_FEAT_NAME_LEN];
    char matched_products[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    printf("Filter Products by ");

    for (int i = 1; i < feat_num; i++)
    {
        printf("%s,", all_in_one_array[0][i]);
    }
    printf("\nJust enter the value(s) of the feature(s) for ex:(Samsung,F):");
    scanf("%s", input);

    int cric_count=0;
    char chr;
    int cricindex=0;
    
    do
    {
        chr=input[cricindex];

        if (chr==',')
        {
            cric_count++;
        }
        cricindex++;

    } while (chr!='\0');
    
    cric_count++;
    //printf("%d",cric_count);

    
    char c;
    int index=0;
    int index2=0;
    int index3=0;
    do
    {
        c=input[index];

        if (c!=',')
        {
            filter_criters[index2][index3]=c;
            index3++;
        }else{
            filter_criters[index2][index3]='\0';
            index2++;
            index3=0;
        }
        index++;
        
    } while (input[index]!='\0');

    filter_criters[index2][index3]='\0';

    /*
    for (int i = 0; i <= index2; i++)
    {
        printf("%s\n",filter_criters[i]);
    }
    */
   
    
    char word[MAX_FEAT_NAME_LEN]="";
    
    int match_count=0;
    int total_matched_products=0;
    int charindex;

    for (int product = 1; product <= product_num; product++)
    {
        for (int wordindex = 0; wordindex < feat_num; wordindex++)
        {
            for (int x = 0; x <= index2; x++)
            {   //printf("%s**%s\n",all_in_one_array[product][wordindex],filter_criters[x]);
                if (str_comparer(all_in_one_array[product][wordindex],filter_criters[x]))
                {

                    match_count++;
                }
            }
        }
        //printf("%d",match_count);
        if (match_count==cric_count)
        {   
            for (int i = 0; i < feat_num; i++)
            {
                int j=0;
                while (all_in_one_array[product][i][j]!='\0')
                {
                    matched_products[total_matched_products][i][j]=all_in_one_array[product][i][j];
                    j++;
                }
                matched_products[total_matched_products][i][j]='\0';


                
                
            }
            total_matched_products++;
        }
        match_count=0;
    }
    
    printf("Matched %d\n",total_matched_products);

    for (int i = 0; i < feat_num; i++)
    {
        printf("%s\t",all_in_one_array[0][i]);
    }
    printf("\n");

    for (int num = 0; num < total_matched_products; num++)
    {
        for (int h = 0; h < feat_num; h++)
        {   
            printf("%s\t",matched_products[num][h]);
        }
        printf("\n");
    }
    printf("\n");
}


void check_stock_status(){

    char option;
    int feat_count=0;
    int product_count=0;
    int menu_flag=1;

    int stocks_count=0;

    char file_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char stocks_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    do
    {
        reader(&feat_count,&product_count,&stocks_count,file_array,stocks_array);
        printf( "\n1.Check Stock by pID and Branch"
                "\n2.Check Stocks by Branch"
                "\n3.Check out-of-stock by Branch"
                "\n4.Back to main menu\n");
        printf("Option:");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            by_pid_branch(stocks_array,stocks_count);
            break;
        case '2':
            by_branch(stocks_array,stocks_count);
            break;
        case '3':
            outofstock(stocks_array,stocks_count,file_array,product_count,feat_count);
            break;
        case '4':
            printf("Returning to main menu!\n");
            menu_flag=0;
            break;
        
        default:
            printf("Invalid input!!\n");
            break;
        }

    } while (menu_flag);
}

void by_pid_branch(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count){

    int featcount=4;
    char pid[3];
    char branch[MAX_FEAT_NAME_LEN];
    char matched_stocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    printf("Enter pID:");
    scanf("%s",pid);

    printf("Enter branch name:");
    scanf("%s",branch);

    int matched_indexes=0;
    int j;
    for (int stocknum = 1; stocknum <= stock_count; stocknum++)
    {   
        //printf("%s**%s,%s**%s\n",pid,allstocks[stocknum][1],branch,allstocks[stocknum][2]);
        if(str_comparer(allstocks[stocknum][1],pid) && str_comparer(allstocks[stocknum][2],branch))
        {   //printf("match");
            for (int featindex = 0; featindex < 4; featindex++)
            {   
                j=0;
                while (allstocks[stocknum][featindex][j]!='\0')
                    {
                        matched_stocks[matched_indexes][featindex][j]=allstocks[stocknum][featindex][j];
                        j++;
                    }
                    matched_stocks[matched_indexes][featindex][j]='\0';
            }
            matched_indexes++;
        }

    }
    printf("Matched %d\n",matched_indexes);

    for (int i = 0; i < 4; i++)
    {
        printf("%s\t",allstocks[0][i]);
    }
    printf("\n");
    

    for (int i = 0; i < matched_indexes; i++)
    {
        for (int a = 0; a < 4; a++)
        {
            printf("%s\t",matched_stocks[i][a]);
        }
        printf("\n");
    }


}

void by_branch(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count){

    int featcount=4;
    char branch[MAX_FEAT_NAME_LEN];
    char matched_stocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    printf("Enter branch name:");
    scanf("%s",branch);

    int matched_indexes=0;
    int j;
    for (int stocknum = 1; stocknum <= stock_count; stocknum++)
    {   
        //printf("%s**%s,%s**%s\n",pid,allstocks[stocknum][1],branch,allstocks[stocknum][2]);
        if(str_comparer(allstocks[stocknum][2],branch))
        {   //printf("match");
            for (int featindex = 0; featindex < 4; featindex++)
            {   
                j=0;
                while (allstocks[stocknum][featindex][j]!='\0')
                    {
                        matched_stocks[matched_indexes][featindex][j]=allstocks[stocknum][featindex][j];
                        j++;
                    }
                    matched_stocks[matched_indexes][featindex][j]='\0';
            }
            matched_indexes++;
        }

    }
    printf("Matched %d\n",matched_indexes);

    for (int i = 0; i < 4; i++)
    {
        printf("%s\t",allstocks[0][i]);
    }
    printf("\n");

    for (int i = 0; i < matched_indexes; i++)
    {
        for (int a = 0; a < 4; a++)
        {
            printf("%s\t",matched_stocks[i][a]);
        }
        printf("\n");
    }


}

void outofstock(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int product_count,int feat_count){

    char branch[MAX_FEAT_NAME_LEN];
    char pIDs_of_specied_branch[MAX_PRODUCT][MAX_FEAT_NAME_LEN];
    
    char out_of_stock_products[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    int j;
    int index=0;

    printf("Enter a branch to see out-of-stock products:");
    scanf("%s",branch);

    //we need to store the pids of the all stocks (depending on the branch) to make comparisons

    for (int stockid = 1; stockid <= stock_count; stockid++)
    {
        if (str_comparer(allstocks[stockid][2],branch))
        {
            j=0;
            while (allstocks[stockid][1][j]!='\0')
            {
                pIDs_of_specied_branch[index][j]=allstocks[stockid][1][j];
                j++;
            }
            pIDs_of_specied_branch[index][j]='\0';
            index++;//this also counts the number of pids of specied branch
        }
        
        
    }

    int outofproudtccount=0;    
    int matched;
    
    for (int pid = 0; pid <= product_count; pid++)
    {
        matched=0;
        for (int i= 0; i <= index; i++)
        {
            if (str_comparer(pIDs_of_specied_branch[i],all_in_one_array[pid][0]))
            {
                matched=1;
                
                for (int stockid = 1; stockid <= stock_count; stockid++)
                {
                    if (str_comparer(allstocks[stockid][3],"0") && str_comparer(pIDs_of_specied_branch[i],allstocks[stockid][1]))
                    {
                        matched=0;
                    }
                       
                }
                break;
            }
            
        }
        if (!matched)
        {
            for (int feat = 0; feat < feat_count; feat++)
            {
                j=0;
                while (all_in_one_array[pid][feat][j]!='\0')
                {
                    out_of_stock_products[outofproudtccount][feat][j]=all_in_one_array[pid][feat][j];
                    j++;
                }
                
                out_of_stock_products[outofproudtccount][feat][j]='\0';
            }
            outofproudtccount++;
        }
        
        
    }
    
    printf("Products that has no stock information in specied branch\nAnd products that has current_stock value 0:\n");


    for (int i = 0; i < outofproudtccount; i++)
    {
        for (int a = 0; a < feat_count; a++)
        {
            printf("%s\t\t",out_of_stock_products[i][a]);
        }
        
        printf("\n");
    }
}


void brand_stock_control(double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN],int *size,int *matched_products){
    
    int stocks_count=0,feat_count=0,product_count=0;    
    char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];
    char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN];

    reader(&feat_count,&product_count,&stocks_count,all_in_one_array,allstocks);

    char brand[MAX_FEAT_NAME_LEN];
    

    printf("Enter the brand:");
    scanf("%s",brand);

    int j;
    int index=0;
    int same_pid=0; //this variable is to check if the product has more than one stock entry
    
    int match_count=0;


    for (int pid = 1; pid <= product_count ; pid++)
    {
        
        if (str_comparer(all_in_one_array[pid][3],brand))
        {
            match_count++;
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
    

    
    *size= index;

}


void stock_report(double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN],int size,int matched_products){


    FILE *fpt=fopen("report.txt","w");

    int index=0;
    int index2;
    double temp_stocks[MAX_PRODUCT];

    printf("%d",matched_products);

    fprintf(fpt,"pID,min_stock_value,max_stock_value\n");

    for (int p = 0; p < matched_products; p++)
    {
        

        do
        {

            temp_stocks[index2]=results[index][2];
            printf("%lf",temp_stocks[index2]);
            index2++;

            
        } while (results[index][0]==results[index+1][0]);
        

        printf("%.2lf,%.2lf",temp_stocks[0],temp_stocks[1]);


        index2=0;
        index++;


    
    }
    

    fclose(fpt);

}



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



