#ifndef BOOK_H
#define BOOK_H
#include <stddef.h>

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