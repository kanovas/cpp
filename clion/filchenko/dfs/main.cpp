#include <iostream>
#include "dfs.hpp"

using namespace std;

int main() {
    Graph<int> graph;
    auto v1 = graph.addNode();
    auto v2 = graph.addNode();
    auto v3 = graph.addNode();
    auto v4 = graph.addNode();
    auto v5 = graph.addNode();
    graph[v1] = 1;
    graph[v2] = 2;
    graph[v3] = 3;
    graph[v4] = 4;
    graph[v5] = 5;

    graph.addEdge(v1, v2);
    graph.addEdge(v1, v3);
    graph.addEdge(v2, v4);
    graph.addEdge(v2, v5);
    //graph.loadFromFile("graph.in");

    graph.dfs([&graph](Graph<int>::NodeHandle const & n) {std::cout << "S" << graph[n] << " ";},
            [&graph](Graph<int>::NodeHandle const & n) {std::cout << "D" << graph[n] << " ";},
            [&graph](Graph<int>::NodeHandle const & n) {std::cout << "E" << graph[n] << " ";});
/*
    try {
        graph.loadFromFile("graph.in");
        graph.saveToFile("graph.out");
    }
    catch (std::exception e) {
        cout << e.what();
    }*/
    return 0;
}