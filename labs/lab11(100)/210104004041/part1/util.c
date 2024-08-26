#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"



Order * enqueue(Order * queue, char * customerName, int orderID, char * items, char * orderTime){

    Order * norder;
    norder= (Order*)malloc(sizeof(Order));
    norder->next=NULL;
    strcpy(norder->custermname,customerName);
    norder->orderID=orderID;
    strcpy(norder->items,items);
    strcpy(norder->ordertime,orderTime);


    if (queue==NULL)
    {
        return norder;
    }else{

        Order *curr= queue;
        while(curr->next!=NULL) curr= curr->next;

        curr->next=norder;

        return queue;
    }    
}

Order * dequeue(Order * queue){

    Order *temp;

    if (queue!=NULL)
    {
        temp= queue->next;
        free(queue);
        return temp;
    }
}

void display(Order * queue){

    Order *current= queue;
    while (current!=NULL)
    {
        printf("OrderID:%d  /Customer Name:%s    /Items:%s    \n",current->orderID,current->custermname,current->items);
        current= current->next;
    }
}

void updateOrder(Order * queue, int orderID, char * newItems){

    Order *current=queue;
    int found_flag=0;

    if (current==NULL)
    {
        printf("No orders yet\n");
    }else{
        while (current!=NULL)
        {
            if (orderID==current->orderID)
            {
                found_flag=1;
                strcpy(current->items,newItems);
                break;
            }
            current=current->next;
        }

        if (found_flag==0) printf("No order by orderid:%d\n",orderID);
        
    }
}