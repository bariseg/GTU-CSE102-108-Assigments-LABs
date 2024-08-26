#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){

    char option;
    int menu_flag=1;

    char isbn[14],title[20],author[20];
    int pub_year,method;
    char feat[20],value[20];
    

    int student_count=0,book_count=0;
    Book* books= NULL;
    Student* students=NULL;
    file_reader(&books,&students,&book_count,&student_count);

    //printbooks(books);

    do
    {
        //printbooks(books);
        //printstudents(students);
        printf("\nWelcome to the Library Book Management System\n\n");
        printf("Please select an option:\n");
        printf( "1. Show student borrowed books\n"
                "2. Add a new book\n"
                "3. Delete a book\n"
                "4. Update a book information\n"
                "5. Filter and Sort books\n"
                "6. Reverse book list\n"
                "7. Search book\n"
                "8. Borrow Book\n"
                "9. Return Book\n"
                "0. Exit\n"
                ">  ");
        scanf(" %c",&option);

        switch (option)
        {

        case '1':
            int sid;
            printf("Enter student id:");
            scanf("%d",&sid);
            student_borrowed_books(students,sid,books);
            break;

        case '2':
            
            printf("Enter details\n");
            printf("isbn:");
            scanf("%s",isbn);
            printf("title:");
            scanf(" %[^\n]s",title);
            printf("author:");
            scanf(" %[^\n]s",author );
            printf("publication year:");
            scanf("%d",&pub_year);
            printf("method (0:fifo,1:lifo):");
            scanf("%d",&method);

            addbook(&books, isbn, title, author, pub_year, method, 0);
            book_file_update(books);
            break;
        
        case '3':
            printf("Enter the isbn of the book to be removed:");
            scanf("%s",isbn);

            deleteBook(&books,isbn);
            book_file_update(books);
            break;
        
        case '4':
            printf("Enter the ISBN of the book to be updated:");
            scanf("%s",isbn);
            printf("Enter the feature name to be updated(title/author/publication year):");
            scanf(" %[^\n]s",feat);
            printf("Enter new value:");
            scanf(" %[^\n]s",value);

            updateBook(books,isbn,feat,value);
            book_file_update(books);
            break;

        case '5':
            int filter_c,sort_c;
            char filter[20];
            printf("Enter filter choice(0.author 1.publication year):");
            scanf("%d",&filter_c);
            printf("Enter filter criteria:");
            scanf(" %[^\n]s",filter);
            printf("Enter sort choice(0.title 1.author 2.publication year):");
            scanf("%d",&sort_c);

            filterAndSortBooks(books,filter_c,filter,sort_c);
            break;
        
        case '6':
            reverseBookList(&books);
            printbooks(books);
            break;
        
        
        case '7':
            int searchchoice;
            char searchcriter[20];
            printf("Enter search choice(0.ISBN 1.Author 2.Title):");
            scanf("%d",&searchchoice);
            printf("Enter search criteria:");
            scanf(" %[^\n]s",searchcriter);

            printf("ISBN    TITLE   AUTHOR  P.YEAR  RESERVED STATUS\n\n");
            searchBooks(books,searchchoice,searchcriter);
            break;
        
        case '8':
            printf("Enter the ISBN of the book to be borrowed:");
            scanf("%s",isbn);

            borrowBook(books,isbn);
            book_file_update(books);
            break;

        case '9':
            printf("Enter the ISBN of the book to be returned:");
            scanf("%s",isbn);

            returnBook(books,isbn);
            book_file_update(books);
            break;

        case '0':
            printf("Exiting!\n");
            menu_flag=0;
            break;
            
        default:
            printf("Invalid input!!\n\n");
            break;
        }
    } while (menu_flag);
    

    free(books);
    free(students);

    return(0);
}

