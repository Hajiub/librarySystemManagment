#include <stdio.h>
#include "library.h"


void DisplayMenu(void)
{
	printf("=================================== Welcome To Abraham's Library ===================================\n");
	printf("1. Display all books\n2. Add A Book\n3. Delete A Book\n4. Update A book\n5. Quit\n");
}

void getitle(char *line, int lim)
{	
	int i, c;
	for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;
	line[i]	 = '\0';
	
}

int getUserChoice()
{

    int x;
    int res;

    do {
        printf("Please select a choice between 1 to 5: ");
        res = scanf(" %i", &x);
        while (getchar() != '\n');
    } while (res != 1 || x > 5 || x < 1);

    return x;
}

void run(void)
{
	char line[MAX_TITLE_LEN];
	int choice;
	Library lib;
	initLibrary(&lib);
	long int isbn;
	while (1)
	{
		DisplayMenu();
		choice = getUserChoice();
		if (choice == 5)
		{
			printf("Thanks for using Abraham's library\n");
			break;
		}
		switch (choice)
		{
			case 1:
				displayAllbooks(&lib);
				break;
			case 2:
				printf("Add a book\n");
				printf("Title: ");
				getitle(line, MAX_TITLE_LEN);
				printf("ISBN: ");
				scanf("%ld", &isbn);
				addBook(&lib, line, isbn);
				break;
			case 3:
				printf("ISBN: ");
				scanf("%ld", &isbn);
				deleteBook(&lib, isbn);
				break;
			case 4:
				printf("Update a book\n");
				printf("New title: ");
				getitle(line, MAX_TITLE_LEN);
				printf("ISBN: ");
				scanf("%ld", &isbn);
				updateBook(&lib, isbn, line);
				break;
			default:
				printf("Invalid choice\n");
				break;
		}
	}
}

int main(void)
{
	run();
}
