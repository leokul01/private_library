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
            Book*, /* Return type */
            Book,      /* Parent class */
            clone,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void, /* Return type */
            Book,      /* Parent class */
            print,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size, /* Return type */
            Book,      /* Parent class */
            getSize,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void, /* Return type */
            Book,      /* Parent class */
            oldify,          /* Name of function in C++ (must match Python name) */
            on      /* Argument(s) */
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int, /* Return type */
            Book,      /* Parent class */
            getCondition,          /* Name of function in C++ (must match Python name) */
            // on      /* Argument(s) */
      );
    }
};


class PyPaperBook : public PaperBook {
public:
    /* Inherit the constructors */
    using PaperBook::PaperBook;

    /* Trampoline (need one for each virtual function) */
    PaperBook* clone() const override {
        PYBIND11_OVERLOAD_PURE(
            PaperBook*, /* Return type */
            PaperBook,      /* Parent class */
            clone,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void, /* Return type */
            PaperBook,      /* Parent class */
            print,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size, /* Return type */
            PaperBook,      /* Parent class */
            getSize,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void, /* Return type */
            PaperBook,      /* Parent class */
            oldify,          /* Name of function in C++ (must match Python name) */
            on      /* Argument(s) */
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int, /* Return type */
            PaperBook,      /* Parent class */
            getCondition,          /* Name of function in C++ (must match Python name) */
            // on      /* Argument(s) */
      );
    }
};


class PyDigitalBook : public DigitalBook {
public:
    /* Inherit the constructors */
    using DigitalBook::DigitalBook;

    /* Trampoline (need one for each virtual function) */
    DigitalBook* clone() const override {
        PYBIND11_OVERLOAD_PURE(
            DigitalBook*, /* Return type */
            DigitalBook,      /* Parent class */
            clone,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void print() const override {
        PYBIND11_OVERLOAD_PURE(
            void, /* Return type */
            DigitalBook,      /* Parent class */
            print,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    Size getSize(void) const override {
      PYBIND11_OVERLOAD_PURE(
            Size, /* Return type */
            DigitalBook,      /* Parent class */
            getSize,          /* Name of function in C++ (must match Python name) */
            // n_times      /* Argument(s) */
        );
    }

    void oldify(int on) override {
      PYBIND11_OVERLOAD(
            void, /* Return type */
            DigitalBook,      /* Parent class */
            oldify,          /* Name of function in C++ (must match Python name) */
            on      /* Argument(s) */
      );
    }

    int getCondition(void) const override {
      PYBIND11_OVERLOAD(
            int, /* Return type */
            DigitalBook,      /* Parent class */
            getCondition,          /* Name of function in C++ (must match Python name) */
            // on      /* Argument(s) */
      );
    }
};


PYBIND11_MODULE(example, m) {
    m.doc() = "Private library module built with pybind11";

    py::class_<Book, PyBook> book(m, "Book");
    book.def("clone", &Book::clone)
        // .def(py::init<const std::string&, const std::string&, const std::vector<time_t>&, int>())
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

    py::class_<PaperBook, PyPaperBook> paper_book(m, "PaperBook", book);
    paper_book.def(py::init<const std::string&, const std::string&, int, const std::vector<time_t>&, int, int>());
            //   .def(py::init<const PaperBook&>())
            //   .def("clone", &PaperBook::clone)
            //   .def("get_size", &PaperBook::getSize)
            //   .def("oldify", &PaperBook::oldify
            //   .def("print", &PaperBook::print, py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>())
            //   .def("get_condition", &PaperBook::getCondition);   


    py::class_<DigitalBook, PyDigitalBook> digital_book(m, "DigitalBook", book);
    digital_book.def(py::init<const std::string&, const std::string&, int, const std::vector<time_t>&, int>());
                // .def("clone", &DigitalBook::clone)
                // .def("get_size", &DigitalBook::getSize)
                // .def("print", &DigitalBook::print);


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