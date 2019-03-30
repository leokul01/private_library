#ifndef BOOK_H_
#define BOOK_H_

#include <cmath>

//! Paper book
/*! A class desribing general features of any book */
class Book
{
    std::string name; //!< book's name
    std::string authors; //!< name(s) of author(s)
    std::vector<time_t> readDates; //!< array dates when book has been read
    int rating; //!< rating(0...100) of the book

  public:
    //! Measurements for size of the book
    enum Measure {
      sheets,
      bytes
    };
    //! Type for size of different kinds of books
    /*! Ex. digital[bytes] and paper[sheets count] */
    struct Size
    {
      int size;
      Measure unit;

      std::string getReadableSize(void) {
        std::string sizeStr = std::to_string(size);
        std::string unitStr = (unit == Measure::sheets) ? "sheets" : "bytes";
        std::string readableSize = sizeStr + " " + unitStr;

        return readableSize;
      }
    };
    //! A constructor of book
    /*!
      \param name string with book's name
      \param authors string with name(s) of authors(s)
      \param read_dates array of dates(double) when book has been read
      \param rating mark with range = 0...100
    */
    Book (const std::string& name,
          const std::string& authors,
          const std::vector<time_t>& readDates = std::vector<time_t>(),
          int rating = 0):
            name(name),
            authors(authors),
            readDates(readDates),
            rating(rating) {}
    //! Virtual destructor of the book
    virtual ~Book() {};
    //! Get name of the book
    /*! \return value of name */
    const std::string& getName(void) const
    {
      return name;
    }
    //! Get authors of the book
    /*! \return value of authors */
    const std::string& getAuthors(void) const
    {
      return authors;
    }
    //! Get size of the Book
    /*! \return size in appropriate format */
    virtual Size getSize(void) const = 0;
    //! Get dates when book has been read
    /*! \return value of read_dates */
    const std::vector<time_t>& getReadDates(void) const
    {
      return readDates;
    }
    //! Get rating of the book with 0...100 scale
    /*! \return value of rating */
    int getRating(void) const
    {
      return rating;
    }
    //! Estimate the book
    /*! \param mark the mark of the book with range 0...100 */
    void estimate(int mark);
    //! Call when the book read once more
    void read(void);
    //! Print information about the book
    virtual void print(std::ostream&) const = 0;
    bool operator <(const Book &b) const;
    bool operator ==(const Book &b) const;
};

#endif
