#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

using AdjList = vector<vector<pair<int, int>>>;

vector<int> dfs_bfs(int start, int goal, const AdjList& adjList) {
    int V = adjList.size();
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    stack<int> s;
    s.push(start);
    bool found = false;
    int lastVisited = start;

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        if (!visited[current]) {
            visited[current] = true;
            lastVisited = current;
            if (current == goal) {
                found = true;
                break;
            }
            for (int i = (int)adjList[current].size() - 1; i >= 0; i--) {
                int neighbor = adjList[current][i].first;
                if (!visited[neighbor]) {
                    parent[neighbor] = current;
                    s.push(neighbor);
                }
            }
        }
    }

    if (!found) {
        queue<int> q;
        q.push(lastVisited);
        visited[lastVisited] = true;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (current == goal) {
                found = true;
                break;
            }
            for (auto& edge : adjList[current]) {
                int neighbor = edge.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
    }

    vector<int> path;
    for (int at = goal; at != -1; at = parent[at]) {
        path.insert(path.begin(), at);
    }

    if (path.empty() || path[0] != start) {
        path.clear();
    }

    return path;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    AdjList adjList(V);

    cout << "Enter edges (from to weight):\n";
    for (int i = 0; i < E; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight});
    }

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    vector<int> path = dfs_bfs(start, goal, adjList);

    if (path.empty()) {
        cout << "No path found from " << start << " to " << goal << ".\n";
    } else {
        int totalCost = 0;
        for (size_t i = 0; i < path.size() - 1; i++) {
            int from = path[i];
            int to = path[i + 1];
            for (auto& edge : adjList[from]) {
                if (edge.first == to) {
                    totalCost += edge.second;
                    break;
                }
            }
        }
        cout << "DFS+BFS path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << "->";
        }
        cout << "\nTotal cost: " << totalCost << "\n";
    }

    return 0;
}
