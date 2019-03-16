#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <climits>

// using vector;
// using queue;
// using pair;
// using priority_queue;

using namespace std;

void explore(const vector<vector<int>> &adj,
             vector<bool> &visited, int v)
{
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            explore(adj, visited, u);
        }
    }
}

// void dfs(const vector<vector<int>> &adj, vector<bool> &visited)
// {
//     for (size_t v = 0; v < adj.size(); ++v) {
//         if (!visited[v]) {
//             res.push_back(v);
//             explore(adj, visited, v);
//         }
//     }
// }

vector<int> relax_edges(const vector<vector<int>> &adj,
                        const vector<vector<int>> &weight,
                        vector<long long> &dist)
{
    vector<int> relaxed_verts;
    for (size_t v = 0; v < adj.size(); ++v) {
        if (dist[v] == LLONG_MAX) {
            continue;
        }
        for (int u : adj[v]) {
            if (dist[u] > dist[v] + weight[v][u]) {
                dist[u] = dist[v] + weight[v][u];
                relaxed_verts.push_back(u);
            }
        }
    }
    return relaxed_verts;
}

vector<long long> shortest_paths(const vector<vector<int>> &adj,
                                 const vector<vector<int>> &weight,
                                 int s)
{
    vector<long long> dist(adj.size(), LLONG_MAX);

    dist[s] = 0;
    for (size_t i = 1; i < adj.size(); ++i) {
        relax_edges(adj, weight, dist);
    }
    vector<int> relaxed_verts = relax_edges(adj, weight, dist);

    vector<bool> visited(adj.size(), false);
    for (int v : relaxed_verts) {
        explore(adj, visited, v);
    }
    for (size_t v = 0; v < adj.size(); ++v) {
        if (visited[v]) {
            dist[v] = -LLONG_MAX;
        }
    }

    return dist;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    vector<vector<int>> weight(V);
    for (size_t i = 0; i < weight.size(); ++i) {
        weight[i] = vector<int>(V, 0);
    }

    for (int i = 0; i < E; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        weight[x - 1][y - 1] = w;
    }

    int s;
    cin >> s;
    s--;

    vector<long long> dist = shortest_paths(adj, weight, s);
    for (int v = 0; v < V; v++) {
        switch (dist[v]) {
        case LLONG_MAX:
            cout << "*";
            break;
        case -LLONG_MAX:
            cout << "-";
            break;
        default:
            cout << dist[v];
            break;
        }
        cout << endl;
    }

    return 0;
}
