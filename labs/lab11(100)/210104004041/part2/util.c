#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


ExamPaper * push(ExamPaper * stack, char * studentName, int studentNumber, int score){

    ExamPaper* newexam= (ExamPaper*)malloc(sizeof(ExamPaper));
    strcpy(newexam->name,studentName);
    newexam->number=studentNumber;
    newexam->score=score;
    
    if (isEmpty(stack))
    {
        newexam->next=NULL;
    }else{
        newexam->next=stack;
    }
    return newexam;

}


void display(ExamPaper * exams){

    ExamPaper *current= exams;
    while (current!=NULL)
    {
        printf("Name: %s    /Number:%d  /score:%d\n",current->name,current->number,current->score);
        current= current->next;
    }
}

ExamPaper * pop(ExamPaper * stack){

    ExamPaper *temp;

    if (!isEmpty(stack))
    {
        temp= stack->next;
        free(stack);
        return temp;
    }
}

int isEmpty(ExamPaper * stack){

    int result=1;

    if (stack!=NULL) result=0;
    
    return result;

}

