#ifndef _UTIL_H_
#define _UTIL_H_


typedef struct Order
{
    char custermname[20];
    int orderID;
    char items[50];
    char ordertime[50];

    struct Order* next;

}Order;


Order * enqueue(Order * queue, char * customerName, int orderID, char * items, char * orderTime);
Order * dequeue(Order * queue);
void display(Order * queue);
void updateOrder(Order * queue, int orderID, char * newItems);


#endif /* _UTIL_H_ */
