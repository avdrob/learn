#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

struct Edge {
    int dest;
    int weight;
};

int distance(const vector<vector<Edge>> &adj, int s, int t)
{
    vector<int> dist(adj.size(), INT_MAX);
    priority_queue<pair<int, int>> pq;

    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int d, v;
        tie(d, v) = pq.top();
        pq.pop();

        for (const auto &e : adj[v]) {
            if (dist[e.dest] > d + e.weight) {
                dist[e.dest] = d + e.weight;
                pq.push({dist[e.dest], e.dest});
            }
        }
    }

    return dist[t] != INT_MAX ? dist[t] : -1;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<Edge>> adj(V);
    for (int i = 0; i < E; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back({y - 1, w});
    }

    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << distance(adj, s, t) << endl;

    return 0;
}
