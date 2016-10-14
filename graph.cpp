#include "graph.h"

Graph::Graph(int V) {
    this->V = V;
    E.resize(this->V);
}

void Graph::add_edge(int from, int to, int len) {
    E[from].push_back(make_pair(to, len));
}
