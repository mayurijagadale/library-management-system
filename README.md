# Library Management System (C++)

A console-based Library Management System built in C++ using OOP, vectors and file handling.

## Features
- Add a book (duplicate IDs are rejected)
- Display all books
- Search books by title keyword
- Issue and return books
- Data is saved to `books.txt` and reloaded when the program starts

## Concepts used
- Classes and objects (`Book`, `Library`)
- Encapsulation (private data, public methods)
- `std::vector` for storing records
- File handling with `ifstream` / `ofstream`

## How to run
```
g++ -std=c++11 -o lms main.cpp
./lms
```
(On Windows: `lms.exe`)

## Future improvements
- Database (MySQL) instead of a text file
- Member management and due-date fines
- GUI
