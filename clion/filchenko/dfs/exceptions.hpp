#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class invalid_filename : public std::exception {
public:
    invalid_filename() {}
    const char * what() const throw() { return "Invalid filename";}
};

class invalid_format : public std::exception {
public:
    invalid_format() {}
    const char * what() const throw() { return "Invalid format";}
};

#endif