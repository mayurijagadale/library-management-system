#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// ---------- Book class (encapsulation: data is private) ----------
class Book {
private:
    int id;
    string title;
    string author;
    bool issued;

public:
    Book() : id(0), issued(false) {}
    Book(int id, string title, string author, bool issued = false)
        : id(id), title(title), author(author), issued(issued) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return issued; }

    void issueBook() { issued = true; }
    void returnBook() { issued = false; }

    void display() const {
        cout << id << " | " << title << " | " << author << " | "
             << (issued ? "Issued" : "Available") << endl;
    }
};

// ---------- Library class ----------
class Library {
private:
    vector<Book> books;
    const string fileName = "books.txt";

    int findIndexById(int id) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) return (int)i;
        }
        return -1;
    }

public:
    Library() { loadFromFile(); }

    // Save: one book per line -> id|title|author|issued
    void saveToFile() const {
        ofstream out(fileName);
        if (!out.is_open()) {
            cout << "Error: could not save data.\n";
            return;
        }
        for (const Book &b : books) {
            out << b.getId() << "|" << b.getTitle() << "|"
                << b.getAuthor() << "|" << b.isIssued() << "\n";
        }
    }

    // Load: runs when program starts; if file is missing, start empty
    void loadFromFile() {
        ifstream in(fileName);
        if (!in.is_open()) return;
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string idStr, title, author, issuedStr;
            getline(ss, idStr, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issuedStr, '|');
            if (idStr.empty()) continue;
            books.push_back(Book(stoi(idStr), title, author, issuedStr == "1"));
        }
    }

    void addBook() {
        int id;
        string title, author;
        cout << "Enter book ID: ";
        cin >> id;
        if (findIndexById(id) != -1) {
            cout << "A book with this ID already exists.\n";
            return;
        }
        cin.ignore();
        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        books.push_back(Book(id, title, author));
        saveToFile();
        cout << "Book added.\n";
    }

    void displayAll() const {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        cout << "ID | Title | Author | Status\n";
        for (const Book &b : books) b.display();
    }

    void searchBook() const {
        string key;
        cin.ignore();
        cout << "Enter title keyword: ";
        getline(cin, key);
        bool found = false;
        for (const Book &b : books) {
            if (b.getTitle().find(key) != string::npos) {
                b.display();
                found = true;
            }
        }
        if (!found) cout << "No matching book found.\n";
    }

    void issueBook() {
        int id;
        cout << "Enter book ID to issue: ";
        cin >> id;
        int i = findIndexById(id);
        if (i == -1) cout << "Book not found.\n";
        else if (books[i].isIssued()) cout << "Book is already issued.\n";
        else {
            books[i].issueBook();
            saveToFile();
            cout << "Book issued.\n";
        }
    }

    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        int i = findIndexById(id);
        if (i == -1) cout << "Book not found.\n";
        else if (!books[i].isIssued()) cout << "This book was not issued.\n";
        else {
            books[i].returnBook();
            saveToFile();
            cout << "Book returned.\n";
        }
    }
};

int main() {
    Library lib;
    int choice;
    do {
        cout << "\n===== Library Management System =====\n"
             << "1. Add Book\n2. Display All Books\n3. Search Book\n"
             << "4. Issue Book\n5. Return Book\n6. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }
        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayAll(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.issueBook(); break;
            case 5: lib.returnBook(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}
