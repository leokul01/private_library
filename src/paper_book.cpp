#include <string>
#include <iostream>
#include <vector>

#include <time.h>

#include "paper_book.h"

using std::string;
using std::vector;
using std::cout;

void paper_book::estimate(const int mark) {
  if (mark >= 0 && mark < 101) {
    this->rating = mark;
  }
}

bool paper_book::operator <(const paper_book &b) const {
  return (this->name < b.name);
}

bool paper_book::operator ==(const paper_book &b) const {
  return (this->name == b.name);
}

void paper_book::read(void) {
  time_t current_date = time(0);
  this->read_dates.push_back(current_date);
}

void paper_book::print(void) const {
  cout << "Book's name: " << this->name << "\n";
  cout << "It's author(s): " << this->authors << "\n";
  cout << "Number of pages: " << this->pages_count << "\n";
  cout << "Number of times has been read: " << this->read_dates.size() << "\n";
  cout << "Rating: " << this->rating << "\n";
  cout << "Condition: " << this->condition << "\n";
}
