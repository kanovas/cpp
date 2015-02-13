#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <bits/c++config.h>
#include <string>
#include "card.hpp"
#include "combination.hpp"
#include "../include/exceptions.hpp"

using namespace std;

const int cards_amount = 5;

struct player {
    player(string name = "Nikolay Filchenko");
    void show_hand(std::ostream & output, player & p);
    void add_card(std::vector<card> & deck, int num, player & p, combination & combinator);
    void exchange(std::vector<card> & deck, int num, player & p, combination & combinator);
    void refresh_highest(combination & combinator);
    void check(player & p);  //throws InvalidAccess
    std::string & get_name() { return name; };
    void set_name(string name) {this->name = name; };
    long long get_highest(player & p);
    int get_cash() {return this->cash; }
    void change_cash(int num, player & p);
    bool can_pay(int num) {return this->cash >= num; }
    bool left();
    void set_left(player & p);
private:
    string name;
    int cash = 9000;
    std::vector<card> hand;
    long long highest_combination;
    std::string combination_name = "none";
};

#endif
