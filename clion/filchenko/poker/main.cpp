#include <iostream>
#include <vector>
#include <sstream>
#include "include/player.hpp"

using namespace std;

void init_deck(std::vector<card> & deck) {
    for (auto i : values) {
        for(auto j : suits) {
            deck.insert(deck.begin(), card(i, j));
        }
    }
}

void separator() {  //le decorations
    cout << "###########################################" << endl;
    cout << "###########################################" << endl;
    cout << "###########################################" << endl;
}

void round_of_betting(std::vector<player> & players, int * current_bet, int * bank, bool raise) {
    cout << "> Current bet is " << *current_bet << "$" << endl;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].left()) continue;
        cout << players[i].get_name() << ", your cash now: " << players[i].get_cash() << "$" << endl;
        if (raise) {
            std::cout << "Enter 1 for call, 2 for fold: ";
        }
        else {
            std::cout << "Enter 1 for call, 2 for fold, 3 for raise: ";
        }
        int cmd;
        cin >> cmd;
        if (cmd < 1 || cmd > 3) {
            throw invalid_access();
        }
        if (cmd == 1) {
            players[i].change_cash(-*current_bet, players[i]);
            *bank += *current_bet;
        }
        else if (cmd == 2) {
            cout << players[i].get_name() << " leaves the game!" << endl;
            players[i].set_left(players[i]);
        }
        else {
            raise = true;
            int z = 0;
            while (z <= *current_bet) {
                cout << "Enter how much you want to bet: ";
                cin >> z;
                cout << endl;
            }
            if (players[i].can_pay(z)) {
                players[i].change_cash(-z, players[i]);
                *bank += z;
            }
            else {
                cout << players[i].get_name() << " cannot pay and leaves the game!" << endl;
                players[i].set_left(players[i]);
                continue;
            }
            for (int j = 0; j < players.size(); j++) {
                if (players[j].left() || i == j) continue;
                cout << "> Current bet is " << z << "$" << endl;
                cout << players[j].get_name() << ", your cash now: " << players[j].get_cash() << "$" << endl;
                std::cout << "Enter 1 for call, 2 for fold: ";
                cin >> cmd;
                if (cmd < 1 || cmd > 2) {
                    throw invalid_access();
                }
                if (cmd == 1) {
                    if (players[j].can_pay(z - *current_bet)) {
                        players[j].change_cash(-z + *current_bet, players[j]);
                        *bank += z - *current_bet;
                    }
                    else {
                        cout << players[j].get_name() << " cannot pay and leaves the game!" << endl;
                        players[j].set_left(players[j]);
                    }
                }
                else if (cmd == 2) {
                    cout << players[j].get_name() << " leaves the game!" << endl;
                    players[j].set_left(players[j]);
                }
            }
            *current_bet = z;
        }
    }
}

int main() {
    int n;
    std::vector<card> deck;
    init_deck(deck);
    combination combinator;       //heh. g++ bug with static functions
    combinator.shuffle_deck(deck);
    std::cout << "Input number of players: ";
    std::cin >> n;
    if (n > 10) {
        throw too_much_players();
    }
    if (n < 1) {
        throw invalid_access();
    }
    std::vector<player> players(n);
    std::string tmp_name;
    for (int i = 0; i < n; i++) {
//        std::cout << i + 1 << " player, input your name: ";
//        std::cin >> tmp_name;
//        players[i].set_name(tmp_name);
        for (int j = 0; j < cards_amount; j++) {
            players[i].add_card(deck, j, players[i], combinator);
        }
        players[i].refresh_highest(combinator);
    }

    separator();
    cout << "################## START ##################" << endl;
    separator();

    for (int i = 0; i < players.size(); i++) {
        cout << players[i].get_name() << ", your hand: " << endl;
        players[i].show_hand(cout, players[i]);
    }
    separator();

    srand(time(NULL));
    int current_bet = rand() % 150;
    int bank = 0;
    cout << "ROUND OF BETTING #1" << endl;
    round_of_betting(players, &current_bet, &bank, false);
    separator();

    std::string num;
    std::getline(std::cin, num);
    cout << "ROUND OF EXCHANGE" << endl;
    for (int i = 0; i < n; i++) {
        if (players[i].left()) continue;
        players[i].show_hand(cout, players[i]);
        std::cout << players[i].get_name() << ", enter numbers of cards you want to exchange: ";
        std::getline(std::cin, num);
        std::stringstream stream(num);
        while (stream.good()) {
            int z;
            stream >> z;
            players[i].exchange(deck, z - 1, players[i], combinator);
        }
        players[i].refresh_highest(combinator);
        players[i].show_hand(cout, players[i]);
        if (n - i > 1) {
            separator();
        }
    }
    separator();

    cout << "ROUND OF BETTING #2" << endl;
    round_of_betting(players, &current_bet, &bank, false);
    separator();

    std::vector<player> winners;
    winners.push_back(players[0]);
    for (int i = 1; i < n; i++) {
        if (players[i].left()) continue;
        if (players[i].get_highest(players[i]) > winners[0].get_highest(winners[0])) {
            winners.clear();
            winners.push_back(players[i]);
        }
        else if (players[i].get_highest(players[i]) == winners[0].get_highest(winners[0])) {
            winners.push_back(players[i]);
        }
    }

    cout << "YOU WIN: " << endl;
    for (int i = 0; i < winners.size(); i++) {
        winners[i].change_cash(bank / winners.size(), winners[i]);
        cout << winners[i].get_name() << "   " << winners[i].get_cash() << "$" << endl;
        winners[i].show_hand(cout, winners[i]);
    }
    cout << endl << "Congratulations!" << endl;
    return 0;
}