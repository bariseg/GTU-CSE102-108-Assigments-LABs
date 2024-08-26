#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct Order
{
    char custermname[20];
    int orderID;
    char items[50];
    time_t ordertime;

    struct Order* next;

}Order;

typedef struct exampaper
{
    char name[20];
    int number;
    int score;

    struct exampaper * next;
    
}exampaper;




void enqueue(Order** list, char* customerName, int orderID, char* items, time_t orderTime);
Order* dequeue(Order* list, time_t thresholdTime);


void serializeLIFO(exampaper* stack, const char* filename);
exampaper* deserializeLIFO(const char* filename);

void serializeFIFO(Order* queue, const char* filename);
Order* deserializeFIFO(const char* filename);


void displayLIFO(exampaper * exams);
void displayFIFO(Order * queue);
exampaper * push(exampaper * stack, char * studentName, int studentNumber, int score);

#endif /* _UTIL_H_ */
