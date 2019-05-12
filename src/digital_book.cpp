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

void DigitalBook::print() const {
  std::cout << "Book's name: " << getName() << "\n";
  std::cout << "It's author(s): " << getAuthors() << "\n";
  std::cout << "Number of bytes: " << bytesCount << "\n";
  std::cout << "Number of times has been read: " << getReadDates().size() << "\n";
  std::cout << "Rating: " << getRating() << "\n";
}
