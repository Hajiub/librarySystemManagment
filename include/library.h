#ifndef LIBRARY_H
#define LIBRARY_H

#include "./book.h"
typedef struct 
{
	Book *head;
}Lib;
#define MAXLEN 50
void initLibrary(Lib *lib);
void addBook(Lib *lib, const char *title, const char *author, const long int isbn);
void DisplayBooks(Lib lib);
void DisplayBookByIsbn(Lib lib, long int isbn);
void DeleteBook(Lib *lib, long int isbn);
void freeLibrary(Lib *lib);
void SaveToFile(char *file_name, Lib lib);
void LoadFromFile(char *file_name, Lib *lib);
#endif
