#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"


void enqueue(Order** list, char* customerName, int orderID, char* items, time_t orderTime){

    Order * norder;
    norder= (Order*)malloc(sizeof(Order));
    norder->next=NULL;
    strcpy(norder->custermname,customerName);
    norder->orderID=orderID;
    strcpy(norder->items,items);
    norder->ordertime=orderTime;

    if ((*list)==NULL)
    {
        (*list)=norder;
    }else{

        Order *curr= (*list);
        while(curr->next!=NULL) curr= curr->next;

        curr->next=norder;

    }

}

Order * dequeue(Order * list, time_t thresholdTime){

    Order *temp;

    if (list!=NULL)
    {
        temp= list->next;
        free(list);
        return temp;
    }
}


void serializeLIFO(exampaper* stack, const char* filename){

    FILE* fpt= fopen(filename,"wb");

    exampaper *curr= stack;

    while (curr!=NULL)
    {
        
        fwrite(curr->name,sizeof(char),20,fpt);
        fwrite(&(curr->number),sizeof(int),1,fpt);
        fwrite(&(curr->score),sizeof(int),1,fpt);

        curr=curr->next;

    }
    fclose(fpt);

    printf("LIFO SERIALIZED\n");
}

exampaper* deserializeLIFO(const char* filename){

    FILE*fpt=fopen(filename,"rb");

    char tempname[20];
    int tempnum,tempscore;
    
    exampaper *stack=NULL;
    exampaper * newnode;


    while (fread(tempname,sizeof(char),20,fpt)!=0)
    {
        newnode= (exampaper*)malloc(sizeof(exampaper));

        strcpy(newnode->name,tempname);

        fread(&tempnum,sizeof(int),1,fpt);
        newnode->number=tempnum;

        fread(&tempscore,sizeof(int),1,fpt);
        newnode->score=tempscore;

        newnode->next=NULL;

        if (stack==NULL)
        {
            newnode->next=NULL;
            stack=newnode;
        }else{
            newnode->next=stack;
        }
        stack=newnode;

    }
    
    fclose(fpt);
    printf("LIFO DESERIALIZED\n");
    return stack;
}


void serializeFIFO(Order* queue, const char* filename){

    FILE* fpt= fopen(filename,"wb");

    Order *curr= queue;

    while (curr!=NULL)
    {
        
        fwrite(curr->custermname,sizeof(char),20,fpt);
        fwrite(&(curr->orderID),sizeof(int),1,fpt);
        fwrite(curr->items,sizeof(char),50,fpt);
        fwrite(&(curr->ordertime),sizeof(time_t),1,fpt);

        curr=curr->next;

    }
    fclose(fpt);

    printf("FIFO SERIALIZED\n");
}

Order* deserializeFIFO(const char* filename){

    FILE*fpt= fopen(filename,"rb");


    Order* queue=NULL;
    Order *newnode;

    char tempcustomername[20];
    int temorderid;
    time_t temptime;
    char tempitems[50];

    while (fread(tempcustomername,sizeof(char),20,fpt )!=0)
    {
        newnode= (Order*)malloc(sizeof(Order));

        strcpy(newnode->custermname,tempcustomername);

        fread(&temorderid,sizeof(int),1,fpt);
        newnode->orderID=temorderid;

        fread(tempitems,sizeof(char),50,fpt);
        strcpy(newnode->items,tempitems);

        fread(&temptime,sizeof(time_t),1,fpt);
        newnode->ordertime=temptime;

        if (queue==NULL)
        {
            newnode->next=NULL;
            queue=newnode;
        }else{

            Order *curr=queue;
            while(curr->next!=NULL) curr= curr->next;

            curr->next=newnode;
        }
    }
    fclose(fpt);
    printf("FIFO DESERIALIZED\n");
    return queue;
}


void displayLIFO(exampaper * exams){

    exampaper *current= exams;
    while (current!=NULL)
    {
        printf("Name: %s    /Number:%d  /score:%d\n",current->name,current->number,current->score);
        current= current->next;
    }
}

void displayFIFO(Order * queue){

    Order *current= queue;
    while (current!=NULL)
    {
        printf("OrderID:%d  /Customer Name:%s    /Items:%s    \n",current->orderID,current->custermname,current->items);
        current= current->next;
    }
}



exampaper * push(exampaper * stack, char * studentName, int studentNumber, int score){

    exampaper* newexam= (exampaper*)malloc(sizeof(exampaper));
    strcpy(newexam->name,studentName);
    newexam->number=studentNumber;
    newexam->score=score;
    
    if (stack==NULL)
    {
        newexam->next=NULL;
    }else{
        newexam->next=stack;
    }
    return newexam;

}