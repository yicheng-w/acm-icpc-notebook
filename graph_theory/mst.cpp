#include "graph.cpp"

/* MST: returns the total weight of the minimum spanning tree
 */
int Undirected_Graph::MST(){
    int total_cost = 0;
    vertex_cost_queue costs;
    vertex_priority current;
    set<int> S;
    int prev_node[V];
    bool visited[V];

    // pick V[0] as our starting pt
    visited[0] = true;
    for (int i = 1 ; i < V ; i++) {
        if (E[i][0]) {
            costs.push(make_pair(i, E[i][0]));
        }
        else {
            costs.push(make_pair(i, INT_MAX));
        }
        S.insert(i);
        prev_node[i] = 0;
        visited[i] = false;
    }

    while (!S.empty()) {
        current = costs.top();
        costs.pop();
        S.erase(current.first);

        visited[current.first] = true;

        if (current.first < prev_node[current.first]) {
            total_cost += E[current.first][prev_node[current.first]];
        }
        else {
            total_cost += E[prev_node[current.first]][current.first];
           
        }

        for (int i = 0 ; i < V ; i++) {
            if (!visited[i]) {
                if (current.first > i) {
                    if (prev_node[i] > i) {
                        if (E[i][current.first] < E[i][prev_node[i]]) {
                            costs.push(make_pair(i, E[i][current.first]));
                            prev_node[i] = current.first;
                        }
                    }
                    else {
                        if (E[i][current.first] < E[prev_node[i]][i]) {
                            costs.push(make_pair(i, E[i][current.first]));
                            prev_node[i] = current.first;
                        }
                    }
                }
                else {
                    if (prev_node[i] > i) {
                        if (E[current.first][i] < E[i][prev_node[i]]) {
                            costs.push(make_pair(i, E[current.first][i]));
                            prev_node[i] = current.first;
                        }
                    }
                    else {
                        if (E[current.first][i] < E[prev_node[i]][i]) {
                            costs.push(make_pair(i, E[current.first][i]));
                            prev_node[i] = current.first;
                        }
                    }
                }
            }
        }
    }

    return total_cost;
}

/* **Undirected_Graph::MST: returns the minimum spanning tree as an adjacency
 * matrix
 */
int **Undirected_Graph::MST_tree(){
    int **MST = new int*[V];

    for (int i = 0 ; i < V ; i++) {
        MST[i] = new int[i]();
    }

    vertex_cost_queue costs;
    vertex_priority current;
    set<int> S;
    int prev_node[V];
    bool visited[V];

    // pick V[0] as our starting pt
    visited[0] = true;
    for (int i = 1 ; i < V ; i++) {
        if (E[i][0]) {
            costs.push(make_pair(i, E[i][0]));
        }
        else {
            costs.push(make_pair(i, INT_MAX));
        }
        S.insert(i);
        prev_node[i] = 0;
        visited[i] = false;
    }

    while (!S.empty()) {
        current = costs.top();
        costs.pop();
        S.erase(current.first);

        visited[current.first] = true;

        if (current.first < prev_node[current.first]) {
            MST[current.first][prev_node[current.first]] = E[current.first][prev_node[current.first]];
        }
        else {
            MST[prev_node[current.first]][current.first] = E[prev_node[current.first]][current.first];
           
        }

        for (int i = 0 ; i < V ; i++) {
            if (!visited[i]) {
                if (current.first > i) {
                    if (prev_node[i] > i) {
                        if (E[i][current.first] < E[i][prev_node[i]]) {
                            costs.push(make_pair(i, E[i][current.first]));
                            prev_node[i] = current.first;
                        }
                    }
                    else {
                        if (E[i][current.first] < E[prev_node[i]][i]) {
                            costs.push(make_pair(i, E[i][current.first]));
                            prev_node[i] = current.first;
                        }
                    }
                }
                else {
                    if (prev_node[i] > i) {
                        if (E[current.first][i] < E[i][prev_node[i]]) {
                            costs.push(make_pair(i, E[current.first][i]));
                            prev_node[i] = current.first;
                        }
                    }
                    else {
                        if (E[current.first][i] < E[prev_node[i]][i]) {
                            costs.push(make_pair(i, E[current.first][i]));
                            prev_node[i] = current.first;
                        }
                    }
                }
            }
        }
    }

    return MST;
}
