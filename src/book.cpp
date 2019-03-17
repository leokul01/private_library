#include <string>
#include <vector>
#include <ctime>

#include "book.h"

void book::estimate(int mark) {
  if (mark >= 0 && mark < 101) {
    rating = mark;
  }
}

bool book::operator <(const book &b) const {
  return name < b.name;
}

bool book::operator ==(const book &b) const {
  return name == b.name;
}

void book::read(void) {
  time_t current_date = time(0);
  read_dates.push_back(current_date);
}
