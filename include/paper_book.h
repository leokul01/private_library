#ifndef PAPER_BOOK_H_
#define PAPER_BOOK_H_

#include "book.h"

//! Paper book
/*! A class desribing the paper book */
class paper_book: public book
{
    int pages_count; //!< number of pages in book
    int condition; //!< condition(0...10) of the book

  public:
    //! A constructor of paper book
    /*!
      \param name string with book's name
      \param authors string with name(s) of authors(s)
      \param pages_count integer with number of pages book has
      \param read_dates array of dates(double) when book has been read
      \param rating mark with range = 0...100
      \param condition integer describing condition of the book with range = 0...10
    */
    paper_book (const std::string& name,
                const std::string& authors,
                int pages_count,
                const std::vector<time_t>& read_dates = std::vector<time_t>(),
                int rating = 0,
                int condition = 10):
                  book(name, authors, read_dates, rating),
                  pages_count(pages_count),
                  condition(condition) {}
    virtual ~paper_book() {};
    book::book_size get_size(void) const;
    void print(std::ostream&) const;
    //! Get condition of the book with 0...10 scale
    /*! \return value of condition */
    int get_condition(void) const
    {
      return condition;
    }
};

#endif
