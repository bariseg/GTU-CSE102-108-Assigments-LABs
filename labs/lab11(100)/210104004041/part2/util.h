#ifndef _UTIL_H_
#define _UTIL_H_


typedef struct ExamPaper
{
    char name[20];
    int number;
    int score;

    struct ExamPaper * next;
    
}ExamPaper;


ExamPaper * push(ExamPaper * stack, char * studentName, int studentNumber, int score);
void display(ExamPaper * exams);
ExamPaper * pop(ExamPaper * stack);
int isEmpty(ExamPaper * stack);

#endif /* _UTIL_H_ */
