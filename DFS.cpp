#include <iostream>
#include <vector>
#include <utility>

using namespace std;

bool find_path_dfs_helper(
    int current_node,
    int goal_node,
    const vector<vector<pair<int, int>>>& adj_list,
    vector<bool>& visited,
    vector<int>& current_path,
    int current_cost,
    vector<int>& final_path,
    int& final_cost_ref
) {
    visited[current_node] = true;
    current_path.push_back(current_node);

    if (current_node == goal_node) {
        final_path = current_path;
        final_cost_ref = current_cost;
        return true;
    }

    for (const auto& edge : adj_list[current_node]) {
        int neighbor = edge.first;
        int weight = edge.second;

        if (!visited[neighbor]) {
            if (find_path_dfs_helper(neighbor, goal_node, adj_list, visited, current_path, current_cost + weight, final_path, final_cost_ref)) {
                return true;
            }
        }
    }

    current_path.pop_back();
    return false;
}

void find_path_dfs(
    int num_vertices,
    const vector<vector<pair<int, int>>>& adj_list,
    int start_node,
    int goal_node
) {
    if (start_node < 0 || start_node >= num_vertices || goal_node < 0 || goal_node >= num_vertices) {
        cout << "Invalid start or goal node." << endl;
        return;
    }

    vector<bool> visited(num_vertices, false);
    vector<int> current_path;
    vector<int> final_path;
    int final_cost = 0;

    bool path_found = find_path_dfs_helper(start_node, goal_node, adj_list, visited, current_path, 0, final_path, final_cost);

    if (path_found) {
        cout << "Path from " << start_node << " to " << goal_node << ": ";
        for (size_t i = 0; i < final_path.size(); ++i) {
            cout << final_path[i] << (i == final_path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
        cout << "Total cost of the path: " << final_cost << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << "." << endl;
    }
}

int main() {
    int num_vertices, num_edges;
    int start_node, goal_node;

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

    cout << "Enter the starting node: ";
    cin >> start_node;

    cout << "Enter the goal node: ";
    cin >> goal_node;

    find_path_dfs(num_vertices, adj_list, start_node, goal_node);

    return 0;
}
