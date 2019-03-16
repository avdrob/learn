#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

static int clk = 0;
static vector<int> emptyvec = vector<int>();

inline void previsit(int v, vector<int> &pretime)
{
    pretime[v] = ++clk;
}

inline void postvisit(int v, vector<int> &posttime)
{
    posttime[v] = ++clk;
}

vector<vector<int>> reverse_graph(const vector<vector<int>> &adj)
{
    vector<vector<int>> rgraph(adj.size());
    for (size_t u = 0; u < adj.size(); ++u) {
        for (int v : adj[u]) {
            rgraph[v].push_back(u);
        }
    }
    return rgraph;
}

void explore(const vector<vector<int>> &adj,
             vector<bool> &visited, int v,
             vector<int> &pretime = emptyvec,
             vector<int> &posttime = emptyvec)
{
    visited[v] = true;
    if (pretime.size()) {
        previsit(v, pretime);
    }
    for (int u : adj[v]) {
        if (!visited[u]) {
            explore(adj, visited, u, pretime, posttime);
        }
    }
    if (posttime.size()) {
        postvisit(v, posttime);
    }
}

vector<int> dfs(const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    vector<int> pretime(adj.size(), 0);
    vector<int> posttime(adj.size(), 0);

    for (size_t v = 0; v < adj.size(); ++v) {
        if (!visited[v]) {
            explore(adj, visited, v, pretime, posttime);
        }
    }

    return posttime;
}

int scc_num(const vector<vector<int>> &adj) {
    vector<vector<int>> rgraph = reverse_graph(adj);
    vector<int> rposttime = dfs(rgraph);
    vector<int> rsorted(adj.size());
    iota(rsorted.begin(), rsorted.end(), 0);
    sort(rsorted.begin(), rsorted.end(),
         [&rposttime] (int a, int b) {
             return rposttime[a] > rposttime[b];
         }
    );

    int res = 0;
    vector<bool> visited(adj.size(), false);
    for (int v : rsorted) {
        if (!visited[v]) {
            explore(adj, visited, v);
            res++;
        }
    }

    return res;
}

int main() {
    size_t V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for (size_t i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }

    cout << scc_num(adj);
    return 0;
}
