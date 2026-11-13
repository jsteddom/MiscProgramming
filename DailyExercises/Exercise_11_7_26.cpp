#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <limits>
#include <utility>
#include <optional>
#include <algorithm>


struct Book {
    std::string title;
    bool isChecked;
};
bool operator==(const Book& a, const Book& b) {
    return a.title == b.title && a.isChecked == b.isChecked;
}

struct Member {
    std::string name;
    std::vector<Book> booksChecked {};
};



class Library {
private:
    std::unordered_map<std::string, Book> books {};
public:
    void addBook(std::string& bookTitle);
    void checkoutBook(std::string& bookTitle, Member& memb);
    void returnBook(std::string& bookTitle, Member& memb);
    void displayAvailableBooks() const;
    void displayMemberBooks(Member& memb) const;
    bool checkBookExists(std::string& bookTitle);
    std::optional<Book> returnBookTitle(std::string& bookTitle, Member& memb);
};
std::optional<Book> Library::returnBookTitle(std::string& bookTitle, Member& memb) {
    for (auto& book : memb.booksChecked) {
        if (book.title == bookTitle) {
            return book;
        }
    }
    return std::nullopt;
}

bool Library::checkBookExists(std::string& bookTitle) {
    auto checkTitle {books.find(bookTitle)};
    if (checkTitle != books.end()) {
        return true;
    } else {
        return false;
    }
}

void Library::addBook(std::string& bookTitle) {
    auto doesBookExist {checkBookExists(bookTitle)};
    if (!doesBookExist) {
        books.insert({bookTitle, {bookTitle, false}});
        std::cout << bookTitle << " has been added to the library.\n";
    } else {
        std::cout << bookTitle << " is already in the library!\n";
    }
}
void Library::checkoutBook(std::string& bookTitle, Member& memb) {
    auto doesBookExist {checkBookExists(bookTitle)};
    if (doesBookExist) {
        auto isCheckedOut {books[bookTitle].isChecked};
        if (isCheckedOut) {
            std::cout << "Book is not available.\n";
            return;
        } else if (memb.booksChecked.size() >= 3) {
            std::cout << "You have too many books checked out!\n";
            return;
        } else {
            books[bookTitle].isChecked = true;
            memb.booksChecked.push_back(books[bookTitle]);
            std::cout << "You have checked out " << bookTitle << "!\n";
            return;
        }
    } else {
        std::cout << "Book is not in the library!\n";
    }
}
void Library::returnBook(std::string& bookTitle, Member& memb) {
    auto doesBookExist {checkBookExists(bookTitle)};
    if (!doesBookExist) {
        std::cout << "Book does not exist!\n";
        return;
    } 
    auto userHasBook {returnBookTitle(bookTitle, memb)};
    if (!userHasBook.has_value()) {
        std::cout << "User does not have this book checked out";
        return;
    }
    auto find {std::find(memb.booksChecked.begin(), memb.booksChecked.end(), userHasBook.value())};
    memb.booksChecked.erase(find);
    books[bookTitle].isChecked = false;
    std::cout << "Book has been return!\n";
}

void Library::displayAvailableBooks() const {
    std::cout << "Available Books: ";
    for (const auto& book : books) {
        if (book.second.isChecked == false) {
            std::cout << book.first << " ";
        }
    }
    std::cout << "\n";
}
void Library::displayMemberBooks(Member& memb) const {
    std::cout << memb.name << " books checked out:\n";
    for (const auto& book : memb.booksChecked) {
        std::cout << "Title: " << book.title << "\n";
    }
    std::cout << "\n";
}


int main() {
    Library myLibrary {};
    Member membOne {"Me"};
    std::string bookOne {"Hunger Games"};
    myLibrary.addBook(bookOne);
    myLibrary.checkoutBook(bookOne, membOne);
    myLibrary.displayMemberBooks(membOne);
    myLibrary.displayAvailableBooks();
    myLibrary.returnBook(bookOne, membOne);
    myLibrary.displayAvailableBooks();
    return 0;
}

/*
Day 4: Library Checkout System (~45 min)

The scenario: You’re building a tiny console program for a library desk. Books can be added to the catalog, checked out by a member, and returned. The desk clerk needs to see what’s available and who has what.

What it should do

Add a book to the catalog by title.
Check out a book for a named member.
Return a book.
Show which books are available.
Show which books a given member currently has.

Rules

A book can’t be checked out if it’s already out, or if it isn’t in the catalog.
A member can hold at most 3 books at a time.
Returning a book that isn’t checked out should be handled gracefully.
The caller should be able to tell whether each operation succeeded.

Your job

Decide what classes or structs you need and what each one owns.
Decide the function signatures, including what’s const, what’s passed by reference, and what returns a bool versus a value.
Decide how to store things.
Write a main() that exercises every rule above, including the failure cases.

Constraints

Data members are private where it makes sense.
Compile with -Wall -Wextra -std=c++17 and fix every warning.
No lambdas, smart pointers, or anything beyond what you’ve covered.

Stretch goals

Make it interactive with a menu loop.
Add a due-date counter (“days remaining”) that decreases as the clerk advances a day.


*/