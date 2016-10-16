#include "graph.h"

Undirected_Graph::Undirected_Graph(int V) {
    this->V = V;

    this->E = new int*[V];

    for (int i = 0 ; i < V ; i++) {
        (this->E)[i] = new int[i]();
    }
}

Undirected_Graph::Undirected_Graph(int V, int **E) {
    this->V = V;
    this->E = E;
}

void Undirected_Graph::add_edge(int from, int to, int len) {
    if (from > to) {
        add_edge(to, from, len);
    }
    else {
        E[from][to] = len;
    }
}
