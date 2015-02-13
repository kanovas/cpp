#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>


typedef long long ll;
typedef unsigned int uint;

struct big_integer {
    big_integer();
    big_integer(big_integer const& other);
    big_integer(long a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator = (big_integer const& other);

    big_integer& operator += (big_integer const& rhs);
    big_integer& operator -= (big_integer const& rhs);
    big_integer& operator *= (big_integer const& rhs);
    big_integer& operator %= (big_integer const& rhs);

    big_integer operator + () const;
    big_integer operator - () const;
    friend std::string to_string(big_integer const& a);
    operator std::string() const;

private:
    char sign;
    std::vector digits;
    void __delete_zeroes();
    void __additional_code();
    static const uint base = 4294967295U;
    static const int blen = 32;
};
big_integer operator + (big_integer a, big_integer const& b);
big_integer operator - (big_integer a, big_integer const& b);
big_integer operator * (big_integer a, big_integer const& b);
big_integer operator % (big_integer a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator << (std::ostream& s, big_integer const& a);
std::istream& operator >> (std::istream& s, big_integer const& a);


#endif