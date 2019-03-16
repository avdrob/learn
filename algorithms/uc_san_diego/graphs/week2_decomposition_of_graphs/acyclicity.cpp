#include <iostream>
#include <vector>

using namespace std;

void previsit(int v, vector<bool> &pathstack)
{
    pathstack[v] = true;
}

void postvisit(int v, vector<bool> &pathstack)
{
    pathstack[v] = false;
}

int explore(const vector<vector<int>> &adj,
            vector<bool> &visited,
            int v)
{
    static vector<bool> pathstack(adj.size(), false);

    visited[v] = true;
    previsit(v, pathstack);
    for (int u : adj[v]) {
        if (visited[u] && pathstack[u]) {
            return 1;
        }
        if (!visited[u]) {
            if (explore(adj, visited, u)) {
                return 1;
            }
        }
    }
    postvisit(v, pathstack);
    return 0;
}

int dfs(const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    for (size_t v = 0; v < adj.size(); ++v) {
        if (!visited[v]) {
            if (explore(adj, visited, v)) {
                return 1;
            }
        }
    }

    return 0;
}

int acyclic(const vector<vector<int>> &adj)
{
    return dfs(adj);
}

int main()
{
    size_t V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for (size_t i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    cout << acyclic(adj);

  return 0;
}
