#ifndef DIGITAL_BOOK_H_
#define DIGITAL_BOOK_H_

#include "book.h"

//! Digital book
/*! A class desribing the digital book */
class DigitalBook: public Book
{
    int bytesCount; //!< bytes in book

  public:
    //! A constructor of digital book
    /*!
      \param name string with book's name
      \param authors string with name(s) of authors(s)
      \param bytes_count integer with number of bytes book has
      \param read_dates array of dates(double) when book has been read
      \param rating mark with range = 0...100
    */
    DigitalBook(const std::string& name,
                 const std::string& authors,
                 int bytesCount,
                 const std::vector<time_t>& readDates = std::vector<time_t>(),
                 int rating = 0):
                   Book(name, authors, readDates, rating),
                   bytesCount(bytesCount) {}
    virtual ~DigitalBook() {};
    Book::Size getSize(void) const;
    void print(std::ostream&) const;
};

#endif
