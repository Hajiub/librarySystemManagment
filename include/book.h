#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Book {
    char *title;
    char *author;
    long int isbn;
    void (*printInfo)(struct Book *);
    struct Book *next;
} Book;

void printInfo(Book *book);
void InitBook(Book *book, const size_t title_size, const size_t author_size);
Book *CreateBook(const char *title, const char *author, const long int isbn);
void freeBook(Book *book);

#endif

#ifdef BOOK_IMPLEMENTATION

void printInfo(Book *book) {
    printf("Author: %s\nTitle: %s\nISBN: %ld\n", book->author, book->title, book->isbn);
}

void InitBook(Book *book, const size_t title_size, const size_t author_size) {
    book->title = (char *)malloc(title_size + 1);
    if (book->title == NULL)
        exit(EXIT_FAILURE);
    
    book->author = (char *)malloc(author_size + 1);
    if (book->author == NULL) {
        free(book->title);
        exit(EXIT_FAILURE);
    }
}

Book *CreateBook(const char *title, const char *author, const long int isbn) {
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

#endif
