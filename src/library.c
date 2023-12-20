#include <stdio.h>
#include <string.h>
#include "library.h"

static sortBooks(Library *lib);
static int searchBook(const Library *lib, const long int isbn)
{
	for (int i = 0; i < lib->b_count; i++)
		if (lib->books[i].isbn == isbn)
			return i;
	return -1;
} 
void displayAllbooks(const Library *lib)
{
	int i;
	if (lib->b_count > 0) 
	{
		printf("Index  Title    ISBN\n");
		for (i = 0; i < lib->b_count; i++)
			printf("%i   %s   %ld\n", i, lib->books[i].title, lib->books[i].isbn);
	
	}
	else
		printf("The library is Empty please add books!\n");
}
void initLibrary(Library *lib)
{
	lib->b_count = 0;
	return;
}
void addBook(Library *lib, const char *title, long int isbn)
{
	lib->books[lib->b_count].isbn = isbn;
	strcpy(lib->books[lib->b_count].title, title);
	lib->b_count++;
	return;
}

void deleteBook(Library *lib, long int isbn)
{
       /* Steps:
	1. Check if isbn does exit
        2. Get the index of the book 
	3. If index is in the end decrement the books count
	4. Else  shift the books 
	*/
	
	int index = -1; 
	for (int i = 0; i < lib->b_count; i++)	
		if (lib->books[i].isbn == isbn)
		{
			index = i;		
		}
	if (index >= 0)
	{
		if (index == lib->b_count - 1)			
			lib->b_count--;
		else
		{
			for (int j = index; j < lib->b_count - 1 ; j++)
				lib->books[j] = lib->books[j + 1];
			lib->b_count--;
		}
	}
	else
		printf("Error: book doesn't exist!\n");
}

void updateBook(Library *lib, long int isbn, const char* title)
{
	int index = searchBook(lib, isbn);
	if (index >= 0)
		strcpy(lib->books[index].title, title);
		printf("Book has been updated!\n");
		return;
	printf("Book with Isbn %ld isn't found\n", isbn);
	return;
}
