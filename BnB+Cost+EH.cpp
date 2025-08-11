#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int vertex;
    int cost;
    int est; 
    vector<int> path;
    bool operator>(const Node &other) const {
        return (cost + est) > (other.cost + other.est);
    }
};

int n, m;
vector<vector<pair<int,int>>> graph;
vector<int> heuristic;

bool branchAndBoundHeuristic(int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic[start], {start}});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.vertex == goal) {
            cout << "Path: ";
            for (size_t i=0; i<current.path.size(); i++) {
                cout << current.path[i];
                if (i != current.path.size()-1) cout << " -> ";
            }
            cout << "\nCost: " << current.cost << "\n";
            return true;
        }

        for (auto &edge : graph[current.vertex]) {
            bool visited = false;
            for (int v : current.path) {
                if (v == edge.first) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                vector<int> newPath = current.path;
                newPath.push_back(edge.first);
                pq.push({edge.first, current.cost + edge.second, heuristic[edge.first], newPath});
            }
        }
    }
    return false;
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<pair<int,int>>());
    heuristic.assign(n, 0);
    cout << "Number of edges: ";
    cin >> m;

    for (int i=0; i<m; i++) {
        int u,v,c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    cout << "Enter heuristic values for each vertex:\n";
    for (int i=0; i<n; i++) {
        cout << "Heuristic for vertex " << i << ": ";
        cin >> heuristic[i];
    }

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    if (!branchAndBoundHeuristic(start, goal))
        cout << "No path found\n";
}
