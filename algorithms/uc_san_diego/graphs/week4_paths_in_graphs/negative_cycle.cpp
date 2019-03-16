#include <iostream>
#include <vector>
#include <climits>

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

vector<int> ccheads(const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    vector<int> res;

    for (size_t v = 0; v < adj.size(); ++v) {
        if (!visited[v]) {
            res.push_back(v);
            explore(adj, visited, v);
        }
    }

    return res;
}

int relax_edges(const vector<vector<int>> &adj,
                const vector<vector<int>> &weight,
                vector<int> &dist)
{
    int res = 0;
    for (size_t v = 0; v < adj.size(); ++v) {
        if (dist[v] == INT_MAX) {
            continue;
        }
        for (int u : adj[v]) {
            if (dist[u] > dist[v] + weight[v][u]) {
                dist[u] = dist[v] + weight[v][u];
                res = 1;
            }
        }
    }
    return res;
}

int negative_cycle(const vector<vector<int>> &adj,
                   const vector<vector<int>> &weight,
                   int s)
{
    vector<int> dist(adj.size(), INT_MAX);

    dist[s] = 0;
    for (size_t i = 1; i < adj.size(); ++i) {
        relax_edges(adj, weight, dist);
    }

    return relax_edges(adj, weight, dist);
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
    for (int i = 0; i < E; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        weight[x - 1][y - 1] = w;
    }

    int res = 0;
    vector<int> cch = ccheads(adj);
    for (int s : cch) {
        res += negative_cycle(adj, weight, s);
    }
    res = res > 0 ? 1 : 0;

    cout << res << endl;
    return 0;
}
