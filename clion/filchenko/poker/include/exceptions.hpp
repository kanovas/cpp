#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class invalid_access : public std::exception {
public:
    invalid_access() {}
    const char * what() const throw() { return "Invalid action";}
};

class too_much_players : public std::exception {
public:
    too_much_players() {}
    const char * what() const throw() { return "Too much players";}
};

class invalid_card_operation : public std::exception {
public:
    invalid_card_operation() {}
    const char * what() const throw() { return "Invalid card operation"; }
};

class invalid_card : public std::exception {
public:
    invalid_card() {}
    const char * what() const throw() { return "Invalid card"; }
};

#endif