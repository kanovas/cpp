#include "../include/card.hpp"

card::card(std::pair<std::string, int> val, std::pair<std::string, int> suit) {
    this->value = val;
    this->suit = suit;
    this->color = !(suit.first == "Spade" || suit.first == "Club");
}

void card::print(std::ostream & output) {
    output << "   :: " <<  suit.first << " " << value.first << " ::   ";
}

void card::set_was(bool f) {
    this->was = f;
}

bool card::ask_was() {
    return this->was;
}

bool card::compare(card & b) {
    if (this->value.second == b.value.second) {
        return this->suit.second > b.suit.second;
    }
    return this->value.second > b.value.second;
}

std::pair<std::string, int> card::get_value() {
    return this->value;
}

std::pair<std::string, int> card::get_suit() {
    return this->suit;
}

bool card::is_a_little_higher_than(card &b) {
    if (this-> value.second == 2 && b.value.second == 14) {
        return true;
    }
    return this->value.second - 1 == b.value.second;
}
card & card::max(card &a, card &b) {
    if (a.compare(b)) {
        return a;
    }
    return b;
}

card & card::min(card &a, card &b) {
    if (a.compare(b)) {
        return b;
    }
    return a;
}