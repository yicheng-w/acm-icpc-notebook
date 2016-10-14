#include "graph.h"

Graph::Graph(int V) {
    this->V = V;
    E.resize(this->V);
}

void Graph::add_edge(int from, int to, int len) {
    E[from].push_back(make_pair(to, len));
}

/* topological_sort: returns a list of vertices sorted such that if
 * there exists an edge u->v, then u appears before v in the list
 *
 * XXX the graph must be a DAG
 */
vector<int> Graph::topological_sort(){
    vector<int> vertices;
    vector<int> degrees(V, 0);
    int current;

    for (int i = 0 ; i < V ; i++) {
        for (int j = 0 ; j < E[i].size() ; j++) {
            degrees[E[i][j].first]++;
        }
    }

    queue<int> q;

    for (int i = 0 ; i < V ; i++) {
        if (degrees[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        current = q.front();
        q.pop();
        vertices.push_back(current);

        for (int i = 0 ; i < E[current].size() ; i++) {
            if (--degrees[E[current][i].first] == 0) {
                q.push(E[current][i].first);
            }
        }
    }

    return vertices;
}
