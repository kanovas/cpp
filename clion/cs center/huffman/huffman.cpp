#include "huffman.hpp"
//coffee is 4 people, perversion is 4 u

static bool compare(std::pair<char, int> a, std::pair<char, int> b) {
    return a.second < b.second;
}

void zip(std::ifstream & input, std::ofstream & output) {
    std::vector<std::pair<char, int>> table;
    int was[256] = {};
    char c;
    while (!input.eof()) {
        input.read(&c, 1);
        was[c]++;
    }
    for (int i = 0; i < 256; i++) {
        if (was[i]) {
            table.push_back(std::make_pair((char)i, was[i]));
        }
    }
    std::sort(table.begin(), table.end(), compare);
    //ok now i have a sorted table of symbols
    int n = table.size();


}

void unzip(std::ifstream & input, std::ofstream & output) {

}