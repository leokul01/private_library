#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "paper_book.h"

book::book_size paper_book::get_size(void) const {
  book::book_size pb_size = book::book_size();
  pb_size.size = pages_count;
  pb_size.unit = book::measure::sheets;

  return pb_size;
}

void paper_book::print(std::ostream& stream) const {
  stream << "Book's name: " << get_name() << "\n";
  stream << "It's author(s): " << get_authors() << "\n";
  stream << "Number of pages: " << pages_count << "\n";
  stream << "Number of times has been read: " << get_read_dates().size() << "\n";
  stream << "Rating: " << get_rating() << "\n";
  stream << "Condition: " << condition << "\n";
}
