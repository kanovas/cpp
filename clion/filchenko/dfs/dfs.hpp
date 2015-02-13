#ifndef DFS_HPP
#define DFS_HPP

#include <stack>
#include <functional>
#include <vector>
#include <fstream>
#include <iostream>
#include "exceptions.hpp"

using namespace std;

template<typename T>
class Graph {
public:
    typedef int NodeHandle;
    typedef std::pair<int, int> EdgeHandle;
    typedef std::function<void(NodeHandle const &)> NodeVisitor;
    typedef std::function<void(EdgeHandle const &)> EdgeVisitor;
    struct Node {
        T & operator=(const T & node);
        std::vector<NodeHandle> edges;
        T node;
    };

    Graph() = default;
    ~Graph() = default;
    void loadFromFile(std::string const & filename);
    void saveToFile(std::string const & filename);
    NodeHandle addNode();
    void addEdge(NodeHandle const & a, NodeHandle const & b);
    void forEachNode(std::function<void(NodeHandle const &)> const & visitor) const;
    size_t getNodesCount() const;
    void forEachEdge(NodeHandle const & source, EdgeVisitor const & visitor);
    NodeHandle move(NodeHandle const & origin, EdgeHandle const & edge);
    T & operator[](NodeHandle const & node);
    void dfs(NodeVisitor const & startNode, NodeVisitor const & endNode, NodeVisitor const & discoverNode);

private:
    std::vector<Node> g;
    int n = 0;
    int m = 0;
};

//load graph from file "filename" with format:
//n m
//m edges
template<typename T>
void Graph<T>::loadFromFile(std::string const &filename) {
    ifstream in;
    try {
        in.open(filename);
    }
    catch (...) {
        throw invalid_filename();
    }
    try {
        in >> this->n >> this->m;
        this->g = * new std::vector<Graph::Node>(n);
        T x, y;
        int x_handle, y_handle;
        int found_nodes = 0;
        for (int i = 0; i < this->m; i++) {
            in >> x >> y;
            x_handle = -1;
            for (int j = 0; j < found_nodes; j++) {
                if (g[j].node == x) {
                    x_handle = j;
                    continue;
                }
            }
            if (x_handle == -1) {
                g[found_nodes].node = x;
                x_handle = found_nodes;
                found_nodes++;
            }
            y_handle = -1;
            for (int j = 0; j < found_nodes; j++) {
                if (g[j].node == y) {
                    y_handle = j;
                    continue;
                }
            }
            if (y_handle == -1) {
                g[found_nodes].node = y;
                y_handle = found_nodes;
                found_nodes++;
            }
            g[x_handle].edges.push_back(y_handle);
        }
    }
    catch (...) {
        throw invalid_format();
    }
}

//saves graph to file "filename" in format:
//n m
//m edges
template<typename T>
void Graph<T>::saveToFile(std::string const &filename) {
    ofstream out;
    try {
        out.open(filename);
    }
    catch (...) {
        throw invalid_filename();
    }
    out << this->n << " " << this->m << endl;
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->g[i].edges.size(); j++) {
            out << g[i].node << " ";
            out << g[g[i].edges[j]].node;
            out << endl;
        }
    }
}

//dat is clear
template<typename T>
size_t Graph<T>::getNodesCount() const {
    return this->n;
}

//adds new node with no edges from it
template<typename T>
typename Graph<T>::NodeHandle Graph<T>::addNode() {
    g.push_back(* new Graph::Node());
    g[g.size() - 1].node = * new T();
    this->n++;
    return g.size() - 1;
}

//add edge between nodes a and b
template<typename T>
void Graph<T>::addEdge(NodeHandle const &a, NodeHandle const &b) {
    g[a].edges.push_back(b);
    this->m++;
}

//apply function visitor to each edge going from source node
template<typename T>
void Graph<T>::forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor) {
    for (int i = 0; i < n; i++) {
        if (g[i].node == source) {
            for (int j = 0; j < g[i].edges.size(); j++) {
                visitor(std::make_pair(i, j));
            }
        }
    }
}

//apply function visitor for each node
template<typename T>
void Graph<T>::forEachNode(NodeVisitor const &visitor) const {
    for (int i = 0; i < this->n; i++) {
        visitor(i);
    }
}

//move to the node by the edge
template<typename T>
typename Graph<T>::NodeHandle Graph<T>::move(NodeHandle const &origin, EdgeHandle const &edge) {
    return g[edge.first].edges[edge.second];
}

//return node of graph
template<typename T>
T & Graph<T>::operator[](NodeHandle const &node) {
    return g[node].node;
}

template<typename T>
T & Graph<T>::Node::operator=(const T &node) {
    this->node = node;
    return this->node;
}

//for every node apply functions startNode -> discoverNode -> look through all children -> endNode
template<typename T>
void Graph<T>::dfs(NodeVisitor const &startNode, NodeVisitor const &discoverNode, NodeVisitor const &endNode) {
    stack<std::pair<NodeHandle, NodeHandle>> s;
    std::vector<int> mark;
    mark.resize(this->n);
    s.push(std::make_pair(0, -1));
    while (!s.empty()) {
        NodeHandle v = s.top().first;
        NodeHandle parent = s.top().second;
        startNode(v);
        discoverNode(v);
        s.pop();
        bool first = true;
        for (int i = 0; i < g[v].edges.size(); i++) {
            if (mark[g[v].edges[i]] == 0) {
                s.push(std::make_pair(g[v].edges[i], -1));
                if (first) {
                    s.top().second = v;
                    first = false;
                }
                mark[g[v].edges[i]] = 1;
            }
        }
        if (first) {
            endNode(v);
        }

        if (parent != -1) {
            endNode(parent);
        }
    }
    /*stack<NodeHandle> s;
    std::vector<bool> mark(n) {};*/
}

#endif