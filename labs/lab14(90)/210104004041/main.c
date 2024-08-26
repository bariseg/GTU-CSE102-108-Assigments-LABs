#include <stdio.h>
#include <time.h>
#include "util.h"


int main(){


    
    exampaper* stack=NULL;

    stack=push(stack,"baris",241,14);
    stack=push(stack,"ereb",422,82);
    stack=push(stack,"mustafa",1881,94);
    stack=push(stack,"kemal",1919,100);
    
    serializeLIFO(stack,"lifo-data.bin");

    displayLIFO(stack);

    exampaper * readstack;

    readstack= deserializeLIFO("lifo-data.bin");

    printf("\n\n***********\n\n");
    displayLIFO(readstack);
    

    
    Order * queue=NULL;

    enqueue(&queue,"baris",4214,"pizza doner pasta",time(NULL));
    enqueue(&queue,"eren",4214,"makarna pide",time(NULL));
    enqueue(&queue,"mustafa",4214,"ayran ciger",time(NULL));
    enqueue(&queue,"kemal",4214,"sutlac kola",time(NULL));

    printf("\n\n\n\norders:\n");
    displayFIFO(queue);

    serializeFIFO(queue,"fifo-data.bin");


    Order *readqueue;
    readqueue= deserializeFIFO("fifo-data.bin");
    printf("\norders from file:\n");
    displayFIFO(queue);
    
    


    return 0;
}

