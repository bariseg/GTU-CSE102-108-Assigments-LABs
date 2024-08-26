#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct Book
{
    char ISBN[14]; //975-6856-00-9
    int public_year;
    int reserved_status;
    char title[20];
    char author[20];
    
    struct Book * next;
}Book;

typedef struct Student
{
    char name[20];
    int id;
    char brrwd_books[11][14]; //max 10 books can be borrowed by a student,isbn nums are stored to find books
    //i have "1" element which is a sentinel element in brrwd_books. "1" is used in student_borrowed_books 

    struct Student * next;
}Student;

//helpers or code blocks that look better in a seperated function.
//users cant use those functions directly
void book_file_update(Book* ll_books);
void file_reader(Book **ll_books,Student **ll_students,int *book_count,int *stu_count);
void printbooks(Book* ll_books);
void sorter(Book **ll_books);
void addstudent(Student**ll_stu,char* name,int id ,char* isbn, int index);
void printstudents(Student* ll_students);

//the functions user uses directly
void student_borrowed_books(Student* ll_students,int stu_id,Book *ll_books);
void addbook(Book**ll_books, char* isbn, char* title, char* author, int publicationYear, int method, int reserv);
void deleteBook(Book **ll_books, char* isbn);
void updateBook(Book *ll_books, char* isbn, char* feature, char* value);
void searchBooks(Book *ll_books,int searchChoice, char* searchValue);
void borrowBook(Book* ll_books,char* isbn);
void returnBook(Book* ll_books,char* isbn);
void reverseBookList(Book**ll_books);
void filterAndSortBooks(Book*ll_books,int filterChoice, char* filter, int sortChoice);

#endif /* _UTIL_H_ */
