#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>

#include "paper_book.h"
#include "digital_book.h"
#include "test.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void Test::paperBook(void)
{
  vector<time_t> times(1, time(0));

  PaperBook b1("Граф Монте-Кристо",
                "А. Дюма",
                314,
                times,
                88,
                6);
  assert(b1.getName() == "Граф Монте-Кристо");
  assert(b1.getAuthors() == "А. Дюма");
  assert(b1.getSize().size == 314);
  assert(b1.getSize().unit == Book::Measure::sheets);
  assert(b1.getReadDates() == times);
  assert(b1.getRating() == 88);
  assert(b1.getCondition() == 6);

  b1.estimate(94);
  assert(b1.getRating() == 94);

  b1.read();
  assert(b1.getReadDates().size() == 2);

  PaperBook b2("Мартин Иден",
                "Д. Лондон",
                277,
                times,
                95,
                9);

  assert(b1 < b2);
  assert(b1 == b1);

  PaperBook b3("Мартин Иден",
                "Д. Лондон",
                277);

  assert(b3.getReadDates().size() == 0);
  assert(b3.getRating() == 0);
  assert(b3.getCondition() == 10);

  b2.print(cout);
}

void Test::digitalBook() {
  vector<time_t> times;
  times.push_back(time(0));

  DigitalBook* db = new DigitalBook("Мы",
                                     "Е. Замятин",
                                     1534,
                                     times,
                                     95);
  assert(db->getSize().size == 1534);
  assert(db->getReadDates().size() == 1);
  assert(db->getSize().getReadableSize() == "1534 bytes");

  db->print(cout);
  delete db;
}

void Test::hierarchy() {
  vector<time_t> times(1, time(0));
  Book* container[5];

  container[0] = new PaperBook("Граф Монте-Кристо",
                                "А. Дюма",
                                314,
                                times,
                                88,
                                6);
  container[1] = new DigitalBook("Мы",
                                  "Е. Замятин",
                                  1534,
                                  times,
                                  95);
  cout << "*** Test virtual functions ***" << endl;
  cout << "Where should be print and size of paper_book" << endl;
  container[0]->print(cout);
  cout << endl << "Where should be print and size of digital book" << endl;
  container[1]->print(cout);

  delete container[0];
  delete container[1];
}
