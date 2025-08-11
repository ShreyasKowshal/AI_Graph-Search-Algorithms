#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int cost;
};

void dijkstra(int start, int goal, const vector<vector<Edge>>& graph, vector<int>& parent, int& totalCost) {
    int V = graph.size();
    vector<int> dist(V, numeric_limits<int>::max());
    dist[start] = 0;

    using P = pair<int,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, start});
    parent.assign(V, -1);

    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cost > dist[u]) continue;
        if (u == goal) break;

        for (auto& edge : graph[u]) {
            int v = edge.to;
            int newCost = cost + edge.cost;
            if (newCost < dist[v]) {
                dist[v] = newCost;
                parent[v] = u;
                pq.push({newCost, v});
            }
        }
    }

    totalCost = dist[goal];
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<Edge>> graph(V);
    cout << "Enter edges (from to cost):\n";
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c}); // If graph is undirected; remove if directed
    }

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    vector<int> parent;
    int totalCost = 0;
    dijkstra(start, goal, graph, parent, totalCost);

    vector<int> path;
    for (int at = goal; at != -1; at = parent[at]) {
        path.insert(path.begin(), at);
    }

    if (path.empty() || path[0] != start || totalCost == numeric_limits<int>::max()) {
        cout << "No path found from " << start << " to " << goal << ".\n";
    } else {
        cout << "Oracle path (shortest path): ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size()-1) cout << "->";
        }
        cout << "\nTotal cost: " << totalCost << "\n";
    }

    return 0;
}
