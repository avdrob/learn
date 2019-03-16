#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

static int clk = 0;

void previsit(int v, vector<int> &pretime)
{
    pretime[v] = ++clk;
}

void postvisit(int v, vector<int> &posttime)
{
    posttime[v] = ++clk;
}

int explore(const vector<vector<int>> &adj,
            vector<bool> &visited,
            vector<int> &pretime,
            vector<int> &posttime,
            int v)
{
    visited[v] = true;
    previsit(v, pretime);
    for (int u : adj[v]) {
        if (!visited[u]) {
            explore(adj, visited, pretime, posttime, u);
        }
    }
    postvisit(v, posttime);
    return 0;
}

vector<int> dfs(const vector<vector<int>> &adj)
{
    vector<bool> visited(adj.size(), false);
    vector<int> pretime(adj.size(), 0);
    vector<int> posttime(adj.size(), 0);

    for (size_t v = 0; v < adj.size(); ++v) {
        if (!visited[v]) {
            explore(adj, visited, pretime, posttime, v);
        }
    }

    vector<int> res(adj.size());
    iota(res.begin(), res.end(), 0);
    sort(res.begin(), res.end(),
         [&posttime] (int a, int b) {
            return posttime[a] > posttime[b];
         }
    );
    return res;
}

vector<int> topsort(vector<vector<int>> &adj)
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

    for (int v : topsort(adj)) {
        cout << v + 1 << " ";
    }
    cout << endl;

    return 0;
}
