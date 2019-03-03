#include <string>
#include <iostream>
#include <vector>

#include <time.h>

#include "paper_book.h"

using std::string;
using std::vector;
using std::cout;

void paper_book::estimate(int mark) {
  if (mark >= 0 && mark < 101) {
    rating = mark;
  }
}

bool paper_book::operator <(const paper_book &b) const {
  return (name < b.name);
}

bool paper_book::operator ==(const paper_book &b) const {
  return (name == b.name);
}

void paper_book::read(void) {
  time_t current_date = time(0);
  read_dates.push_back(current_date);
}

void paper_book::print(std::ostream& stream) const {
  stream << "Book's name: " << name << "\n";
  stream << "It's author(s): " << authors << "\n";
  stream << "Number of pages: " << pages_count << "\n";
  stream << "Number of times has been read: " << read_dates.size() << "\n";
  stream << "Rating: " << rating << "\n";
  stream << "Condition: " << condition << "\n";
}
