#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <climit>

typedef struct graph_node {
    string value;
    vector<int> neighbors;
    vector<int> edge_weights;
} node;

/* dijkstra: generates a shortest distance from source to finish in a graph
 * containing the two nodes
 * TODO long description
 */
int dijkstra(vector<node> G, int s, int t){
    vector<int> distance(G.size(), INT_MAX);
    vector<bool> visited(G.size(), false);

    distance[s] = 0; // distance to starting node
    
    int min_dist = INT_MAX;

    while (!visited[t]) {
        for (int i = 0 ; i < G[s].neighbors.size() ; i++) {
            if (distance[G[s].neighbors[i]] > distance[s] + G[s].edge_weights[i]) {
                distance[G[s].neighbors[i]] = distance[s] + G[s].edge_weights[i];
            }
        }
        visited[s] = true;
        for (int i = 0 ; i < distance.size() ; i++) {
            if (!visited[i] && distance[i] < min_dist) {
                min_dist = distance[i];
                s = i;
            }
        }
        min_dist = INT_MAX;
    }

    return distance[t];
}

int main(int argc, char *argv[]) {
    // TODO write tests!
    return 0;
}
