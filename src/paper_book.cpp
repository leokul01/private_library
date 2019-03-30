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

void PaperBook::print(std::ostream& stream) const {
  stream << "Book's name: " << getName() << "\n";
  stream << "It's author(s): " << getAuthors() << "\n";
  stream << "Number of pages: " << pagesCount << "\n";
  stream << "Number of times has been read: " << getReadDates().size() << "\n";
  stream << "Rating: " << getRating() << "\n";
  stream << "Condition: " << condition << "\n";
}
