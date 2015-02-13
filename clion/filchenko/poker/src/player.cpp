#include "../include/player.hpp"

player::player(string name) {
    this->name = name;
    this->hand = std::vector<card>(cards_amount);
}

void player::check(player & p) {
    if (&p != this) {
        throw invalid_access();
    }
}

void player::add_card(std::vector<card> & deck, int num, player & p, combination & combinator) {
    check(p);
    hand[num] = deck.front();
    deck.erase(deck.begin());
}

void player::show_hand(std::ostream & output, player & p) {
    check(p);
    for (auto & c : this->hand) {
        c.print(output);
    }
    output << endl;
//    output << "Highest combination: " << this->combination_name << endl;
}

void player::exchange(std::vector<card> & deck, int num, player & p, combination & combinator) {
    check(p);
    if (num < 0 || num >= cards_amount) {
        cout << "Invalid card" << endl;
        return;
    }
    hand[num].set_was(true);
    deck.push_back(hand[num]);
    add_card(deck, num, p, combinator);
}

void player::refresh_highest(combination & combinator) {
    std::pair<long long, std::string> tmp = combinator.comb_refresh_highest(this->hand);
    this->highest_combination = tmp.first;
    this->combination_name = tmp.second;
}

long long player::get_highest(player & p) {
    check(p);
    return this->highest_combination;
}

void player::change_cash(int num, player &p) {
    check(p);
    cash += num;
}

bool player::left() {
    return name == "java is the best language";
}

void player::set_left(player & p) {
    check(p);
    this->name = "java is the best language";
}
