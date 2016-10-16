#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>
#include <list>
#include <set>

using namespace std;

typedef pair<int, int> edge;
#define GET_DIST(E) E.first
#define GET_LENGTH(E) E.second
typedef vector<vector<edge> > edge_list;
typedef pair<int, int> vertex_priority;
#define BIG_NUMBER 99999 // can't use int_max because floyd warshall requires adding

class vertex_comp {
  public:
    bool operator() (const vertex_priority &v1, const vertex_priority &v2) {
        return v1.second > v2.second;
    }
};

typedef priority_queue<vertex_priority, vector<vertex_priority>, vertex_comp> vertex_cost_queue;

class Undirected_Graph {
    int V;
    int **E;
  public:
    Undirected_Graph(int V);
    Undirected_Graph(int V, int **E);
    void add_edge(int from, int to, int len);
    int MST();
    int **MST_tree();
};

// directed graph
class Graph {
    int V; // number of vertices
    edge_list E;
  public:
    // graph.cpp
    Graph(int V);
    void add_edge(int from, int to, int len);
    vector<int> topological_sort();
    // dijkstra.cpp
    int dijkstras(int s, int t);
    list<int> dijkstras_path(int s, int t);
    // floyd_warshall.cpp
    int **floyd_warshall();
};

#endif // GRAPH_H
