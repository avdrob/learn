#include <iostream>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>> &adj, int u, vector<bool> &visited)
{
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, v, visited);
        }
    }
}

int reach(const vector<vector<int>> &adj, int u, int v)
{
    vector<bool> visited(adj.size(), false);
    dfs(adj, u, visited);
    return visited[v];
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<vector<int> > adj(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    int x, y;
    cin >> x >> y;
    cout << reach(adj, x - 1, y - 1) << endl;

    return 0;
}
