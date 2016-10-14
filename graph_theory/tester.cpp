#include <iostream>

#include "graph.h"

int main(int argc, char *argv[]) {
    int V, E, from, to, len;
    V = 6;
    //cout << "Number of Vertices: ";
    //cin >> V;
    Graph G(V);
    //cout << "Number of Edges: ";
    //cin >> E;
    //cout << "Please Enter Edges (from to length)\n";
    //for (int i = 0 ; i < E ; i++) {
    //    cin >> from >> to >> len;
    //    G.add_edge(from, to, len);
    //}
    //cout << "Enter start and end for searching: ";
    //cin >> from >> to;
    G.add_edge(0, 1, 7);
    G.add_edge(1, 0, 7);
    G.add_edge(0, 5, 14);
    G.add_edge(5, 0, 14);
    G.add_edge(0, 2, 9);
    G.add_edge(2, 0, 9);
    G.add_edge(1, 2, 10);
    G.add_edge(2, 1, 10);
    G.add_edge(1, 3, 15);
    G.add_edge(3, 1, 15);
    G.add_edge(2, 5, 2);
    G.add_edge(5, 2, 2);
    G.add_edge(2, 3, 11);
    G.add_edge(3, 2, 11);
    G.add_edge(5, 4, 9);
    G.add_edge(4, 5, 9);
    G.add_edge(3, 4, 6);
    G.add_edge(4, 3, 6);
    from = 0; to = 4;
    cout << G.dijkstras(from, to);
    cout << '\n';
    list<int> path = G.dijkstras_path(from, to);
    for (list<int>::iterator it = path.begin() ; it != path.end() ; it++) {
        cout << *it << "->";
    }
    cout << "\n";

    int **D = G.floyd_warshall();
    cout << "  ";
    for (int i = 0 ; i < V ; i++) {
        cout << i << '\t';
    }
    cout << '\n';
    for (int i = 0 ; i < V ; i++) {
        cout << i << " ";
        for (int j = 0 ; j < V ; j++) {
            cout << D[i][j] << '\t';
        }
        cout << '\n';
    }

    V = 8;
    Graph DAG(V);

    DAG.add_edge(0, 1, 1);
    DAG.add_edge(0, 3, 1);
    DAG.add_edge(5, 1, 1);
    DAG.add_edge(2, 3, 1);
    DAG.add_edge(2, 6, 1);
    DAG.add_edge(1, 4, 1);
    DAG.add_edge(1, 7, 1);
    DAG.add_edge(1, 6, 1);
    DAG.add_edge(3, 7, 1);

    vector<int> sorted_v = DAG.topological_sort();

    for (int i = 0 ; i < sorted_v.size() ; i++) {
        cout << sorted_v[i] << ", ";
    }
    cout << '\n';
    return 0;
}
