CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c library.c
EXEC = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -rf $(EXEC)

