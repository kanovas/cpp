#include "bigInt.h"

/* Private functions */
const big_integer ZERO = big_integer(0);
const big_integer ONE = big_integer(1);
void big_integer::__delete_zeroes()
{
    while (digits.size() > 1 && !digits.back())
        digits.pop_back();
    if (!digits.back())
        sign = 0;
}
void big_integer::__additional_code()
{
    for (size_t i = 0; i < digits.size(); ++i)
        digits[i] = ~digits[i];
    --(*this);
}

/* Constructors */
big_integer::big_integer()
{
    *this = ZERO;
}

big_integer::big_integer(big_integer const& other)
{
    sign = other.sign;
    digits = other.digits;
}

big_integer::big_integer(long a)
{
    digits.clear();
    if (!a) {
        sign = 0;
        digits.push_back(0);
        return;
    }
    sign = a > 0 ? 1 : (!a ? 0 : -1);
    if (a < 0)
        a = -a;
    digits.push_back(a);
}

big_integer::big_integer(std::string const& str)
{
    int start_index = 0;
    char need_sign = 0;
    if (str.size() > 0 && str[0] == '-')
        start_index = 1, need_sign = -1;
    if (start_index == (int)str.size())
        throw std::runtime_error("Invalid string in input");
    big_integer rs[10];
    for (int i = 0; i < 10; ++i)
        rs[i] = i;
    bool is_zero = true;
    *this = ZERO;
    for (size_t i = start_index; i < str.size(); ++i)
    {
        if (!isdigit(str[i]))
            throw std::runtime_error("Invalid string in input");
        if (str[i] != '0')
            is_zero = false;
        *this *= 10;
        *this += rs[str[i] - '0'];
    }
    if (!is_zero && !need_sign)
        need_sign = 1;
    if (is_zero)
        need_sign = 0;
    sign = need_sign;
}

/* Destructor */
big_integer::~big_integer()
{
}

big_integer& big_integer::operator = (big_integer const& other)
{
    sign = other.sign;
    digits = other.digits;
    return *this;
}

big_integer& big_integer::operator += (big_integer const& rhs)
{
    if (!sign)
    {
        (*this) = rhs;
        return *this;
    }
    if ((sign == 1 && rhs.sign >= 0) || (sign == -1 && rhs.sign <= 0))
    {
        size_t size = std::max(digits.size(), rhs.digits.size());
        int carry = 0;
        for (size_t i = 0; i < size || carry; ++i)
        {
            if (i == digits.size())
                digits.push_back(0);
            ll rdigit = (i < rhs.digits.size() ? rhs.digits[i] : 0);
            ll current = digits[i] + rdigit + carry;
            carry = current > (ll)base;
            if (carry)
                digits[i] = current - base - 1;
            else
                digits[i] = current;
        }
    }
    else
    {
        sign = rhs.sign;
        if ((*this) == rhs)
            return *this = ZERO;
        if (rhs.sign == -1)
            sign = 1, *this -= -rhs;
        else
            *this = rhs - (*this);
    }
    __delete_zeroes();
    return *this;
}

big_integer& big_integer::operator -= (big_integer const& rhs)
{
    if (!rhs.sign)
        return *this;
    if (!sign)
        return *this = -rhs;
    if (sign == 1 && rhs.sign == -1)
        return (*this) += (-rhs);
    if (sign == -1 && rhs.sign == 1)
    {
        *this = -(*this);
        *this += rhs;
        return *this = -(*this);
    }
    if ((*this) == rhs)
        return *this = ZERO;
    if (sign == 1)
    {
        if ((*this) < rhs)
            *this = -(rhs - (*this));
        else
        {
            int carry = 0;
            for (size_t i = 0; i < rhs.digits.size() || carry; ++i)
            {
                ll rdigit = (i < rhs.digits.size() ? rhs.digits[i] : 0);
                ll current = digits[i] - rdigit - carry;
                carry = current < 0;
                if (carry)
                    digits[i] = current + base + 1;
                else
                    digits[i] = current;
            }
            __delete_zeroes();
        }
    }
    else
    {
        if ((*this) > rhs)
            *this = (-rhs) + (*this);
        else
        {
            int carry = 0;
            for (size_t i = 0; i < rhs.digits.size() || carry; ++i)
            {
                ll rdigit = (i < rhs.digits.size() ? rhs.digits[i] : 0);
                ll current = digits[i] - rdigit - carry;
                carry = current < 0;
                if (carry)
                    digits[i] = current + base + 1;
                else
                    digits[i] = current;
            }
            __delete_zeroes();
        }
    }
    return *this;
}

big_integer& big_integer::operator *= (big_integer const& rhs)
{
    if (!sign || !rhs.sign)
        return *this = ZERO;
    sign = ((sign == -1) ^ (rhs.sign == -1)) ? -1 : 1;
    my_vector ans(digits.size() + rhs.digits.size());
    for (size_t i = 0; i < digits.size(); ++i)
    {
        uint carry = 0;
        for (size_t j = 0; j < rhs.digits.size() || carry; ++j)
        {
            uint rdigit = (j < rhs.digits.size() ? rhs.digits[j] : 0);
            unsigned long long current = ans[i + j] + 1ULL * digits[i] * rdigit + carry;
            ans[i + j] = current & (1ULL * base);
            carry = current >> blen;
        }
    }
    digits.resize(ans.size());
    for (size_t i = 0; i < ans.size(); ++i)
        digits[i] = ans[i];
    __delete_zeroes();
    return *this;
}

big_integer& big_integer::operator %= (big_integer const& rhs)
{
    if (!sign)
        return *this;

    *this -= (*this / rhs) * rhs;
    __delete_zeroes();
    return *this;
}

/* Unary operators -, + */
big_integer big_integer::operator - () const
{
    big_integer r = big_integer(*this);
    r.sign = -r.sign;
    return r;
}

big_integer big_integer::operator + () const
{
    return *this;
}

/* Operators +, -, * */
big_integer operator + (big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator - (big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer operator * (big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer operator % (big_integer a, big_integer const& b)
{
    return a %= b;
}

/* Big integer to string */

std::string to_string(big_integer const& a)
{
    if (!a.digits.size())
        throw std::runtime_error("Cannot output this number: no constructors were called");
    if (!a.sign)
        return "0";

    std::string number = "";
    char sign = a.sign;
    big_integer b = big_integer(a);
    big_integer divisor = 10;
    while (b.sign)
    {
        big_integer last_digit = b % divisor;
        number += char('0' + last_digit.digits[0]);
        b /= divisor;
    }
    if (sign == -1)
        number += '-';

    reverse(number.begin(), number.end());
    return number;
}

operator std::string() const
{
    return to_string(this);
}

std::ostream& operator << (std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}

std::istream& operator >> (std::istream& s, big_integer const& a)
{
    std::string ss;
    a = big_integer(s >> ss);
    return s;
}