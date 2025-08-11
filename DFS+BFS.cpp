#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

struct Edge {
    int to, cost;
    Edge(int t, int c = 1) : to(t), cost(c) {}
};

struct Graph {
    int V;
    vector<vector<Edge>> adj;
    Graph(int n) : V(n), adj(n) {}
    void addEdge(int u, int v, int cost = 1) { adj[u].emplace_back(v, cost); }
};

// Data structure to hold path information for BFS
struct PathInfo {
    vector<int> path;
    int total_cost;
};

// Recursive DFS to find a path
bool findPathDFS(
    Graph& g,
    int node,
    int goal,
    vector<bool>& visited,
    vector<int>& current_path,
    int& current_cost,
    PathInfo& result
) {
    visited[node] = true;
    current_path.push_back(node);

    if (node == goal) {
        result.path = current_path;
        result.total_cost = current_cost;
        return true;
    }

    for (auto& e : g.adj[node]) {
        if (!visited[e.to]) {
            current_cost += e.cost;
            if (findPathDFS(g, e.to, goal, visited, current_path, current_cost, result)) {
                return true;
            }
            current_cost -= e.cost;
        }
    }
    
    current_path.pop_back();
    return false;
}

// Wrapper for DFS pathfinding
PathInfo dfs(Graph& g, int start, int goal) {
    vector<bool> visited(g.V, false);
    vector<int> current_path;
    int current_cost = 0;
    PathInfo result = {{}, 0};
    findPathDFS(g, start, goal, visited, current_path, current_cost, result);
    return result;
}

// BFS to find a path
PathInfo bfs(Graph& g, int start, int goal) {
    queue<PathInfo> q;
    vector<bool> visited(g.V, false);

    PathInfo start_info;
    start_info.path.push_back(start);
    start_info.total_cost = 0;
    q.push(start_info);
    visited[start] = true;

    while (!q.empty()) {
        PathInfo current_info = q.front();
        q.pop();

        int current_node = current_info.path.back();

        if (current_node == goal) {
            return current_info;
        }

        for (auto& e : g.adj[current_node]) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                PathInfo neighbor_info = current_info;
                neighbor_info.path.push_back(e.to);
                neighbor_info.total_cost += e.cost;
                q.push(neighbor_info);
            }
        }
    }
    return {{}, 0}; // Return an empty path if not found
}

void printPath(const PathInfo& info) {
    if (info.path.empty()) {
        cout << "No path found." << endl;
    } else {
        for (size_t i = 0; i < info.path.size(); ++i) {
            cout << info.path[i] << (i == info.path.size() - 1 ? "" : " -> ");
        }
        cout << "\nTotal cost: " << info.total_cost << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (source, destination, and optional weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    
    int start_node, goal_node;
    cout << "Enter the starting node: ";
    cin >> start_node;
    cout << "Enter the goal node: ";
    cin >> goal_node;
    
    cout << "\n--- DFS Path to Goal ---" << endl;
    PathInfo dfs_result = dfs(g, start_node, goal_node);
    printPath(dfs_result);
    
    cout << "\n--- BFS Path to Goal ---" << endl;
    PathInfo bfs_result = bfs(g, start_node, goal_node);
    printPath(bfs_result);
    
    return 0;
}