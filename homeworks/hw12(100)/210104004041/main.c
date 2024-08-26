#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"


int main(){

    Node *head=NULL;

    srand(time(NULL));

    fillLinkedList(&head);

    printf("first list\n");
    printlist(head);

    serializeLinkedList(head);


    Node *newhead=NULL;

    deserializeLinkedList(&newhead);

    printf("\n\n****LIST READ FROM FILE****\n");
    printlist(newhead);


    return 0;
}

