#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT 20
#define MAX_LINE_SIZE 300

typedef struct 
{
    char name[15];
    char color[15];
    double price;
    int serial_num;
    int quantity;
}furniture_s;

void search(furniture_s furns[MAX_PRODUCT],int furn_count,char filter[20],int opt);
void reader(furniture_s furns[MAX_PRODUCT],int *furn_count);
void see_all();
void add_furn();
void remove_furn(int furn_count,furniture_s furns[MAX_PRODUCT]);


int main(){

    furniture_s furnitures[MAX_PRODUCT];
    int menu_flag=1;
    char option;
    int furn_count;

    int opt;
    char filtercric[20];

    do
    {
        reader(furnitures,&furn_count);

        /*
        for (int i = 0; i < 8; i++)
        {
            printf("%s ",furnitures[i].name);
            printf("%s ",furnitures[i].color);
            printf("%lf ",furnitures[i].price);
            printf("%d ",furnitures[i].serial_num);
            printf("%d \n",furnitures[i].quantity);
            
        }*/
        



        printf("\n1- See all furnitures\n2- Add a new furniture\n3- Remove furniture\n4- Search furniture\n5- Exit\n");
        printf("Option:");
        scanf(" %c",&option);


        switch (option)
        {
        case '1':
            see_all();
            break;
        case '2':
            add_furn();
            break;
        case '3':
            remove_furn(furn_count,furnitures);
            break;
        case '4':
            
            printf("1.by name\n2.by color\noption:");
            scanf("%d",&opt);
            printf("enter filter critic:");
            scanf("%s",filtercric);

            search(furnitures,furn_count,filtercric,opt);
            break;
        case '5':
            
            menu_flag=0;
            break;
        
        
        default:
            printf("Invalid input!!\n\n");
            break;
        }



    } while (menu_flag);








    return 0;
}


void reader(furniture_s furns[MAX_PRODUCT],int *furn_count){

    FILE*fpt=fopen("furniture_database.txt","r");

    
    furniture_s furniture;
    char *feature;
    char line[MAX_LINE_SIZE];
    double temp_price;
    int temp_serial;
    int temp_quant;

    int temp_furn_count=0;
    while (fgets(line,MAX_LINE_SIZE,fpt)!=NULL)
    {
        feature=strtok(line, " ");
        strcpy(furniture.name,feature);

        feature=strtok(NULL, " ");
        strcpy(furniture.color,feature);
        
        feature=strtok(NULL, " ");
        temp_price= atof(feature);
        furniture.price=temp_price;

        feature=strtok(NULL, " ");
        temp_serial=atoi(feature);
        furniture.serial_num=temp_serial;

        feature=strtok(NULL, " ");
        temp_quant=atoi(feature);
        furniture.quantity=temp_quant;

        furns[temp_furn_count]=furniture;

        temp_furn_count++;

    }
    
    *furn_count=temp_furn_count;



    fclose(fpt);
}


void add_furn(){

    FILE *fpt=fopen("furniture_database.txt","a");

    char input_str[MAX_LINE_SIZE];

    printf("Enter properties (Name color price serial number quantity):");

    for (int i = 0; i < 5; i++)
    {
        
        scanf(" %s",input_str);

        fprintf(fpt,"%s ",input_str);

    }
    fprintf(fpt,"\n");
        

    fclose(fpt);
}

void see_all(){

    FILE*fpt=fopen("furniture_database.txt","r");

    char char_read;
    printf("\nName color price serial number quantity\n");

    while ((char_read=fgetc(fpt))!=EOF)
    {
        printf("%c",char_read);
    }

    fclose(fpt);
}

void remove_furn(int furn_count,furniture_s furns[MAX_PRODUCT]){

    int index;
    printf("Enter the index:");
    scanf("%d",&index);

    printf("Furniture to be removed:\n");
    
    printf("name:%s\n",furns[index].name);
    printf("color:%s\n",furns[index].color);
    printf("price:%lf\n",furns[index].price);
    printf("serialnumber:%d\n",furns[index].serial_num);
    printf("quantity:%d\n",furns[index].quantity);

    FILE* fpt=fopen("furniture_database.txt","w");

    for (int i = 0; i < furn_count; i++)
    {
        if (i!=index)
        {
            fprintf(fpt,"%s ",furns[i].name);
            fprintf(fpt,"%s ",furns[i].color);
            fprintf(fpt,"%lf ",furns[i].price);
            fprintf(fpt,"%d ",furns[i].serial_num);
            fprintf(fpt,"%d ",furns[i].quantity);
            fprintf(fpt,"\n");
        }
    }

    

    fclose(fpt);
}

void search(furniture_s furns[MAX_PRODUCT],int furn_count,char filter[20],int opt){

    if (furn_count==1)
    {
        if (opt==1) //name
        {
            if ((strcmp(furns[furn_count].name,filter))==0)
            {
                printf("%s ",furns[furn_count].name);
                printf("%s ",furns[furn_count].color);
                printf("%lf ",furns[furn_count].price);
                printf("%d ",furns[furn_count].serial_num);
                printf("%d \n",furns[furn_count].quantity);
                    
            }
        }else{ //color

            if ((strcmp(furns[furn_count].color,filter))==0)
            {
                printf("%s ",furns[furn_count].name);
                printf("%s ",furns[furn_count].color);
                printf("%lf ",furns[furn_count].price);
                printf("%d ",furns[furn_count].serial_num);
                printf("%d \n",furns[furn_count].quantity);
                    
            }
        }
        

    }else{
        search(furns,furn_count-1,filter,opt);

        if (opt==1) //name
        {
            if ((strcmp(furns[furn_count].name,filter))==0)
            {
                printf("%s ",furns[furn_count].name);
                printf("%s ",furns[furn_count].color);
                printf("%lf ",furns[furn_count].price);
                printf("%d ",furns[furn_count].serial_num);
                printf("%d \n",furns[furn_count].quantity);
                    
            }
            


        }else{ //color

            if ((strcmp(furns[furn_count].color,filter))==0)
            {
                printf("%s ",furns[furn_count].name);
                printf("%s ",furns[furn_count].color);
                printf("%lf ",furns[furn_count].price);
                printf("%d ",furns[furn_count].serial_num);
                printf("%d \n",furns[furn_count].quantity);
                    
            }
        }

    }
    




}

