#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "paper_book.h"

Book::Size PaperBook::getSize(void) const {
  Book::Size pbSize = Book::Size();
  pbSize.size = pagesCount;
  pbSize.unit = Book::Measure::sheets;

  return pbSize;
}

void PaperBook::print() const {
  std::cout << "Book's name: " << getName() << "\n";
  std::cout << "It's author(s): " << getAuthors() << "\n";
  std::cout << "Number of pages: " << pagesCount << "\n";
  std::cout << "Number of times has been read: " << getReadDates().size() << "\n";
  std::cout << "Rating: " << getRating() << "\n";
  std::cout << "Condition: " << condition << "\n";
}
