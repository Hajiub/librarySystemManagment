# Library Management System

## Overview

This Library Management System is designed to provide an efficient way to manage and organize your book collection. Unlike traditional systems using arrays, this version utilizes a linked list as its underlying data structure, offering greater flexibility for handling a potentially unlimited number of books.

## Features

- **Auto-Save Functionality:** The system automatically saves the books you add to a `data.txt` file, ensuring that your collection persists even after closing the application.

- **Linked List Implementation:** Instead of using an array, the system employs a linked list data structure. This choice allows for dynamic allocation of memory and efficient handling of a large number of books.

## Getting Started

To get started with the Library Management System, follow these steps:

1. Clone the repository to your local machine.

    ```bash
    git clone https://github.com/your-username/library-management-system.git
    ```

2. Compile and run the application.

    ```bash
    cd library-management-system
    make
    ./library_system
    ```

3. Add and manage your books using the provided commands.

## Commands

- **Add Book:** Add a new book to the system.

    ```bash
    create
    ```

- **Display Books:** View the list of books in the system.

    ```bash
    list
    ```

- **Save and Exit:** Save the current book collection to the `data.txt` file and exit the system.

    ```bash
    exit
    ```

