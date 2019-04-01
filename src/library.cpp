#include <iostream>
#include "library.h"
#include "book.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;

void Library::oldify(const std::string& bookName, int on) {
    Node* booksTree = this->booksTree;

    // Go through the tree
    while (booksTree != nullptr) {
        // Get down to the most left and low from current <booksTree>
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        // Go up along the sewing and seek the book with specified name <bookName>
        while (booksTree->isRightSewed) {
            if (booksTree->book->getName() == bookName) {
                // If this is the book we've searched for, check the book on viability
                // And destroy if it is too old (condition parameter under zero)
                // Otherwise change the condition parameter on <on> points
                if (on > booksTree->book->getCondition()) {
                    booksTree = destroy(booksTree);
                } else booksTree->book->oldify(on);
                return ;
            }
            booksTree = booksTree->right;
        }
        // Last element in previous cycle isn't checked, so I do it here
        if (booksTree->book->getName() == bookName) {
            if (on > booksTree->book->getCondition()) {
                booksTree = destroy(booksTree);
            } else booksTree->book->oldify(on);
            return ;
        }
        booksTree = booksTree->right;
    }
}

const Book* Library::get(const std::string& bookName) const {
    Node* booksTree = this->booksTree;

    // Go through the tree
    while (booksTree != nullptr) {
        // Get down to the most left and low from current <booksTree>
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        // Go up along the sewing and seek the book with specified name <bookName>
        while (booksTree->isRightSewed) {
            // If this is the book we've searched for, check the equality of names
            // And return with the book if it's name matches <bookName>
            if (booksTree->book->getName() == bookName) {
                return booksTree->book;
            }
            booksTree = booksTree->right;
        }
        // Last element in previous cycle isn't checked, so I do it here
        if (booksTree->book->getName() == bookName) {
            return booksTree->book;
        }
        booksTree = booksTree->right;
    }
    // If there is no matches with <bookName>
    return nullptr;
}

void Library::showPretty(Node* booksTree, int curDepth) const {
    if (booksTree == nullptr)
        return;
    if (!booksTree->isRightSewed)
        showPretty(booksTree->right, curDepth+1);
    for(int i=0;i<curDepth;++i)
        printf(" ");
        printf("%s\n", booksTree->book->getName().c_str());
    if (!booksTree->isLeftSewed)
        showPretty(booksTree->left, curDepth+1);
}

void Library::showPretty(void) const {
    showPretty(booksTree, 0);
}

int Library::getMaxDepth(Node* booksTree) const {
    if (booksTree == nullptr)  
        return 0;  
    else {  
        int leftDepth = (booksTree->isLeftSewed) ? 0 : getMaxDepth(booksTree->left);  
        int rightDepth = (booksTree->isRightSewed) ? 0 : getMaxDepth(booksTree->right);  
      
        if (leftDepth > rightDepth)  
            return(leftDepth + 1);  
        else return(rightDepth + 1);  
    }  
}

void Library::show(bool onlyHighestRating, int thresholdRating) const {
    Node* booksTree = this->booksTree;

    // Go through the tree
    while (booksTree != nullptr) {
        // Get down to the most left and low from current <booksTree>
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed))
            booksTree = booksTree->left;
        // Go up along the sewing
        while (booksTree->isRightSewed) {
            // If <highestRating> parameter is true, when check
            // that the book has highest rating. If it is so, print book's name out
            // If <highestRating> parameter is false, print without any checks
            if ((onlyHighestRating == true && booksTree->book->getRating() == 100) || 
                (onlyHighestRating == false && booksTree->book->getRating() >= thresholdRating) ||
                (onlyHighestRating == false && thresholdRating == 101)) 
            {
                std::cout << booksTree->book->getName() << " ";
            }
            booksTree = booksTree->right;
        }
        // Last element in previous cycle isn't checked, so I do it here
        if ((onlyHighestRating == true && booksTree->book->getRating() == 100) || 
            onlyHighestRating == false) {
            std::cout << booksTree->book->getName() << " ";
        }
        booksTree = booksTree->right;
    }
}

int Library::getMaxRating(void) const {
    Node* booksTree = this->booksTree;
    int maxRating = 0;

    // Go through the tree
    while (booksTree != nullptr) {
        // Get down to the most left and low from current <booksTree>
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        // Go up along the sewing and seek the book with specified name <bookName>
        while (booksTree->isRightSewed) {
            // If rating of this book is higher than <maxRating>,
            // put rating of this book to <maxRating>
            int curBookRating = booksTree->book->getRating();
            if (curBookRating > maxRating)
                maxRating = curBookRating;
            booksTree = booksTree->right;
        }
        // Last element in previous cycle isn't checked, so I do it here
        int curBookRating = booksTree->book->getRating();
        if (curBookRating > maxRating)
            maxRating = curBookRating;
        booksTree = booksTree->right;
    }

    return maxRating;
}


void Library::clean(void) {
    Node* booksTree = this->booksTree;
    // It's the temporary pointer to node, which is used when booksTree is deallocated
    Node* tmp;

    // Go through the tree
    while (booksTree != nullptr) {
        // Get down to the most left and low from current <booksTree>
        while (booksTree->left != nullptr && !(booksTree->isLeftSewed)) 
            booksTree = booksTree->left;
        // Go up along the sewing
        while (booksTree->isRightSewed) {
            // Save the pointer to the next node in the tree
            tmp = booksTree->right;
            // Deallocate booksTree
            delete booksTree;
            // Put next pointer to node to the booksTree and go further
            booksTree = tmp;
        }
        // Last element in previous cycle isn't deallocated, so I do it here
        tmp = booksTree->right;
        delete booksTree;
        booksTree = tmp;
    }
}

void Library::insert(Book* book, Node*& booksTree) {
    // If the root is nullptr, it is appropriate spot to place new node with
    // specified book
    if (booksTree == nullptr) {
        booksTree = new Node(book);   
    }
    // Otherwise get down, comparing the books (their names under the hood) 
    else if (*(book) < *(booksTree->book)) {
        // If there is a place to get deeper, go
        if (booksTree->left != nullptr && booksTree->isLeftSewed == false) {
            insert(book, booksTree->left);
        }
        // If not, place the node here
        else {
            Node* nodeToInsert = new Node(book);

            // Correct left sew for <booksTree>
            if (booksTree->isLeftSewed) {
                nodeToInsert->left = booksTree->left;
                nodeToInsert->isLeftSewed = true;
                booksTree->isLeftSewed = false;
            }
            
            // Place just allocated node to the left subtree of the <booksTree>
            booksTree->left = nodeToInsert;

            // Make right sew for <nodeToInsert>
            nodeToInsert->right = booksTree;
            nodeToInsert->isRightSewed = true;
        }
    } 
    else if (*(book) > *(booksTree->book)) {
        // If there is a place to get deeper, go
        if (booksTree->right != nullptr && booksTree->isRightSewed == false)
            insert(book, booksTree->right);
        // If not, place the node here
        else {
            Node* nodeToInsert = new Node(book);

            // Correct right sew for <booksTree>
            if (booksTree->isRightSewed) {
                nodeToInsert->right = booksTree->right;
                nodeToInsert->isRightSewed = true;
                booksTree->isRightSewed = false;
            }

            // Place just allocated node to the right subtree of the <booksTree>
            booksTree->right = nodeToInsert;

            // Make left sew for <nodeToInsert>
            nodeToInsert->left = booksTree;
            nodeToInsert->isLeftSewed = true;
        }
    }
}

Library::Node* Library::remove(const std::string& bookName, Node* booksTree) {
    // If root is nullptr, there is nothing to remove
    if (booksTree == nullptr)
        return nullptr;

    // Compare names and go deeper along the tree
    if (booksTree->book->getName() < bookName) {
        booksTree->right = remove(bookName, booksTree->right);
        return booksTree;
    }
    else if (booksTree->book->getName() > bookName) {
        booksTree->left = remove(bookName, booksTree->left);
        return booksTree;
    }
    //  If it is the book with specified <bookName>, destroy it
    else return destroy(booksTree);
}

Library::Node* Library::destroy(Node* booksTree) {
    // (Case 1) Check if <booksTree> is a pointer to list 
    if (booksTree->left == nullptr && booksTree->right == nullptr) {
        delete booksTree;
        return nullptr;
    }
    // (Case 2) Check if <booksTree> is a pointer to list with two sewings
    else if (booksTree->isLeftSewed && booksTree->isRightSewed) {
        // Get the pointed by sewings nodes 
        Node* left = booksTree->left;
        Node* right = booksTree->right;

        // if left sewing is a parent for <booksTree>
        if (left->right == booksTree) {
            // Add sewing for parent and delete <booksTree>
            left->isRightSewed = true;

            delete booksTree;
            return right;
        } 
        // if right sewing is a parent for <booksTree>
        else {
            // Add sewing for parent and delete <booksTree>
            right->isLeftSewed = true;

            delete booksTree;
            return left;
        }
    }
    // (Case 3) Check the case then one connection of the <booksTree> is nullptr and other is a sewing
    else if ((booksTree->isRightSewed && (booksTree->left == nullptr)) || 
                (booksTree->isLeftSewed && (booksTree->right == nullptr))) 
    {
        // In that case we can simply deallocate <bookTree> and return nullptr
        // Because parent won't have sewing after deletion
        delete booksTree;
        return nullptr;
    } 
    // (Case 4) Check the case then left connection is firm (not a sewing) and right is a sewing
    //                       *
    //                     |   -
    //                     *
    //                    | |
    //                    * *
    else if (booksTree->left != nullptr && !(booksTree->isLeftSewed) && booksTree->isRightSewed) {
        // Get left node and name it <mostRight>, because I want to put there the
        // Max node in the left subtree
        Node* mostRight = booksTree->left;

        // Go right while the connection is firm to get the Max node of left subtree 
        while(!(mostRight->isRightSewed))
            mostRight = mostRight->right;
        // If the <mostRight> has a right sewing, I redirect it according to
        // booksTree right sewing
        if (mostRight->isRightSewed)
            mostRight->right = booksTree->right;

        // Deallocate booksTree and return its left subtree on the same place
        // with repaired predecessors sewings
        Node* tmp = booksTree->left;
        delete booksTree;
        return tmp;
    } 
    // (Case 5) Check the case then right connection is firm (not a sewing) and left is a sewing
    //                       *
    //                     -   | 
    //                         *
    //                        | |
    //                        * *
    else if (booksTree->right != nullptr && !(booksTree->isRightSewed) && booksTree->isLeftSewed) {
        // Get right node and name it <mostLeft>, because I want to put there the
        // Min node in the right subtree
        Node* mostLeft = booksTree->right;

        // Go left while the connection is firm to get the Min node of right subtree 
        while(!(mostLeft->isLeftSewed))
            mostLeft = mostLeft->left;
        // If the <mostLeft> has a left sewing, I redirect it according to
        // booksTree left sewing
        if (mostLeft->isLeftSewed)
            mostLeft->left = booksTree->left;

        // Deallocate booksTree and return its right subtree on the same place
        // with repaired predecessors sewings
        Node* tmp = booksTree->right;
        delete booksTree;
        return tmp;
    } 
    // (Case 6) Check the case then both connections are firm (not sewings)
    //                       *
    //                    |     | 
    //                    *     *
    //                   | |   | |
    //                   * *   * *
    else {
        // Get left node and name it <mostRight>, because I want to put there the
        // Max node in the left subtree.
        // <mostRightPredecessor> trails the <mostRight> node
        Node* mostRightPredecessor = booksTree->left;        
        Node* mostRight = booksTree->left;

        // Go right while the connection is firm to get the Max node of left subtree
        // And Max predecessor
        while (!(mostRight->isRightSewed)) {
            mostRightPredecessor = mostRight;
            mostRight = mostRight->right;
        }

        // Delete the book, not a node, and put a copy of the mostRight book instead
        delete booksTree->book;
        booksTree->book = mostRight->book->clone();

        // <mostRightPredecessor> == <mostRight> only then left subtree doesn't have
        // Firm right predecessors 
        // So it's the (Case 1-4)
        if (mostRightPredecessor == mostRight) 
            booksTree->left = destroy(mostRight);
        // <mostRightPredecessor> != <mostRight> means that there is firm right subtree
        // So we delete the <mostRight> (Case 1-4) and redefine predecessor right connection
        else
            mostRightPredecessor->right = destroy(mostRight);

        return booksTree;
    }
}