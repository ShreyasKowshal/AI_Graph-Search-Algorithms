#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int to;
    int cost;
};

int n, m;
vector<vector<Edge>> graph;

int findEdgeCost(int u, int v) {
    for (auto &e : graph[u]) {
        if (e.to == v) return e.cost;
    }
    return -1;
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<Edge>());
    cout << "Number of edges: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u,v,c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    cout << "Enter number of vertices in the path (including start and goal): ";
    int pathLen;
    cin >> pathLen;

    vector<int> path(pathLen);
    cout << "Enter the path vertices in order:\n";
    for (int i = 0; i < pathLen; i++) {
        cin >> path[i];
    }

    if (path.front() != start || path.back() != goal) {
        cout << "Path must start at " << start << " and end at " << goal << "\n";
        return 0;
    }

    int cost = 0;
    for (int i = 0; i + 1 < pathLen; i++) {
        int c = findEdgeCost(path[i], path[i+1]);
        if (c == -1) {
            cout << "Invalid edge between " << path[i] << " and " << path[i+1] << "\n";
            return 0;
        }
        cost += c;
    }

    cout << "Path accepted.\nPath: ";
    for (int i = 0; i < pathLen; i++) {
        cout << path[i];
        if (i != pathLen - 1) cout << " -> ";
    }
    cout << "\nCost: " << cost << "\n";
}
