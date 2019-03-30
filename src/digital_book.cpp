#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "digital_book.h"

Book::Size DigitalBook::getSize(void) const {
  Book::Size dbSize = Book::Size();
  dbSize.size = bytesCount;
  dbSize.unit = Book::Measure::bytes;

  return dbSize;
}

void DigitalBook::print(std::ostream& stream) const {
  stream << "Book's name: " << getName() << "\n";
  stream << "It's author(s): " << getAuthors() << "\n";
  stream << "Number of bytes: " << bytesCount << "\n";
  stream << "Number of times has been read: " << getReadDates().size() << "\n";
  stream << "Rating: " << getRating() << "\n";
}
