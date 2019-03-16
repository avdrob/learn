#include <iostream>
#include <vector>

using namespace std;

void explore(const vector<vector<int>> &adj, int u, vector<bool> &visited)
{
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            explore(adj, v, visited);
        }
    }
}

int number_of_components(const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    int res = 0;

    for (size_t u = 0; u < adj.size(); ++u) {
        if (!visited[u]) {
            explore(adj, u, visited);
            res++;
        }
    }

    return res;
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    cout << number_of_components(adj) << endl;
    return 0;
}
