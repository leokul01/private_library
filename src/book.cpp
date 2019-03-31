#include <string>
#include <vector>
#include <ctime>

#include "book.h"

void Book::estimate(int mark) {
  if (mark >= 0 && mark < 101) {
    rating = mark;
  }
}

bool Book::operator <(const Book &b) const {
  return name < b.name;
}

bool Book::operator >(const Book &b) const {
  return name > b.name;
}

bool Book::operator ==(const Book &b) const {
  return name == b.name;
}

void Book::read(void) {
  readDates.push_back(time(0));
}
