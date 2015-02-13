#ifndef CARD_HPP
#define CARD_HPP

#include <bits/c++config.h>
#include "exceptions.hpp"
#include <iostream>
#include <vector>

using namespace std;

std::pair<std::string, int> const values [] = {
        std::make_pair("D2", 2),
        std::make_pair("D3", 3),
        std::make_pair("D4", 4),
        std::make_pair("D5", 5),
        std::make_pair("D6", 6),
        std::make_pair("D7", 7),
        std::make_pair("D8", 8),
        std::make_pair("D9", 9),
        std::make_pair("D10", 10),
        std::make_pair("KNIGHT", 11),
        std::make_pair("QUEEN", 12),
        std::make_pair("KING", 13),
        std::make_pair("ACE", 14)
};
std::pair<std::string, int> const suits [] = {
        std::make_pair("Spades", 1),    //piki tocheny
        std::make_pair("Diamonds", 2),  //bubbi.........
        std::make_pair("Clubs", 3),     //kresty-kupola
        std::make_pair("Hearts", 4)     //chervy-stervy
};

struct card {
    card(std::pair<std::string, int> val = values[0], std::pair<std::string, int> suit = suits[0]);
    void print(std::ostream & output);
    void set_was(bool f);
    bool ask_was();
    bool compare(card & b);
    std::pair<std::string, int> get_value();
    std::pair<std::string, int> get_suit();
    bool is_a_little_higher_than(card & b);
    card & max(card & a, card & b);
    card & min(card & a, card & b);

private:
    std::pair<std::string, int> value;
    std::pair<std::string, int> suit;
    bool color;  //true = red;
    bool was;
};

#endif
