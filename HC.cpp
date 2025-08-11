#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int cost;
};

int n, m;
vector<vector<Edge>> graph;
vector<int> heuristic;
vector<int> parent;

bool hillClimbing(int start, int goal) {
    int current = start;
    parent.assign(n, -1);

    while (current != goal) {
        int nextNode = -1;
        int minHeuristic = 1e9;

        for (auto &e : graph[current]) {
            if (heuristic[e.to] < minHeuristic) {
                minHeuristic = heuristic[e.to];
                nextNode = e.to;
            }
        }

        if (nextNode == -1 || heuristic[nextNode] >= heuristic[current]) {
            return false;
        }
        parent[nextNode] = current;
        current = nextNode;
    }
    return true;
}

void printPath(int goal) {
    vector<int> path;
    int cur = goal;
    int cost = 0;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i != (int)path.size() - 1) cout << " -> ";
    }
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int from = path[i];
        int to = path[i+1];
        for (auto &e : graph[from]) {
            if (e.to == to) {
                cost += e.cost;
                break;
            }
        }
    }
    cout << "\nCost: " << cost << "\n";
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<Edge>());
    heuristic.assign(n, 0);
    cout << "Number of edges: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u,v,c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    cout << "Enter heuristic values for each vertex:\n";
    for (int i = 0; i < n; i++) {
        cout << "Heuristic for vertex " << i << ": ";
        cin >> heuristic[i];
    }

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    bool found = hillClimbing(start, goal);
    if (found) printPath(goal);
    else cout << "No path found\n";
}
