#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>

#include "paper_book.h"
#include "digital_book.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void test_paper_book(void)
{
  vector<time_t> times(1, time(0));

  paper_book b1("Граф Монте-Кристо",
                "А. Дюма",
                314,
                times,
                88,
                6);
  assert(b1.get_name() == "Граф Монте-Кристо");
  assert(b1.get_authors() == "А. Дюма");
  assert(b1.get_size().size == 314);
  assert(b1.get_size().unit == book::measure::sheets);
  assert(b1.get_read_dates() == times);
  assert(b1.get_rating() == 88);
  assert(b1.get_condition() == 6);

  b1.estimate(94);
  assert(b1.get_rating() == 94);

  b1.read();
  assert(b1.get_read_dates().size() == 2);

  paper_book b2("Мартин Иден",
                "Д. Лондон",
                277,
                times,
                95,
                9);

  assert(b1 < b2);
  assert(b1 == b1);

  paper_book b3("Мартин Иден",
                "Д. Лондон",
                277);

  assert(b3.get_read_dates().size() == 0);
  assert(b3.get_rating() == 0);
  assert(b3.get_condition() == 10);

  b2.print(cout);
}

void test_digital_book()
{
  vector<time_t> times;
  times.push_back(time(0));

  digital_book* db = new digital_book("Мы",
                                     "Е. Замятин",
                                     1534,
                                     times,
                                     95);
  assert(db->get_size().size == 1534);
  assert(db->get_read_dates().size() == 1);
  assert(db->get_size().get_readable_size() == "1534 bytes");

  db->print(cout);
  delete db;
}

void test_hierarchy() {
  vector<time_t> times(1, time(0));
  book* container[5];

  container[0] = new paper_book("Граф Монте-Кристо",
                                "А. Дюма",
                                314,
                                times,
                                88,
                                6);
  container[1] = new digital_book("Мы",
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

int main(void)
{
  test_paper_book();
  test_digital_book();
  test_hierarchy();
  return 0;
}
