#ifndef DIGITAL_BOOK_H_
#define DIGITAL_BOOK_H_

#include "book.h"

//! Digital book
/*! A class desribing the digital book */
class digital_book: public book
{
    int bytes_count; //!< bytes in book

  public:
    //! A constructor of digital book
    /*!
      \param name string with book's name
      \param authors string with name(s) of authors(s)
      \param bytes_count integer with number of bytes book has
      \param read_dates array of dates(double) when book has been read
      \param rating mark with range = 0...100
    */
    digital_book(const std::string& name,
                 const std::string& authors,
                 int bytes_count,
                 const std::vector<time_t>& read_dates = std::vector<time_t>(),
                 int rating = 0):
                   book(name, authors, read_dates, rating),
                   bytes_count(bytes_count) {}
    virtual ~digital_book() {};
    book::book_size get_size(void) const;
    void print(std::ostream&) const;
};

#endif
