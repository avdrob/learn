#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(const vector<vector<int>> &adj, int s, int t)
{
    vector<int> dist(adj.size(), -1);
    queue<int> Q;

    dist[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                Q.push(u);
            }
        }
    }

    return dist[t];
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for (int i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    int s, t;
    cin >> s >> t;
    s--, t--;

    cout << distance(adj, s, t);
    return 0;
}
