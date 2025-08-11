#include <iostream>
#include <vector>
#include <utility>

using namespace std;

bool dfs_with_history(
    int current_node,
    int goal_node,
    const vector<vector<pair<int, int>>>& adj_list,
    vector<bool>& visited,
    vector<int>& path_history,
    int& total_cost
) {
    visited[current_node] = true;
    path_history.push_back(current_node);

    if (current_node == goal_node) {
        return true;
    }

    for (const auto& edge : adj_list[current_node]) {
        int neighbor = edge.first;
        int weight = edge.second;
        if (!visited[neighbor]) {
            total_cost += weight;
            if (dfs_with_history(neighbor, goal_node, adj_list, visited, path_history, total_cost)) {
                return true;
            }
            total_cost -= weight;
        }
    }
    
    path_history.pop_back();
    return false;
}

int main() {
    int num_vertices, num_edges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> num_vertices;

    cout << "Enter the number of edges: ";
    cin >> num_edges;

    vector<vector<pair<int, int>>> adj_list(num_vertices);

    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    int start_node, goal_node;
    cout << "Enter the starting node: ";
    cin >> start_node;

    cout << "Enter the goal node: ";
    cin >> goal_node;

    vector<bool> visited(num_vertices, false);
    vector<int> path;
    int total_cost = 0;

    cout << "Starting DFS from node " << start_node << " to find goal " << goal_node << "." << endl;

    if (dfs_with_history(start_node, goal_node, adj_list, visited, path, total_cost)) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
        cout << "Total cost of the path: " << total_cost << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << "." << endl;
    }

    return 0;
}
