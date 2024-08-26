#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "util.h"


void fillLinkedList(struct Node** head){

    int astcount= (rand() % 11)+10; // asset count 10-20
    //printf("count:%d\n",astcount);
    int assettype; //random chosen assettype

    //temp assests used in each loop
    void *newasset;
    Node *newnode,*curr=NULL;
    Asset1 *tempas1;
    Asset2 *tempas2;
    Asset3 *tempas3;
    Asset4 *tempas4;
    
    int i;
    for (i=0; i < astcount; i++)
    {
        assettype= rand() % 4;

        switch (assettype)
        {
        case 0: //asset type1
            //printf("type1 added\n");
            newasset= malloc(sizeof(Asset1));
            tempas1= (Asset1*)newasset;
            strcpy(tempas1->type,"typeone");
            tempas1->ivals[0]= rand() % 100;
            tempas1->svals[0]= rand() % 100;
            tempas1->svals[0]+= (rand()%100)*0.01;

            break;
        case 1:
            //printf("type2 added\n");
            newasset= malloc(sizeof(Asset2));
            tempas2= (Asset2*)newasset;
            strcpy(tempas2->type,"typetwo");
            tempas2->ivals[0]= rand() % 100;
            tempas2->ivals[1]= rand() % 100;
            
            tempas2->svals[0]= rand() % 100;
            tempas2->svals[0]+= (rand()%100)*0.01;

            tempas2->svals[1]= rand() % 100;
            tempas2->svals[1]+= (rand()%100)*0.01;

            break;
        case 2:
            //printf("type3 added\n");
            newasset= malloc(sizeof(Asset3));
            tempas3=(Asset3*)newasset;

            strcpy(tempas3->type,"typethree");
            strcpy(tempas3->string1,"crazystringone");
            strcpy(tempas3->string2,"bariserengezici");

            break;
        case 3:
            //printf("type4 added\n");
            newasset= malloc(sizeof(Asset4));
            tempas4= (Asset4*)newasset;
            strcpy(tempas4->type,"typefour");

            tempas4->value1 = rand() % 100;
            tempas4->value1+= (rand()%100)*0.01;

            tempas4->value2 = rand() % 100;
            tempas4->value2+= (rand()%100)*0.01;

            tempas4->value3 = rand() % 100;
            tempas4->value3+= (rand()%100)*0.01;

            break;
        
        }
    
        newnode=(Node*)malloc(sizeof(Node));
        newnode->data= newasset;
        newnode->next=NULL;

        if (curr==NULL){ //assigning head
            (*head)= newnode;
            curr=(*head);
        }else{
            curr->next=newnode;
            curr=curr->next;
        }
        
    }
    
}

void serializeLinkedList(struct Node* head){

    FILE *fpt= fopen("linkedlist.bin","wb");

    Node* curr= head;
    void* tempdata;
    while (curr!=NULL)
    {
        tempdata= curr->data;

        if (strcmp(((Asset1*)tempdata)->type, "typeone") == 0) {

            //printf("1\n");
            fwrite(((Asset1*)tempdata)->type,sizeof(char),20,fpt);
            fwrite(&( ((Asset1*)tempdata)->ivals[0] ),sizeof(int),1,fpt);
            fwrite(&( ((Asset1*)tempdata)->svals[0] ),sizeof(double),1,fpt);
        
        }else if (strcmp(((Asset2*)tempdata)->type, "typetwo") == 0) {
            //printf("2\n");
            fwrite(((Asset2*)tempdata)->type,sizeof(char),20,fpt);
            fwrite(&( ((Asset2*)tempdata)->ivals[0] ),sizeof(int),1,fpt);
            fwrite(&( ((Asset2*)tempdata)->ivals[1] ),sizeof(int),1,fpt);
            
            fwrite(&( ((Asset2*)tempdata)->svals[0] ),sizeof(double),1,fpt);
            fwrite(&( ((Asset2*)tempdata)->svals[1] ),sizeof(double),1,fpt);

        }else if (strcmp(((Asset3*)tempdata)->type, "typethree") == 0) {
            //printf("3\n");
            fwrite(((Asset3*)tempdata)->type,sizeof(char),20,fpt);
            fwrite(((Asset3*)tempdata)->string1,sizeof(char),50,fpt);
            fwrite(((Asset3*)tempdata)->string2,sizeof(char),50,fpt);

        }else if (strcmp(((Asset4*)tempdata)->type, "typefour") == 0) {
            //printf("4\n");
            fwrite(((Asset4*)tempdata)->type,sizeof(char),20,fpt);
            fwrite(&( ((Asset4*)tempdata)->value1 ),sizeof(double),1,fpt);
            fwrite(&( ((Asset4*)tempdata)->value2 ),sizeof(float),1,fpt);
            fwrite(&( ((Asset4*)tempdata)->value3 ),sizeof(double),1,fpt);
        }
    
        curr=curr->next;
    }
    fclose(fpt);
}

void deserializeLinkedList(struct Node** head){

    FILE *fpt= fopen("linkedlist.bin","rb");

    void *newasset;
    Node *newnode,*curr=NULL;

    Asset1 *tempas1;
    Asset2 *tempas2;
    Asset3 *tempas3;
    Asset4 *tempas4;

    char temptype[20];

    while (fread(temptype,sizeof(char),20,fpt)!=0)
    {   
        
        if (strcmp(temptype,"typeone")==0)
        {
            newasset= malloc(sizeof(Asset1));
            tempas1= (Asset1*)newasset;

            strcpy(tempas1->type,temptype);
            fread(&( tempas1->ivals[0] ),sizeof(int),1,fpt);
            fread(&( tempas1->svals[0] ),sizeof(double),1,fpt);

        }else if (strcmp(temptype,"typetwo")==0)
        {
            newasset= malloc(sizeof(Asset2));
            tempas2= (Asset2*)newasset;

            strcpy(tempas2->type,temptype);
            fread(&( tempas2->ivals[0] ),sizeof(int),1,fpt);
            fread(&( tempas2->ivals[1] ),sizeof(int),1,fpt);
            fread(&( tempas2->svals[0] ),sizeof(double),1,fpt);            
            fread(&( tempas2->svals[1] ),sizeof(double),1,fpt);


        }else if (strcmp(temptype,"typethree")==0)
        {
            newasset= malloc(sizeof(Asset3));
            tempas3= (Asset3*)newasset;

            strcpy(tempas3->type,temptype);
            fread(tempas3->string1,sizeof(char),50,fpt);
            fread(tempas3->string2,sizeof(char),50,fpt);

        }else if (strcmp(temptype,"typefour")==0)
        {
            newasset= malloc(sizeof(Asset4));
            tempas4= (Asset4*)newasset;
            
            strcpy(tempas4->type,temptype);
            fread(&( tempas4->value1 ),sizeof(double),1,fpt);
            fread(&( tempas4->value2 ),sizeof(float),1,fpt);
            fread(&( tempas4->value3 ),sizeof(double),1,fpt);

        }
            
        newnode=(Node*)malloc(sizeof(Node));
        newnode->data= newasset;
        newnode->next=NULL;

        if (curr==NULL){ //assigning head
            (*head)= newnode;
            curr=(*head);
        }else{
            curr->next=newnode;
            curr=curr->next;
        }
    
    }
    
    fclose(fpt);

}

void printlist(struct Node* head){

    Node* curr= head;
    void* tempdata;
    while (curr!=NULL)
    {
        tempdata= curr->data;

        if (strcmp(((Asset1*)tempdata)->type, "typeone") == 0) {
            printf("Asset type: Asset1\n");
            printf("ivals:%d\n",((Asset1*)tempdata)->ivals[0]);
            printf("svals:%.2lf\n\n",((Asset1*)tempdata)->svals[0]);
        }else if (strcmp(((Asset2*)tempdata)->type, "typetwo") == 0) {
            printf("Asset type: Asset2\n");
            printf("ivals:%d",((Asset2*)tempdata)->ivals[0]);
            printf(",%d\n",((Asset2*)tempdata)->ivals[1]);

            printf("svals:%.2lf",((Asset2*)tempdata)->svals[0]);
            printf(",%.2lf\n\n",((Asset2*)tempdata)->svals[1]);

        }else if (strcmp(((Asset3*)tempdata)->type, "typethree") == 0) {
            printf("Asset type: Asset3\n");

            printf("string1:%s\n",((Asset3*)tempdata)->string1);
            printf("string2:%s\n\n",((Asset3*)tempdata)->string2);

        }else if (strcmp(((Asset4*)tempdata)->type, "typefour") == 0) {
            printf("Asset type: Asset4\n");

            printf("value1:%.2lf\n",((Asset4*)tempdata)->value1);
            printf("value2:%.2f\n",((Asset4*)tempdata)->value2);
            printf("value3:%.2lf\n\n",((Asset4*)tempdata)->value3);

        }
    
        curr=curr->next;
    }

}

