#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/library.h"


#define MAXLINE 100
#define FILE_PATH "./data/data.txt"
Lib lib;

char cmd[MAXLINE];
char *tokens[MAXLINE];
enum Commands { HELP, EXIT, LIST, SEARCH, CREATE, DELETE};

char *commands[] = {"help", "exit", "list", "search", "create", "delete"};

void tokenize(char **tokensArray, char *buffer)
{
    int tk = 0;
    char *token;
    char *delem = " ";
    token = strtok(buffer, delem);
    while (token != NULL && tk < MAXLINE) {
        tokensArray[tk++] = token;
        token = strtok(NULL, delem);
    }
    tokensArray[tk] = NULL;
}

void displayHelp(char **tokensArray)
{
    if (tokensArray[1] != NULL) {
        if (strcmp(tokensArray[1], "exit") == 0) {
            printf("exit - Terminate the program\n");
        } else if (strcmp(tokensArray[1], "list") == 0) {
            printf("list - Display a list of available items\n");
        } else if (strcmp(tokensArray[1], "search") == 0) {
            printf("search 'ISBN' - Search for an item by ISBN\n");
        } else if (strcmp(tokensArray[1], "create") == 0) {
            printf("create - Create a new item with specified author, title, and ISBN\n");
        } else if (strcmp(tokensArray[1], "delete") == 0) {
            printf("delete 'ISBN' - Delete an item by ISBN\n");
        } else {
            printf("Unknown command. Type `help` for a list of available commands.\n");
        }
    } else {
        printf("Available commands:\n");
        printf("exit - Terminate the program\n");
        printf("list - Display a list of available items\n");
        printf("search 'ISBN' - Search for an item by ISBN\n");
        printf("create - Create a new item with specified author, title, and ISBN\n");
        printf("delete 'ISBN' - Delete an item by ISBN\n");
    }
}
char *removeTrailingSpaces(char *line)
{
    int length = strlen(line);
    
    for (int i = length - 1; i >= 0; i--) 
    {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') 
        {
            line[i] = '\0';
        } else {
            break;
        }
    }
    char *pt = line;
    while (isspace(*pt++));
    return --pt;
}

void create()
{
	char title[MAXLINE];
	char author[MAXLEN];
	char isbnStr[MAXLEN];

	printf("Title: ");
	fgets(title, MAXLINE, stdin);
        char *trimmedtitle = removeTrailingSpaces(title);

	printf("Author: ");
	fgets(author, MAXLEN, stdin);
	char *trimmedauthor = removeTrailingSpaces(author);

	printf("ISBN: ");
	fgets(isbnStr, MAXLEN, stdin);
	char *trimmedisbn = removeTrailingSpaces(isbnStr);
	if (*trimmedisbn && *trimmedtitle && *trimmedauthor)
	{
		addBook(&lib, trimmedtitle, trimmedauthor, strtol(trimmedisbn, NULL, 10));
		printf("Your book has been added!\n");
	}
	else
	{
	
		fprintf(stderr,"Error: Cannot add a book with an empty field!\n");
		return;
	}
}
void search()
{
	if (tokens[1])
	{
		long int isbn = strtol(tokens[1], NULL, 10);
       	        DisplayBookByIsbn(lib, isbn);
	}
	else
	{
		char *ser[] = {"help", "search"};
		displayHelp(ser);
	}
}
void delete(void)
{
	if (tokens[1])
	{
		long int isbn = strtol(tokens[1], NULL, 10);
		DeleteBook(&lib, isbn);
		return;
	}
	char *del[] = {"help", "delete"};
	displayHelp(del);
}
void processCommand(char *command) 
{
    enum Commands cmdIndex;
    int found = 0;

    for (cmdIndex = HELP; commands[cmdIndex]; cmdIndex++) 
    {
        if (strcmp(command, commands[cmdIndex]) == 0)
       	{
            found = 1;
            break;
        }
    }

    if (found) 
    {
        if (cmdIndex == EXIT)
	{
	    SaveToFile(FILE_PATH, lib);
	    freeLibrary(&lib);
            exit(0);
	}
        switch (cmdIndex) 
        {
            case HELP:
                displayHelp(tokens);
                break;
            case LIST:
                DisplayBooks(lib);
                break;
            case SEARCH:
		search();
		break;
            case CREATE:
                create();
                break;
            case DELETE:
                delete();
                break;
            default:
                printf("If some how you got this line! it means that earth is flat!\n");
                break;
        }
    }
    else
    {
        printf("%s: command not found\n", command);
        return;
    }

}

int getLine(char *buffer, int lim) {
    int i, c;
    printf("Lib> ");
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
        buffer[i] = c;
    buffer[i] = '\0';
    return i;
}

int main(void) 
{
    initLibrary(&lib);
    LoadFromFile(FILE_PATH, &lib);
    int len = 0;
    while (1) 
    {
        len = getLine(cmd, MAXLINE);
	if (len <= 0)
		continue;
        tokenize(tokens, cmd);
        processCommand(tokens[0]);
    }
    return 0;
}
