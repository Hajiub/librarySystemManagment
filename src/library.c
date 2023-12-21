#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/book.h"
#include "../include/library.h"


static Book *SearchBook(Lib lib, long int isbn)
{
	Book *b = lib.head;
	while (b)
	{
		if (b->isbn == isbn)
			return b;
		b = b->next;
	}
	return NULL;

}
void initLibrary(Lib *lib)
{
	lib->head = NULL;
}

void addBook(Lib *lib, const char *title, const char *author, const long int isbn)
{
    // Todo: add book at the end
    Book *new_book = CreateBook(title, author, isbn);
    new_book->next = lib->head;
    lib->head = new_book;
}

void DisplayBooks(Lib lib) 
{
    Book *currentBook = lib.head;

    if (!currentBook) {
        printf("Library is empty. Please add books!\n");
        return;
    }

    printf("%-20s%-15s%-30s\n", "Author", "ISBN", "Title");
    while (currentBook != NULL) {
        currentBook->printInfo(currentBook);
        currentBook = currentBook->next;
    }
}

void DisplayBookByIsbn(Lib lib, long int isbn)
{
	Book *book = SearchBook(lib, isbn);
	if (book == NULL)
	{
		fprintf(stderr,"Book doesn't exist!\n");
		return;
	}
	book->printInfo(book);

}
void DeleteBook(Lib *lib, long int isbn)
{
    Book *prev = NULL;
    Book *current = lib->head;

    if (current != NULL && current->isbn == isbn)
    {
        lib->head = current->next;
        freeBook(current);
        return;
    }

    while (current != NULL && current->isbn != isbn)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Error: Book with ISBN %ld not found.\n", isbn);
        return;
    }

    prev->next = current->next;
    freeBook(current);
}

void freeLibrary(Lib *lib)
{
	Book *n, *temp;
	n = lib->head;
	while (n != NULL)
	{
		temp = n->next;
		freeBook(n);
		n = temp;
	}
}
static FILE *openFile(const char *file_name, char *mode)
{
	FILE *f = fopen(file_name, mode);
	if (f == NULL)
	{
		fprintf(stderr, "Couldn't open %s", file_name);
		return NULL;
	}	
	return f;
}
void SaveToFile(char *file_name, Lib lib)
{
	FILE *file = openFile(file_name, "w");
	Book *current = lib.head;
	while (current != NULL)
	{
		fprintf(file,"%s,%s,%ld\n", current->title, current->author, current->isbn);
		current = current->next;
	}
	fclose(file);
	return;
}
void LoadFromFile(char *file_name, Lib *lib)
{
    FILE *file = openFile(file_name, "r");
    char line[MAXLEN];
    char *dele = ",";
    char *tokens[3];
    char *token;
    int i;

    while (fgets(line, MAXLEN, file))
    {
        i = 0;
        token = strtok(line, dele);
        while (token != NULL)
        {
            tokens[i++] = token;
            token = strtok(NULL, dele);
        }

        // Check if the line has at least three tokens before processing
        if (i >= 3)
        {
            addBook(lib, tokens[0], tokens[1], atoi(tokens[2]));
        }
    }

    fclose(file);
}

