#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include "paper_book.h"
#include "digital_book.h"
#include "library.h"
#include "test.h"

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

void Test::digitalBook(void) {
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

void Test::hierarchy(void) {
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

void Test::container(void) {
  vector<time_t> times(1, time(0));
  Library lib = Library();

  PaperBook* book1 = new PaperBook("e",
                        "Д. Лондон",
                        277);
  DigitalBook* book2 = new DigitalBook("c",
                          "Е. Замятин",
                          1534,
                          times,
                          74);
  PaperBook* book3 = new PaperBook("k",
                        "А. Дюма",
                        314,
                        times,
                        89,
                        6);
  PaperBook* book4 = new PaperBook("h",
                        "Д. Лондон",
                        277);
  PaperBook* book5 = new PaperBook("a",
                        "Д. Лондон",
                        277);
  PaperBook* book6 = new PaperBook("d",
                        "Д. Лондон",
                        277);
  PaperBook* book7 = new PaperBook("g",
                        "Д. Лондон",
                        277);
  PaperBook* book8 = new PaperBook("m",
                        "Д. Лондон",
                        277);
  PaperBook* book9 = new PaperBook("z",
                        "Д. Лондон",
                        277);

  Book* books[9] = {book1, book2, book3, book4, book5, book6, book7, book8, book9};

  for(int i = 0; i < 9; i++) lib.insert(books[i]);

  std::string str1 = lib.show();
  assert(str1 == "a c d e g h k m z ");

  assert(lib.getMaxRating() == 89);

  const Book* test_book = lib.get("c");
  assert(test_book->getName() == "c");
  assert(test_book->getAuthors() == "Е. Замятин");
  assert(test_book->getReadDates() == times);
  assert(test_book->getRating() == 74);


  PaperBook* test_book2 = new PaperBook("l",
                          "А. Морган",
                          321);
  lib.insert(test_book2);
  std::string str2 = lib.show();
  assert(str2 == "a c d e g h k l m z ");

  lib.remove("l");
  std::string str3 = lib.show();
  assert(str3 == "a c d e g h k m z ");

  lib.oldify("k", 4);
  const Book* test_book3 = lib.get("k");
  assert(test_book3->getCondition() == 2);
}