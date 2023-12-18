// library.h

#ifndef LIBRARY_H  // Include guard to prevent multiple inclusion
#define LIBRARY_H

// Maximum number of books and maximum length for book title
#define MAX_BOOKS 1024
#define MAX_TITLE_LEN 100

// Struct definition for a Book
typedef struct 
{
    char title[MAX_TITLE_LEN];
    long int isbn;   
} Book;

// Struct definition for a Library
typedef struct
{
    Book books[MAX_BOOKS];
    int b_count; 
} Library;

// Function prototypes
void initLibrary(Library *lib);
void addBook(Library *lib, const char *title, long int isbn);
void displayAllbooks(const Library *lib);
void deleteBook(Library *lib, long int isbn);
void updateBook(Library *lib, long int isbn, const char* title);

#endif  // End of include guard
