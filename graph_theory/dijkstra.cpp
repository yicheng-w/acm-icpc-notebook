#include "graph.h"

// Basic stuff about graphs
// In this package, graphs are represented in the following way, a Graph G(V, E)
// is composed of two parts:
//  1. A vector of content of vertices of size V
//  2. A form of representation of the edges, either Adjacency Matrix or
//     Adjacency List
// 
// Adjacency Matrix: a V x V 2D array of ints. 0 if the edge does not exist,
// and the length of it if it does exist (negative edge length allowed). FIXME
// Adjacency List: a vector of vectors, top level the size is V. At each
// element, there is another vector of pairs of ints <destination, length>
//
// actual uses for dijkstra:
//     find degrees of separation on fb
//     find where popular articles links back to actual research
//     wiki-racing!

int Graph::dijkstras(int s, int t) {
    int i;
    vector<bool> visited(V, false);
    vector<vertex_priority> vertex_set(V);
    vertex_priority current;
    int current_i, base_dist;

    for (i = 0 ; i < vertex_set.size() ; i++) {
        vertex_set[i] = make_pair(i, INT_MAX);
    }

    vertex_set[s].second = 0;

    vertex_cost_queue frontier;

    frontier.push(vertex_set[s]);

    while (!frontier.empty()) {
        current = frontier.top();
        frontier.pop();
        current_i = current.first;
        base_dist = current.second;

        if (visited[current_i]) {
            break; // this is the equivalent of empty frontier
        }

        if (current_i == t) {
            break; // we're done
        }
        
        for (int i = 0 ; i < E[current_i].size() ; i++) {
            if (base_dist + E[current_i][i].second < vertex_set[E[current_i][i].first].second) {
                vertex_set[E[current_i][i].first].second = base_dist + E[current_i][i].second;
                frontier.push(vertex_set[E[current_i][i].first]); // updated reference
            }
        }

        visited[current_i] = true;
    }
    return vertex_set[t].second;
}

list<int> Graph::dijkstras_path(int s, int t) {
    int i;
    vector<bool> visited(V, false);
    vector<vertex_priority> vertex_set(V);
    vector<int> prev_node(V, -1);
    vertex_priority current;
    int current_i, base_dist;

    for (i = 0 ; i < vertex_set.size() ; i++) {
        vertex_set[i] = make_pair(i, INT_MAX);
    }

    vertex_set[s].second = 0;

    vertex_cost_queue frontier;

    frontier.push(vertex_set[s]);

    while (!frontier.empty()) {
        current = frontier.top();
        frontier.pop();
        current_i = current.first;
        base_dist = current.second;

        if (visited[current_i]) {
            break; // this is the equivalent of empty frontier
        }

        if (current_i == t) {
            break; // we're done
        }
        
        for (int i = 0 ; i < E[current_i].size() ; i++) {
            if (base_dist + E[current_i][i].second < vertex_set[E[current_i][i].first].second) {
                vertex_set[E[current_i][i].first].second = base_dist + E[current_i][i].second;
                frontier.push(vertex_set[E[current_i][i].first]); // updated reference
                prev_node[E[current_i][i].first] = current_i;
            }
        }

        visited[current_i] = true;
    }
    
    // generating path, using linked list for generating efficiency, then copied
    // into array
    list<int> path;
    int prev = prev_node[t];

    path.push_front(t);

    while (prev != -1) {
        path.push_front(prev);
        prev = prev_node[prev];
    }

    return path;
}
