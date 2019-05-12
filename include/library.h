#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "book.h"
#include <map>
#include <string>
#include <memory>
#include <utility>
#include <iostream>

using std::map;
using std::string;
using std::shared_ptr;
/**
 * @brief Library
 * Container (Threaded binary tree) for paper and digital books.
 */
class Library {
private:    
        map <string, shared_ptr<Book>> booksMap;

public:
        /**
         * @brief Show
         * Print the container
         * @param buf The buffer to print in
         * @param onlyHighestRating If true shows only books with highest rating parameter, 
         *        else all
         * @param thresholdRating Used when <onlyHighestRating> is false and determs the
         *        minimun rating for book to be printed
         * @return string which contains output to buf
         */
        std::string show(bool onlyHighestRating = false, int thresholdRating = 101) const;
        /**
         * @brief Get the Max Rating
         * Parse all books in the library and search maximum value for rating field of book
         * @return max rating met in the library
         */
        int getMaxRating(void) const;
        void insert(Book* book) {
            booksMap[book->getName()] = shared_ptr<Book>(book);
        }
        void remove(const std::string& bookName) {
            booksMap.erase(bookName);
        }
        /**
         * @brief Clean
         * Deallocate all nodes, container contains
         */
        void clean() {
            booksMap.clear();
        }
        /**
         * @brief Oldify
         * Change the condition parameter of paper book with name <bookName> 
         * on specified points <on>
         * @param bookName The name of the book
         * @param on Amount of points to pull off from book's condition
         */
        void oldify(const std::string& bookName, int on) {
            if (on > booksMap[bookName]->getCondition()) {
                booksMap.erase(bookName);
            } else booksMap[bookName]->oldify(on);
        }
        /**
         * @brief Get
         * The method to get book with specified name from container if it exists
         * @param bookName The name of the book to seek in container
         * @return const Book* The pointer to the desired book if it exists,
         *         otherwise nullptr
         */
        const Book* get(const std::string& bookName) const {
            auto it = booksMap.find(bookName);
            if (it != booksMap.end())
                return it->second.get();
            return nullptr;
        }

        ~Library() {
            clean();
        }
};

#endif