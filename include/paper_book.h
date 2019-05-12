#ifndef PAPER_BOOK_H_
#define PAPER_BOOK_H_

#include "book.h"

//! Paper book
/*! A class desribing the paper book */
class PaperBook: public Book
{
    int pagesCount; //!< number of pages in book
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
    PaperBook (const std::string& name,
                const std::string& authors,
                int pagesCount,
                const std::vector<time_t>& readDates = std::vector<time_t>(),
                int rating = 0,
                int condition = 10):
                  Book(name, authors, readDates, rating),
                  // TODO: There are possible mistakes
                  pagesCount(pagesCount),
                  condition(condition) {}

    PaperBook (const PaperBook& rhs): 
      Book(rhs.getName(), rhs.getAuthors(), rhs.getReadDates(), rhs.getRating()),
      pagesCount(rhs.pagesCount),
      condition(rhs.condition) {}
    
    PaperBook* clone() const { return new PaperBook(*this); }
    virtual ~PaperBook() {};
    Book::Size getSize(void) const;
    void oldify(int on) {
      if (this->condition >= on) condition -= on;
    }
    void print() const;
    //! Get condition of the book with 0...10 scale
    /*! \return value of condition */
    int getCondition(void) const
    {
      return condition;
    }
};

#endif
