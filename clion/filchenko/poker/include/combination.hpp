#ifndef COMBINATION_HPP
#define COMBINATION_HPP

#include "card.hpp"
#include <algorithm>

using namespace std;

struct combination {
    void shuffle_deck(std::vector<card> & deck);
    std::pair<long long, std::string> comb_refresh_highest(std::vector<card> & hand);
};

#endif
