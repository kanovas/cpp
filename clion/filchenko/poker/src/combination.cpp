#include "../include/combination.hpp"
#include "../include/player.hpp"

namespace {
    void sort(std::vector<card> & hand) {  //std::sort doesn't want 2 wrk i don't kno y
        for (int i = 0; i < hand.size(); i++) {
            for (int j = i; j < hand.size(); j++) {
                if (hand[i].compare(hand[j])) {
                    std::swap(hand[i], hand[j]);
                }
            }
        }
    }
}

void combination::shuffle_deck(std::vector<card> &deck) {
    for (int i = 0; i < deck.size(); i++) {
        deck[i].set_was(false);
    }
    for (int i = 0; i < deck.size(); i++) {
        srand(time(NULL));
        size_t j = rand() % (deck.size() - i) + i;
        std::swap(deck[i], deck[j]);
    }
}

std::pair<long long, std::string> combination::comb_refresh_highest(std::vector<card> & hand) {
    sort(hand);
    //ok here is my shitcode

    //counting balanced sum  //< 209
    int sum = 0;
    for (int i = 0; i < hand.size(); i++) {
        sum += hand[i].get_value().second * (i + 1);
    }
    //street flash?
    bool street_flash = true;
    for (int i = 1; i < hand.size() + 1; i++) { //+1 - because of aces
        street_flash = hand[(i - 1) % hand.size()].get_suit() == hand[i % hand.size()].get_suit() &&
                                            hand[i % hand.size()].is_a_little_higher_than(hand[(i - 1) % hand.size()]);
    }
    if (street_flash) {
        return std::make_pair((long long) 15 * 15 * 15 * 15 * 15 * 15 * 15 * 15 * 15 * hand[0].get_value().second, "street flash");      //15 = 14 + 1 :з
    }
    //square?
    bool square = false;
    int num;
    for (int i = 0; i < hand.size(); i++) {
        int hm = 0;
        for (int j = 0; j < hand.size(); j++) {
            if (hand[i].get_value() == hand[j].get_value()) hm++;
        }
        if (hm == 4) {
            square = true;
            num = i;
        }
    }
    if (square) {
        return std::make_pair((long long) 15 * 15 * 15 * 15 * 15 * 15 * 15 * hand[num].get_value().second + sum, "square");
    }
    //now let's count number of pairs & triples
    std::pair<int, int> pairs [2];
    int pairs_count = 0;
    for (int i = 0; i < hand.size(); i++) {
        pairs[pairs_count].first = i;
        pairs[pairs_count].second = -1;
        for (int j = 0; j < hand.size(); j++) {
            if (i != j && hand[i].get_value() == hand[j].get_value()) {
                pairs[pairs_count].second = j;
                pairs_count++;
            }
        }
    }
    if (pairs[0].second != -1 && pairs[1].second != -1) {
        pairs_count++;
    }
    std::vector<int> triple(3);
    int triples_count = 0;
    for (int i = 0; i < hand.size(); i++) {
        int count = 1;
        triple.push_back(i);
        for (int j = 0; j < hand.size(); j++) {
            if (i != j && hand[i].get_value() == hand[j].get_value()) {
                triple.push_back(j);
                count++;
            }
        }
        if (count == 3) {
            triples_count = 0;
            break;
        }
        triple.clear();
    }
    //full house?
    if (triples_count == 1 && pairs_count == 2) {
        return std::make_pair(15 * 15 * 15 * 15 * 15 * 15 * hand[triple[0]].get_value().second + sum, "full house");
    }
    //flash?
    bool flash = true;
    for (int i = 1; i < hand.size(); i++) {
        flash = hand[i - 1].get_suit() == hand[i].get_suit();
    }
    if (flash) {
        return std::make_pair(15 * 15 * 15 * 15 * 15 * 2 * hand[hand.size() - 1].get_value().second, "flash");
    }
    //street?
    bool street = false;
    for (int i = 1; i < hand.size() + 1; i++) { //+1 - because of aces
        street = hand[i % hand.size()].is_a_little_higher_than(hand[(i - 1) % hand.size()]);
    }
    if (street) {
        return std::make_pair(15 * 15 * 15 * 15 * 15 * hand[hand.size() - 1].get_value().second, "street");
    }
    //triple?
    if (triples_count == 1) {
        return std::make_pair(15 * 15 * 15 * 15 * hand[triple[0]].get_value().second + sum, "triple");
    }
    //two pairs?
    if (pairs_count == 2) {
        return std::make_pair(15 * 15 * 15 * hand[pairs[0].first].max(hand[pairs[0].first], hand[pairs[1].first]).get_value().second +
                15 * 15 * hand[pairs[0].first].min(hand[pairs[0].first], hand[pairs[1].first]).get_value().second + sum, "two pairs");
    }
    //one pair?
    if (pairs_count == 1) {
        return std::make_pair(15 * 15 * hand[pairs[0].first].get_value().second + sum, "pair");
    }
    return std::make_pair(15 * hand[hand.size() - 1].get_value().second + sum, "highest card");
}
