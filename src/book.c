#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/book.h"

void printInfo(Book *book) 
{
 	printf("%-20s%-15ld%-30s\n", book->author, book->isbn, book->title);
}

void InitBook(Book *book, const size_t title_size, const size_t author_size) 
{
    book->title = (char *)malloc(title_size + 1);
    if (book->title == NULL)
        exit(EXIT_FAILURE);
    
    book->author = (char *)malloc(author_size + 1);
    if (book->author == NULL) {
        free(book->title);
        exit(EXIT_FAILURE);
    }
}

Book *CreateBook(const char *title, const char *author, const long int isbn) 
{
    Book *book = (Book *)malloc(sizeof(Book));
    if (book == NULL)
        exit(EXIT_FAILURE);

    InitBook(book, strlen(title), strlen(author));
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->isbn = isbn;
    book->printInfo = printInfo;
    book->next = NULL;
    return book;
}

void freeBook(Book *book) {
    free(book->title);
    free(book->author);
    free(book);
}
