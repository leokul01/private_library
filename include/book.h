#ifndef BOOK_H_
#define BOOK_H_

#include <cmath>

//! Paper book
/*! A class desribing general features of any book */
class book
{
    std::string name; //!< book's name
    std::string authors; //!< name(s) of author(s)
    std::vector<time_t> read_dates; //!< array dates when book has been read
    int rating; //!< rating(0...100) of the book

  public:
    //! Measurements for size of the book
    typedef enum measure {
      sheets,
      bytes
    } measure;
    //! Type for size of different kinds of books
    /*! Ex. digital[byttes] and paper[pages count] */
    typedef struct book_size
    {
      int size;
      measure unit;

      std::string get_readable_size(void) {
        std::string size_str = std::to_string(size);
        std::string unit_str;

        if (unit == measure::sheets) {
          unit_str = "sheets";
        } else {
          unit_str = "bytes";
        }
        
        std::string readable_size = size_str + " " + unit_str;

        return readable_size;
      }
    } book_size;
    //! A constructor of book
    /*!
      \param name string with book's name
      \param authors string with name(s) of authors(s)
      \param read_dates array of dates(double) when book has been read
      \param rating mark with range = 0...100
    */
    book (const std::string& name,
          const std::string& authors,
          const std::vector<time_t>& read_dates = std::vector<time_t>(),
          int rating = 0):
            name(name),
            authors(authors),
            read_dates(read_dates),
            rating(rating) {}
    //! Virtual destructor of the book
    virtual ~book() {};
    //! Get name of the book
    /*! \return value of name */
    const std::string& get_name(void) const
    {
      return name;
    }
    //! Get authors of the book
    /*! \return value of authors */
    const std::string& get_authors(void) const
    {
      return authors;
    }
    //! Get size of the Book
    /*! \return size in appropriate format */
    virtual book_size get_size(void) const = 0;
    //! Get dates when book has been read
    /*! \return value of read_dates */
    const std::vector<time_t>& get_read_dates(void) const
    {
      return read_dates;
    }
    //! Get rating of the book with 0...100 scale
    /*! \return value of rating */
    int get_rating(void) const
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
    bool operator <(const book &b) const;
    bool operator ==(const book &b) const;
};

#endif
