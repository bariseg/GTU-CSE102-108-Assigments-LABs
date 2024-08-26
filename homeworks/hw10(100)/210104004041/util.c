#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"



void student_borrowed_books(Student* ll_students,int stu_id,Book *ll_books){

    int flag;
    int i;
    
    printf("ISBN    TITLE   AUTHOR  P.YEAR  RESERVED STATUS\n\n");
    while (ll_students!=NULL)
    {
        if (ll_students->id==stu_id)
        {
            i=0,flag=1;
            while (flag)
            {
                if (strcmp(ll_students->brrwd_books[i],"1")==0)
                {
                    flag=0;
                }else{
                    searchBooks(ll_books,0,ll_students->brrwd_books[i]);
                    i++;
                }
            }
            break;
        }
        ll_students=ll_students->next;
    }
}

void printbooks(Book* ll_books){

    Book *currn =ll_books;
    while (currn != NULL) {
        printf("%s %s %s %d %d\n", currn->ISBN, currn->title, currn->author, currn->public_year,currn->reserved_status);
        currn = currn->next;
    }
}

void printstudents(Student* ll_students){

    int flag=1;
    int i;
    Student *currn =ll_students;
    while (currn != NULL) {
        
        printf("%s %d ", currn->name, currn->id);
        flag=1,i=0;
        while (flag)
        {   
            if (strcmp(currn->brrwd_books[i],"1")==0)
            {
                flag=0;
            }else{
                printf("%s ",currn->brrwd_books[i]);
                i++;
            }
        }
        currn = currn->next;
        printf("\n");
    }
}

void book_file_update(Book* ll_books){

    FILE *fpt= fopen("books.txt","w");

    Book*curr =ll_books;
    while (curr!=NULL)
    {
        fprintf(fpt,"%s,",curr->ISBN);
        fprintf(fpt,"%s,",curr->title);
        fprintf(fpt,"%s,",curr->author);
        fprintf(fpt,"%d,",curr->public_year);
        fprintf(fpt,"%d\n",curr->reserved_status);

        curr= curr->next;
    }
    
    fclose(fpt);

}

void file_reader(Book **ll_books,Student **ll_students,int *book_count,int *stu_count){

    FILE *bookfpt=fopen("books.txt","r");
    
    if (bookfpt!=NULL)
    {
        char t_isbn[14],t_title[20],t_author[20];
        int t_year,t_reserved;

        while ((fscanf(bookfpt,"%[^,]s",t_isbn))!=EOF)
        {
            fgetc(bookfpt); //comma
            
            fscanf(bookfpt,"%[^,]s",t_title);
            fgetc(bookfpt); 

            fscanf(bookfpt,"%[^,]s",t_author);
            fgetc(bookfpt); 

            fscanf(bookfpt,"%d",&t_year);
            fgetc(bookfpt); 

            fscanf(bookfpt,"%d",&t_reserved);
            fgetc(bookfpt); //new line character

            addbook(ll_books,t_isbn,t_title,t_author,t_year,0,t_reserved);
        }

    }else{
        printf("Book file opening error!!\n");
    }
    fclose(bookfpt);
    

    FILE *stufile=fopen("students.txt","r");
    if (stufile!=NULL)
    {
        char name[20];
        int temp_id;
        char* bookisbn;
        int tempindex;
        
        char isbnline[141]; //max 10 isbn * (13 +1 comma) - (1 comma) + (1 \n) + (1 \0) 
        while ((fscanf(stufile,"%[^,]s",name))!=EOF)
        {
            fgetc(stufile); //comma
            
            fscanf(stufile,"%d",&temp_id);
            fgetc(stufile); //comma

            tempindex=0;

            fscanf(stufile, "%[^\n]s",isbnline);
            fgetc(stufile); // \n
            tempindex=0;
            bookisbn= strtok(isbnline, ",");
            while (bookisbn!=NULL)
            {
                //printf("%s\n",bookisbn);
                addstudent(ll_students,name,temp_id,bookisbn,tempindex);
                
                bookisbn= strtok(NULL, ",");
                tempindex++;
            }
        }

    }else{
        printf("Student file opening error!!\n");
    }
    
    fclose(stufile);

}

void sorter(Book **ll_books){

    int swapped;
    Book* current;
    Book* temp = NULL;
    Book* nxt;
    Book* previous;
    do {
        swapped= 0;
        current= *ll_books;
        previous=NULL;

        while (current->next != temp) {
            nxt = current->next;

            if (nxt != NULL && strcmp(current->ISBN, nxt->ISBN) > 0) {
                if (previous != NULL) {
                    previous->next = nxt;
                } else {
                    *ll_books = nxt;
                }

                current->next = nxt->next;
                nxt->next = current;

                previous = nxt;
                swapped = 1;
            } else {
                previous = current;
                current = nxt;
            }
        }
        temp = current;
    } while (swapped);
}

//this function is not for the user.its used in file_read in order to create students linked list
void addstudent(Student**ll_stu,char* name,int id ,char* isbn, int index){

    if (index==0)
    {
        Student * new_student=(Student*)malloc(sizeof(Student));

        strcpy(new_student->name,name);
        new_student->id=id;
        strcpy(new_student->brrwd_books[index],isbn);

        if ((*ll_stu)==NULL)
        {
            (*ll_stu)=new_student;
        }else{ //addind from beginning
            new_student->next=(*ll_stu);
            (*ll_stu)= new_student;
        }

    }else{
            strcpy((*ll_stu)->brrwd_books[index],isbn);
            
    }
    //printf("%s %d %s\n",(*ll_stu)->name,(*ll_stu)->id,(*ll_stu)->brrwd_books[index]);
    
}

void addbook(Book**ll_books,char* isbn, char* title, char* author, int publicationYear, int method, int reserv){

    Book * new_book=(Book*)malloc(sizeof(Book));

    strcpy(new_book->ISBN,isbn);
    strcpy(new_book->title,title);
    strcpy(new_book->author,author);
    new_book->public_year=publicationYear;
    new_book->reserved_status=reserv;
    new_book->next=NULL;

    if ((*ll_books)==NULL)
    {
        *ll_books = new_book;
    }else{
        if (method==0) //fifo //sondan
        {
            Book*curr= *ll_books;
            while (curr->next!=NULL) curr=curr->next;
            
            curr->next=new_book;
            
        }else if(method==1){ //lifo //bastan

            new_book->next= (*ll_books);
            (*ll_books)=new_book;
        }
    }

}

void deleteBook(Book **ll_books,char* isbn){

    Book* temp_book = *ll_books;
    Book* prev= *ll_books;
    //printf("girilen isbn:%s\n",isbn);
    if (temp_book==NULL)
    {
        printf("There are no books recorded!!\n");
    }else{
        
        if (strcmp(temp_book->ISBN,isbn)==0)//first element 
        {
            *ll_books= (*ll_books)->next;
            free(temp_book);
            printf("The deletion was succesfull!!\n");
        }else{
            
            while (temp_book!=NULL)
            {
                if(strcmp(temp_book->ISBN,isbn) == 0)
                {
                    prev->next=temp_book->next;
                    free(temp_book);
                    printf("The deletion was succesfull!!\n");
                    break;
                }
                prev=temp_book;
                temp_book=temp_book->next;
            }
            
        }
    }
}

void updateBook(Book *ll_books, char* isbn, char* feature, char* value){

    Book *curr= ll_books;
    int succes_flag=0;
    while (curr!=NULL)
    {
        if(strcmp(curr->ISBN,isbn)==0){
            succes_flag=1;
            if (strcmp(feature,"title")==0)
            {
                strcpy(curr->title, value);
                succes_flag++;
            }else if(strcmp(feature,"author")==0){
                strcpy(curr->author, value);
                succes_flag++;
            }else if(strcmp(feature,"publication year")==0){
                curr->public_year= atoi(value);
                succes_flag++;
            }
            break;
        }
        curr=curr->next;
    }
    switch (succes_flag)
    {
    case 0:
        printf("No book find by ISBN:%s !!\n",isbn);
        break;
    case 1:
        printf("Feature name error:%s !!\n",feature);
        break;
    case 2:
        printf("Updating succesfull!!\n");
        break;
    default:
        break;
    }
    

}

void searchBooks(Book *ll_books,int searchChoice, char* searchValue){

    Book *currn= ll_books;
    int found_flag=0;
    
    while (currn!=NULL)
    {
        if (searchChoice==0 && strcmp(currn->ISBN,searchValue)==0){
            printf("%s %s %s %d %d\n", currn->ISBN, currn->title, currn->author, currn->public_year,currn->reserved_status);
            found_flag=1;
        }else if (searchChoice==1 && strcmp(currn->author,searchValue)==0){
            printf("%s %s %s %d %d\n", currn->ISBN, currn->title, currn->author, currn->public_year,currn->reserved_status);
            found_flag=1;
        }else if (searchChoice==2 && strcmp(currn->title,searchValue)==0){
            printf("%s %s %s %d %d\n", currn->ISBN, currn->title, currn->author, currn->public_year,currn->reserved_status);
            found_flag=1;
        }
        currn=currn->next;
    }
    if (!found_flag) printf("No books found!!\n\n");

    
}

void borrowBook(Book* ll_books,char* isbn){

    Book *curr= ll_books;
    while (curr!=NULL)
    {
        if(strcmp(curr->ISBN,isbn)==0){
            curr->reserved_status=1;
            printf("Succesfully borrowed(%s,%s)!!!\n",curr->ISBN,curr->title);
            break;
        }
        curr=curr->next;
    }
}

void returnBook(Book* ll_books,char* isbn){

    Book *curr= ll_books;
    while (curr!=NULL)
    {
        if(strcmp(curr->ISBN,isbn)==0){
            curr->reserved_status=0;
            printf("Succesfully returned(%s,%s)!!!\n",curr->ISBN,curr->title);
            break;
        }
        curr=curr->next;
    }
}

void reverseBookList(Book**ll_books){

    //first bubble sorting
    if (*ll_books == NULL || (*ll_books)->next == NULL) {
        printf("There are not enough books to sort and reverse");
    } else {
        sorter(ll_books);

        //after, reverse the lists
        Book*currn= *ll_books;
        Book* prev=NULL;
        Book* next=NULL;
        while (currn!=NULL)
        {
            next= currn->next;
            currn->next= prev;
            prev=currn;
            currn=next;
        }
        
        *ll_books= prev;

    }

}

void filterAndSortBooks(Book*ll_books,int filterChoice, char* filter, int sortChoice){

    int found_flag=0;
    Book* filtered_list=NULL;
    Book* curr= ll_books;
    while (curr!=NULL)
    {
        if (filterChoice==0 && strcmp(curr->author,filter)==0)
        {   
            found_flag=1;
            addbook(&filtered_list,curr->ISBN,curr->title,curr->author,curr->public_year,0,curr->reserved_status);
        }else if(filterChoice==1 && curr->public_year==atoi(filter)){
            found_flag=1;
            addbook(&filtered_list,curr->ISBN,curr->title,curr->author,curr->public_year,0,curr->reserved_status);
        }

        curr=curr->next;
    }
    
    if (found_flag)
    {
        //sorting
        int swapped;
        Book* current;
        Book* temp = NULL;
        Book* nxt;
        Book* previous;
        do {
            swapped= 0;
            current= filtered_list;
            previous=NULL;

            while (current->next != temp) {
                nxt = current->next;

                if (sortChoice==0 && (nxt != NULL && strcmp(current->title, nxt->title) > 0)) {
                    if (previous != NULL) {
                        previous->next = nxt;
                    } else {
                        filtered_list = nxt;
                    }

                    current->next = nxt->next;
                    nxt->next = current;

                    previous = nxt;
                    swapped = 1;
                }else if (sortChoice==1 &&(nxt != NULL && strcmp(current->author, nxt->author)) > 0) {
                    if (previous != NULL) {
                        previous->next = nxt;
                    } else {
                        filtered_list = nxt;
                    }

                    current->next = nxt->next;
                    nxt->next = current;

                    previous = nxt;
                    swapped = 1;
                }else if (sortChoice==2 &&(nxt != NULL && current->public_year > nxt->public_year)) {
                    if (previous != NULL) {
                        previous->next = nxt;
                    } else {
                        filtered_list = nxt;
                    }

                    current->next = nxt->next;
                    nxt->next = current;

                    previous = nxt;
                    swapped = 1;
    
                } else {
                    previous = current;
                    current = nxt;
                }
            }
            temp = current;
        } while (swapped);
            

        printf("ISBN    TITLE   AUTHOR  P.YEAR  RESERVED STATUS\n\n");
        printbooks(filtered_list);
    }else{
        printf("No book found!!\n\a");
    }

    free(filtered_list);
}
