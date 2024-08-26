#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


void display(Customer * custs){

    if(custs==NULL){
        printf("no customers yet!!\n");
    }else{

        printf("Name    age group\n");
        while (custs!=NULL)
        {
            printf("%s  %d  %s\n",custs->name,custs->age,custs->group);
            custs=custs->next;
        }
        
    }

}

void changePriority(Customer *custs,char *customername,int newlevel){

    int found_flag=0;

    if(custs==NULL){
        printf("no customers yet!!\n");
    }else{

        while (custs!=NULL)
        {
            if (strcmp(custs->name,customername)==0)
            {
                found_flag=1;
                custs->pri= newlevel;
                switch (newlevel)
                {
                case 1:
                    strcpy(custs->group,"NORMAL");
                    break;
                case 2:
                    strcpy(custs->group,"VETERAN");
                    break;
                case 3:
                    strcpy(custs->group,"OD");
                    break;
                case 4:
                    strcpy(custs->group,"VIP");
                    break;
                
                default:
                    break;
                }
                break;
            }
            custs=custs->next;
        }
        
    }
    
    if (!found_flag) printf("couldnt find customer %s\n",customername);

}

Customer * insertcustomer(Customer *custs,char* cname, int cage, char *cgroup){

    Customer * newcust= (Customer*)malloc(sizeof(Customer));
    newcust->age=cage;
    strcpy(newcust->name,cname);
    strcpy(newcust->group,cgroup);

    int ncustlevel;
    
    if (strcmp(cgroup,"VIP")==0)
    {
        ncustlevel=4;
        newcust->pri=ncustlevel;
    }else if(strcmp(cgroup,"OD")==0){
        ncustlevel=3;
        newcust->pri=ncustlevel;
    }else if(strcmp(cgroup,"VETERAN")==0){
        ncustlevel=2;
        newcust->pri=ncustlevel;
    }else if(strcmp(cgroup,"NORMAL")==0){
        ncustlevel=1;
        newcust->pri=ncustlevel;
    }
    

    if (custs==NULL) //no customer
    {
        newcust->prev=NULL;
        newcust->next=NULL;
        return newcust;
    }else if(custs->next==NULL){ //only 1 customer 

        if (custs->pri < ncustlevel) //new custoemr has the highest priority
        {
            newcust->prev=NULL;
            newcust->next=custs;
            custs->next=NULL;
            custs->prev=newcust;

            return newcust;

        }else{ //fifo

            custs->next=newcust;
            custs->prev=NULL;

            newcust->next=NULL;
            newcust->prev=custs;

            return custs;

        }
    
    }else{ //more than 1 customers

        if (custs->pri < ncustlevel) //new customer has the highest priority
        {
            newcust->prev=NULL;
            newcust->next=custs;
            custs->prev=newcust;

            return newcust;
        }else{

            Customer * current= custs;
            while (current->next!=NULL &&current->next->pri>=ncustlevel) current=current->next;
            
            if (current->next == NULL) {
                newcust->prev = current;
                newcust->next = NULL;
                current->next = newcust;

            }else{

                newcust->prev = current;
                newcust->next = current->next;
                current->next->prev = newcust;
                current->next = newcust;
            }

            return custs;
            
        }

    }

    



}

Customer * removeCustomer(Customer *custs,char* cname){

    if (custs!=NULL)
    {
        Customer *temp=custs;
        if (custs->next==NULL)
        {
            custs=NULL;
            free(temp);
            return custs;

        }else{

            if (strcmp(custs->name,cname)==0)
            {
                custs->next->prev=NULL;
                free(temp);
                return custs->next;
            }else{

                while (temp!=NULL)
                {
                    if (strcmp(temp->name,cname)==0)
                    {
                        if (temp->next==NULL) //last customer is gonna be deleted
                        {
                            temp->prev->next=NULL;
                        }else{ //in the middle
                            temp->next->prev=temp->prev;
                            temp->prev->next=temp->next;
                                                      
                        }
                        free(temp);
                        return custs;  

                    }
                    temp=temp->next;
                }
            
            }
            
        
        }
        return custs;
    }

}



void searchingcustomers(Customer *custs, char *name){

    if (custs!=NULL)
    {
        
        if (strcmp(custs->name,name)==0)
        {
            printf("Found: %s   %d  %s  %d\n",custs->name,custs->age,custs->group,custs->pri);
        }else{

            searchingcustomers(custs->next,name);
        }
    }
}


