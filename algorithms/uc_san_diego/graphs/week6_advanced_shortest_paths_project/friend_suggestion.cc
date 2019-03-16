#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cstdint>
#include <utility>
#include <tuple>

using namespace std;

const int64_t inf = numeric_limits<int64_t>::max();

int64_t bidirectional_dijkstra(const vector<vector<int>> &adj,
                               const vector<vector<int64_t>> &weight,
                               const vector<vector<int>> &adj_r,
                               const vector<vector<int64_t>> &weight_r,
                               int s, int t)
{
    static vector<int64_t> dist     = vector<int64_t>(adj.size());
    static vector<int64_t> dist_r   = vector<int64_t>(adj.size());
    static vector<bool> processed   = vector<bool>(adj.size());
    static vector<bool> processed_r = vector<bool>(adj.size());

    fill(dist.begin(), dist.end(), inf);
    fill(dist_r.begin(), dist_r.end(), inf);
    fill(processed.begin(), processed.end(), false);
    fill(processed_r.begin(), processed_r.end(), false);

    priority_queue<pair<int64_t, int>,
                   vector<pair<int64_t, int>>,
                   greater<pair<int64_t, int>>> pq;
    priority_queue<pair<int64_t, int>,
                   vector<pair<int64_t, int>>,
                   greater<pair<int64_t, int>>> pq_r;
    dist[s] = 0;
    dist_r[t] = 0;
    pq.push({0, s});
    pq_r.push({0, t});
    while (!pq.empty() || !pq_r.empty()) {
        int64_t d;
        int u;

        /* Forward search. */
        if (!pq.empty()) {
            tie(d, u) = pq.top();
            pq.pop();
            for (register size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                int64_t w = weight[u][i];
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
            processed[u] = true;
            if (processed_r[u]) {
                break;
            }
        }

        /* Backward search. */
        if (!pq_r.empty()) {
            tie(d, u) = pq_r.top();
            pq_r.pop();
            for (register size_t i = 0; i < adj_r[u].size(); ++i) {
                int v = adj_r[u][i];
                int64_t w = weight_r[u][i];
                if (dist_r[v] > dist_r[u] + w) {
                    dist_r[v] = dist_r[u] + w;
                    pq_r.push({dist_r[v], v});
                }
            }
            processed_r[u] = true;
            if (processed[u]) {
                break;
            }
        }
    }

    int64_t res = inf;
    for (register size_t i = 0; i < processed.size(); ++i) {
        if (!(processed[i] || processed_r[i])) {
            continue;
        }
        if (dist[i] != inf && dist_r[i] != inf &&
            res > dist[i] + dist_r[i]) {
            res = dist[i] + dist_r[i];
        }
    }
    return res != inf ? res : -1;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    vector<vector<int>> adj_r(V);
    vector<vector<int64_t>> weight(V);
    vector<vector<int64_t>> weight_r(V);
    for (register int i = 0; i < E; ++i) {
        int u, v;
        int64_t w;
        cin >> u >> v >> w;
        adj[u - 1].push_back(v - 1);
        weight[u - 1].push_back(w);
        adj_r[v - 1].push_back(u - 1);
        weight_r[v - 1].push_back(w);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int s, t;
        cin >> s >> t;
        cout << bidirectional_dijkstra(adj, weight, adj_r,
                                       weight_r, s - 1, t - 1);
        cout << endl;
    }

    return 0;
}
