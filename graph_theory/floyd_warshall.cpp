#include "graph.h"

int **Graph::floyd_warshall() {
    int **dist = 0;
    dist = new int*[V];

    // initialization
    for (int i = 0 ; i < V ; i++) {
        dist[i] = new int[V];
        for (int j = 0 ; j < V ; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = BIG_NUMBER;
            }
        }
    }

    for (int i = 0 ; i < E.size() ; i++) {
        for (int j = 0 ; j < E[i].size() ; j++) {
            dist[i][E[i][j].first] = E[i][j].second;
        }
    }

    for (int k = 0 ; k < V ; k++) {
        for (int i = 0 ; i < V ; i++) {
            for (int j = 0 ; j < V ; j++) {
                dist[i][j] = (dist[i][j] < dist[i][k] + dist[k][j]) ? dist[i][j] : dist[i][k] + dist[k][j];
            }
        }
    }

    return dist;
}
