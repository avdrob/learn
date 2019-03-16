#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bipartite(const vector<vector<int>> &adj)
{
    vector<int> color(adj.size(), -1);
    queue<int> Q;

    color[0] = 0;
    Q.push(0);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int u : adj[v]) {
            if (color[u] == -1) {
                color[u] = 1 - color[v];
                Q.push(u);
            }
            else if (color[u] == color[v]) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for (int i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    cout << bipartite(adj);
    return 0;
}
