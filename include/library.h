#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "book.h"
/**
 * @brief Library
 * Container (Threaded binary tree) for paper and digital books.
 */
class Library {
    private:
    /**
     * @brief Node
     * Element of container
     */
        class Node {
            public:
                Book* book; /**< Book */

                Node* left = nullptr; /**< Pointer to the left subtree */
                bool isLeftSewed = false; /**< True if this node has left stitching */

                Node* right = nullptr;  /**< Pointer to the right subtree */
                bool isRightSewed = false; /**< True if this node has right stitching */

                Node(Book* book, Node* left = nullptr, Node* right = nullptr): book(book), left(left), right(right) {}
                ~Node() {
                    delete book;
                }
        };
    
        Node* booksTree = nullptr; /**< Container itself */

        void showPretty(Node* booksTree, int curDepth) const;
        int getMaxDepth(Node* booksTree) const;
        /**
         * @brief Insert
         * Add element which is dynamically allocated to container
         * @param book The book to add
         * @param booksTree The container of books
         */
        void insert(Book *book, Node*& booksTree);
        /**
         * @brief Remove
         * Remove book with name <bookName> from container
         * @param bookName The name of the book to remove
         * @param booksTree The container
         * @return Node* The pointer to node, that takes place after deletion
         *               on the same position as removed node had
         */
        Node* remove(const std::string& bookName, Node* booksTree);
        /**
         * @brief Destroy
         * Delete specified Node pointed by <booksTree>
         * @param booksTree The pointer to Node to deallocate
         * @return Node* The pointer to Node after repairing the tree from deletion
         */
        Node* destroy(Node* booksTree);

    public:
        /**
         * @brief Show
         * Print the tree inorder
         * @param onlyHighestRating If true shows only books with highest rating parameter, 
         *        else all
         * @param thresholdRating Used when <onlyHighestRating> is false and determs the
         *        minimun rating for book to be printed
         */
        void show(bool onlyHighestRating = false, int thresholdRating = 101) const;
        void showPretty(void) const;
        /**
         * @brief Get the Max Rating
         * Parse all books in the library and search maximum value for rating field of book
         * @return max rating met in the library
         */
        int getMaxRating(void) const;
        /**
         * @brief Wrapper for private Insert method
         * This method hides the claim to specify tree in parameters 
         * and calls private Insert method
         * @param book The book to insert
         */
        void insert(Book* book) {
            insert(book, booksTree);
        }
        /**
         * @brief Wrapper for private Remove method
         * This method hides the claim to specify tree in parameters 
         * and calls private Insert method
         * @param bookName The name of the book to delete from container
         */
        void remove(const std::string& bookName) {
            remove(bookName, booksTree);
        }
        /**
         * @brief Clean
         * Deallocate all nodes, container contains
         */
        void clean();
        /**
         * @brief Oldify
         * Change the condition parameter of paper book with name <bookName> 
         * on specified points <on>
         * @param bookName The name of the book
         * @param on Amount of points to pull off from book's condition
         */
        void oldify(const std::string& bookName, int on);
        /**
         * @brief Get
         * The method to get book with specified name from container if it exists
         * @param bookName The name of the book to seek in container
         * @return const Book* The pointer to the desired book if it exists,
         *         otherwise nullptr
         */
        const Book* get(const std::string& bookName) const;

        ~Library() {
            clean();
        }
};

#endif