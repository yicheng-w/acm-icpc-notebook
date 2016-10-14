#include <iostream>

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

    dijkstra_queue frontier;

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

    dijkstra_queue frontier;

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
    return 0;
}
