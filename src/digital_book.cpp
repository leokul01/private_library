#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "digital_book.h"

book::book_size digital_book::get_size(void) const {
  book::book_size db_size;
  db_size.bytes_count = bytes_count;

  return db_size;
}

void digital_book::print(std::ostream& stream) const {
  stream << "Book's name: " << get_name() << "\n";
  stream << "It's author(s): " << get_authors() << "\n";
  stream << "Number of bytes: " << bytes_count << "\n";
  stream << "Number of times has been read: " << get_read_dates().size() << "\n";
  stream << "Rating: " << get_rating() << "\n";
}
