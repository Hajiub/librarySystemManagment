#define BOOK_IMPLEMENTATION
#include "book.h"

#define MAXLEN 100

typedef struct
{
	Book *head;
}Lib;

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
void Init(Lib *lib)
{
	lib->head = NULL;
}

void addBook(Lib *lib, const char *title, const char *author, const long int isbn)
{
    Book *new_book = CreateBook(title, author, isbn);
    new_book->next = lib->head;
    lib->head = new_book;
}

void DisplayBooks(Lib lib)
{
	Book *n = lib.head;
	while (n != NULL)
	{
		n->printInfo(n);
		n = n->next;
		
	}
}
void DisplayBookByIsbn(Lib lib, long int isbn)
{
	Book *book = SearchBook(lib, isbn);
	if (book == NULL)
	{
		printf("Error: 404\n");
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
	while (current)
	{
		fprintf(file,"%ld, %s, %s\n", current->isbn, current->title, current->author);
		current = current->next;
	}
	printf("You have saved your data succuessfully!\n");
	return;
}
void LoadFromFile(char *file_name, Lib *lib)
{
	FILE *file = openFile(file_name, "r");
	char line[MAXLEN];
	char *dele = ",";
	char *tokens[3];
	char *token;
	int i = 0;
	while (fgets(line, MAXLEN, file))
	{
		token = strtok(line, dele);
		while (token != NULL)
		{
		   tokens[i++] = token;
		   token = strtok(NULL, dele);
		}
		addBook(lib, tokens[0], tokens[1], atoi(tokens[2]));
		i = 0;
	}	

	fclose(file);
}
int main(int argc, char **argv)
{
    Lib lib;
    Init(&lib);
    LoadFromFile("data.txt", &lib);
    DisplayBooks(lib);
    freeLibrary(&lib);
    return 0;
}
