#ifndef PAPER_BOOK_H_
#define PAPER_BOOK_H_

//! Paper book
/*! A class desribing the paper book */
class paper_book
{
    std::string           name; //!< book's name
    std::string           authors; //!< name(s) of author(s)
    int                   pages_count; //!< number of pages in book
    std::vector<time_t>   read_dates; //!< array dates when book has been read
    int                   rating; //!< rating(0...100) of the book
    int                   condition; //!< condition(0...10) of the book

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
    paper_book(const std::string& name, const std::string& authors,
      int pages_count, const std::vector<time_t>& read_dates,
      int rating, int condition):
      name(name), authors(authors), pages_count(pages_count),
      read_dates(read_dates), rating(rating), condition(condition) {}
    //! Get name of the book
    /*! \return value of name */
    const std::string&          get_name(void) const
    {
      return (name);
    }
    //! Get authors of the book
    /*! \return value of authors */
    const std::string&          get_authors(void) const
    {
      return (authors);
    }
    //! Get number of pages
    /*! \return value of pages_count */
    int                         get_pages_count(void) const
    {
      return (pages_count);
    }
    //! Get dates when book has been read
    /*! \return value of read_dates */
    const std::vector<time_t>&  get_read_dates(void) const
    {
      return (read_dates);
    }
    //! Get rating of the book with 0...100 scale
    /*! \return value of rating */
    int                         get_rating(void) const
    {
      return (rating);
    }
    //! Get condition of the book with 0...10 scale
    /*! \return value of condition */
    int                         get_condition(void) const
    {
      return (condition);
    }
    //! Estimate the book
    /*! \param mark the mark of the book with range 0...100 */
    void                        estimate(int mark);
    //! Call when the book read once more
    void                        read(void);
    //! Print information about the book
    void                        print(std::ostream&) const;
    bool                        operator <(const paper_book &b) const;
    bool                        operator ==(const paper_book &b) const;
};

#endif
