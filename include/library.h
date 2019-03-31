#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "book.h"

class Library {
    public:
        class Node {
            public:
                Book* book;

                Node* left = nullptr;
                bool isLeftSewed = false;

                Node* right = nullptr;
                bool isRightSewed = false;

                Node(Book* book, Node* left = nullptr, Node* right = nullptr): book(book), left(left), right(right) {}
                ~Node() {
                    delete book;
                }
        };
        void show(bool highestRating = false) const;
        void insert(Book* book) {
            insert(book, booksTree);
        }
        Node* remove(const std::string& bookName) {
            return remove(bookName, booksTree);
        }
        Node* destroy(Node* booksTree);
        void clean();
        void oldify(const std::string& bookName, int on);
        Book* get(const std::string& bookName) const;
    private:
        Node* booksTree = nullptr;

        void insert(Book *book, Node*& booksTree);
        Node* remove(const std::string& bookName, Node* booksTree);
};

#endif