#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>

#include "src/paper_book.cpp"
#include "src/digital_book.cpp"
#include "src/book.cpp"
#include "src/library.cpp"

namespace py = pybind11;

class PyBook : public Book {
public:
    /* Inherit the constructors */
    using Book::Book;

    /* Trampoline (need one for each virtual function) */
    Book* clone() const override {
        PYBIND11_OVERLOAD_PURE(
            Book*,          /* Return type */
            Book,           /* Parent class */
            clone,          /* Name of function in C++ (must match Python name) */
                            /* Argument(s) */
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void,
            Book,
            print,
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size,
            Book,
            getSize,
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void,
            Book,
            oldify,
            on
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int,
            Book,
            getCondition,
      );
    }
};


class PyPaperBook : public PaperBook {
public:
    using PaperBook::PaperBook;

    PaperBook* clone() const override {
        PYBIND11_OVERLOAD_PURE(
            PaperBook*,
            PaperBook,
            clone,               
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void,
            PaperBook,
            print,    
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size,
            PaperBook,
            getSize, 
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void,
            PaperBook,
            oldify,
            on
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int,
            PaperBook,
            getCondition,
      );
    }
};


class PyDigitalBook : public DigitalBook {
public:
    using DigitalBook::DigitalBook;

    DigitalBook* clone() const override {
        PYBIND11_OVERLOAD_PURE(
            DigitalBook*,
            DigitalBook,
            clone,
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void,
            DigitalBook,
            print,
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size,
            DigitalBook,
            getSize,
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void,
            DigitalBook,
            oldify,
            on
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int,
            DigitalBook,
            getCondition,
      );
    }
};


PYBIND11_MODULE(private_library, m) {
    m.doc() = "Private library module built with pybind11";

    py::class_<Book, PyBook> book(m, "Book");
    book.def("clone", &Book::clone)
        .def("get_name", &Book::getName)
        .def("get_authors", &Book::getAuthors)
        .def("get_size", &Book::getSize)
        .def("get_read_dates", &Book::getReadDates)
        .def("get_rating", &Book::getRating)
        .def("estimate", &Book::estimate, py::arg("mark"))
        .def("get_condition", &Book::getCondition)
        .def("read", &Book::read)
        .def("print", &Book::print)
        .def("__eq__", &Book::operator==)
        .def("__lt__", &Book::operator<)
        .def("__gt__", &Book::operator>);

    
    py::enum_<Book::Measure>(book, "Measure")
        .value("sheets", Book::Measure::sheets)
        .value("bytes", Book::Measure::sheets)
        .export_values();


    py::class_<Book::Size>(m, "Size")
        .def_readwrite("size", &Book::Size::size)
        .def_readwrite("unit", &Book::Size::unit)
        .def("__repr__", &Book::Size::getReadableSize);

    py::class_<PaperBook, PyPaperBook>(m, "PaperBook", book)
        .def(py::init<const std::string&, const std::string&, int, const std::vector<time_t>&, int, int>());


    py::class_<DigitalBook, PyDigitalBook>(m, "DigitalBook", book)
        .def(py::init<const std::string&, const std::string&, int, const std::vector<time_t>&, int>());


    py::class_<Library> library(m, "Libary");
    library.def(py::init<>())
           .def("show", &Library::show, py::arg("onlyHighestRating") = false, py::arg("thresholdRating") = 101)
           .def("get_max_rating", &Library::getMaxRating)
           .def("insert", &Library::insert, py::arg("book"))
           .def("remove", &Library::remove, py::arg("book_name"))
           .def("clean", &Library::clean)
           .def("oldify", &Library::oldify, py::arg("book_name"), py::arg("on"))   
           .def("get", &Library::get, py::arg("book_name"));        
}