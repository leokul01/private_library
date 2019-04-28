#include <iostream>
#include "library.h"
#include "book.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;

string Library::show(std::ostream& buf, bool onlyHighestRating, int thresholdRating) const {
    string result = "";
    for(auto it = booksMap.begin(); it != booksMap.end(); it++) {
        if ((onlyHighestRating == true && it->second->getRating() == 100) || 
        (onlyHighestRating == false && it->second->getRating() >= thresholdRating) ||
        (onlyHighestRating == false && thresholdRating == 101)) {
            result = result + it->second->getName() + " ";
        }
    }
    buf << result;
    return result;
}

int Library::getMaxRating(void) const {
    int maxRating = 0;

    for(auto it = booksMap.begin(); it != booksMap.end(); it++) {
        int curBookRating = it->second->getRating();
            if (curBookRating > maxRating)
                maxRating = curBookRating;
    }

    return maxRating;
}