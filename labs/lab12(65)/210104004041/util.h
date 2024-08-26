#ifndef _UTIL_H_
#define _UTIL_H_

    typedef struct Customer
    {
        char name[20];
        int age;
        char group[10];
        int pri;        

        struct Customer* prev;
        struct Customer* next;
        

    }Customer;
    
void display(Customer * custs);

void changePriority(Customer *custs,char *customername,int newlevel);

Customer * insertcustomer(Customer *custs,char* cname, int cage, char *cgroup);

Customer * removeCustomer(Customer *custs,char* cname);

void searchingcustomers(Customer *custs, char *name);

#endif /* _UTIL_H_ */
