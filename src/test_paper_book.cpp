#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include <time.h>

#include "paper_book.h"

using std::string;
using std::vector;
using std::cout;

void  test_paper_book(void)
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
  assert(b1.get_pages_count() == 314);
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
}

int   main(void)
{
  test_paper_book();
  return (0);
}
