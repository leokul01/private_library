#include <iostream>
#include "library.h"
#include "book.h"

void Library::oldify(const std::string& bookName, int on) {
    Node* booksTree = this->booksTree;

    while (booksTree != nullptr) {
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        while (booksTree->isRightSewed) {
            if (booksTree->book->getName() == bookName) {
                if (on > booksTree->book->getCondition()) {
                    booksTree = destroy(booksTree);
                } else booksTree->book->oldify(on);
                return ;
            }
            booksTree = booksTree->right;
        }
        if (booksTree->book->getName() == bookName) {
            if (on > booksTree->book->getCondition()) {
                booksTree = destroy(booksTree);
            } else booksTree->book->oldify(on);
            return ;
        }
        booksTree = booksTree->right;
    }
}

Book* Library::get(const std::string& bookName) const {
    Node* booksTree = this->booksTree;

    while (booksTree != nullptr) {
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        while (booksTree->isRightSewed) {
            if (booksTree->book->getName() == bookName) {
                return booksTree->book;
            }
            booksTree = booksTree->right;
        }
        if (booksTree->book->getName() == bookName) {
            return booksTree->book;
        }
        booksTree = booksTree->right;
    }
    return nullptr;
}

void Library::show(bool highestRating) const {
    Node* booksTree = this->booksTree;

    while (booksTree != nullptr) {
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        while (booksTree->isRightSewed) {
            if ((highestRating == true && booksTree->book->getRating() == 100) || highestRating == false) {
                std::cout << booksTree->book->getName() << " ";
            }
            booksTree = booksTree->right;
        }
        if ((highestRating == true && booksTree->book->getRating() == 100) || highestRating == false) {
            std::cout << booksTree->book->getName() << " ";
        }
        booksTree = booksTree->right;
    }
}

void Library::clean(void) {
    Node* booksTree = this->booksTree;
    Node* tmp;

    while (booksTree != nullptr) {
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        while (booksTree->isRightSewed) {
            tmp = booksTree->right;
            delete booksTree;
            booksTree = tmp;
        }
        tmp = booksTree->right;
        delete booksTree;
        booksTree = tmp;
    }
}

void Library::insert(Book* book, Node*& booksTree) {
    if (booksTree == nullptr) {
        booksTree = new Node(book);
    } else if (*(book) < *(booksTree->book)) {
        if (booksTree->left != nullptr && booksTree->isLeftSewed == false) {
            insert(book, booksTree->left);
        }
        else {
            Node* nodeToInsert = new Node(book);

            // Left sewing
            if (booksTree->isLeftSewed) {
                nodeToInsert->left = booksTree->left;
                nodeToInsert->isLeftSewed = true;
                booksTree->isLeftSewed = false;
            }
            
            booksTree->left = nodeToInsert;

            // Right sewing
            nodeToInsert->right = booksTree;
            nodeToInsert->isRightSewed = true;
        }
    } else if (*(book) > *(booksTree->book)) {
        if (booksTree->right != nullptr && booksTree->isRightSewed == false)
            insert(book, booksTree->right);
        else {
            Node* nodeToInsert = new Node(book);

            // Right sewing
            if (booksTree->isRightSewed) {
                nodeToInsert->right = booksTree->right;
                nodeToInsert->isRightSewed = true;
                booksTree->isRightSewed = false;
            }

            booksTree->right = nodeToInsert;

            // Left sewing
            nodeToInsert->left = booksTree;
            nodeToInsert->isLeftSewed = true;
        }
    }
}

Library::Node* Library::remove(const std::string& bookName, Node* booksTree) {
    if (booksTree == nullptr)
        return nullptr;

    if (booksTree->book->getName() < bookName) {
        booksTree->right = remove(bookName, booksTree->right);
        return booksTree;
    }
    else if (booksTree->book->getName() > bookName) {
        booksTree->left = remove(bookName, booksTree->left);
        return booksTree;
    }
    else return destroy(booksTree);
}

Library::Node* Library::destroy(Node* booksTree) {
    if (booksTree->isLeftSewed && booksTree->isRightSewed) {
        Node* left = booksTree->left;
        Node* right = booksTree->right;

        if (left->right == booksTree) {
            left->isRightSewed = true;

            delete booksTree;
            return right;
        } else {
            right->isLeftSewed = true;

            delete booksTree;
            return left;
        }
    } 
    else if ((booksTree->isRightSewed && (booksTree->left == nullptr)) || (booksTree->isLeftSewed && (booksTree->right == nullptr))) {
        delete booksTree;
        return nullptr;
    } else if (booksTree->left != nullptr && !(booksTree->isLeftSewed) && booksTree->isRightSewed) {
        Node* mostRight = booksTree->left;

        while(!(mostRight->isRightSewed))
            mostRight = mostRight->right;
        if (mostRight->isRightSewed)
            mostRight->right = booksTree->right;

        delete booksTree;
        return booksTree->left;
    } else if (booksTree->right != nullptr && !(booksTree->isRightSewed) && booksTree->isLeftSewed) {
        Node* mostLeft = booksTree->right;

        while(!(mostLeft->isLeftSewed))
            mostLeft = mostLeft->left;
        if (mostLeft->isLeftSewed)
            mostLeft->left = booksTree->left;

        delete booksTree;
        return booksTree->right;
    } else {
        Node* mostRightPredecessor = booksTree->left;        
        Node* mostRight = booksTree->left;
        while (!(mostRight->isRightSewed)) {
            mostRightPredecessor = mostRight;
            mostRight = mostRight->right;
        }

        delete booksTree->book;
        booksTree->book = mostRight->book->clone();

        if (mostRightPredecessor == mostRight) 
            booksTree->left = destroy(mostRight);
        else
            mostRightPredecessor->right = destroy(mostRight);

        return booksTree;
    }
}