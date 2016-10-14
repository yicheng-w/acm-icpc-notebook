#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>
#include <list>

using namespace std;

typedef pair<int, int> edge;
#define GET_DIST(E) E.first;
#define GET_LENGTH(E) E.second;
typedef vector<vector<edge> > edge_list;
typedef pair<int, int> vertex_priority;

class vertex_comp {
  public:
    bool operator() (const vertex_priority &v1, const vertex_priority &v2) {
        return v1.second > v2.second;
    }
};

typedef priority_queue<vertex_priority, vector<vertex_priority>, vertex_comp> dijkstra_queue;

class Graph {
    int V; // number of vertices
    edge_list E;
  public:
    Graph(int V);
    void add_edge(int from, int to, int len);
    int dijkstras(int s, int t);
    list<int> dijkstras_path(int s, int t);
};

#endif // GRAPH_H
