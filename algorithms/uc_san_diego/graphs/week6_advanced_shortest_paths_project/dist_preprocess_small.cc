#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <set>
#include <limits>
#include <algorithm>

#include <cstdlib>
#include <cassert>
#include <chrono>

using namespace std;
using namespace chrono;

class Graph {
public:
    using pqueue = priority_queue<pair<int, int>,
                                  vector<pair<int, int>>,
                                  greater<pair<int, int>>>;
    const int INF = numeric_limits<int>::max() / 2;

    Graph() = delete;
    Graph(size_t n, size_t m)
        : V(n), E(m), adj(n), adj_r(n), weight(n), weight_r(n),
          shortcuts(n), covered_nghbrs(n), contr_nghbrs(n, 0),
          witness_dist(n), node_level(n, 0), rank(n, -1)
    {}

    void add_edge(int u, int v, int w)
    {
        adj[u].push_back(v);
        weight[u].push_back(w);
        adj_r[v].push_back(u);
        weight_r[v].push_back(w);
    }

    void preprocess(void)
    {
        cerr << "Start processing" << endl;
        auto start = steady_clock::now();
        vector<bool> contracted(V, false);
        // vector<int> forward_dist(V);
        // vector<int> reverse_dist(V);
        pqueue pq;

        for (size_t u = 0; u < V; ++u) {
            pq.push({importance(u), u});
        }

        while (!pq.empty()) {
            int imp, v;
            tie(imp, v) = pq.top();
            pq.pop();

            if (contracted[v]) {
                continue;
            }
            imp = importance(v);
            if (imp > pq.top().first) {
                pq.push({imp, v});
                continue;
            }

            // calc_dist_to_nghbrs(v, forward_dist, reverse_dist, contracted);
            int uplimit = calc_upper_bound(v, contracted);

            /* Predecessors of v */
            for (size_t i = 0; i < adj_r[v].size(); ++i) {
                int u = adj_r[v][i];
                if (contracted[u]) {
                    continue;
                }
                witness_search(u, v, contracted, uplimit);
                /* Successors of v */
                for (size_t j = 0; j < adj[v].size(); ++j) {
                    int w = adj[v][j];
                    if (!contracted[w] && w != u && witness_dist[w] == INF) {
                        // add_shortcut(v, u, w, reverse_dist[u] +
                        //                       forward_dist[w]);
                        add_shortcut(v, u, w, weight_r[v][i] + weight[v][j]);
                        cerr << "HEY: " << j << endl;
                    }
                }
            }

            contract_node(v, contracted);
        }

        auto finish = steady_clock::now();
        auto millis = duration_cast<milliseconds>(finish - start).count();
        cout << "Ready";
        cout << ": " << millis / 1000 << "." << millis % 1000 << endl;
    }

    void contract_redundant_edges(void)
    {
        vector<vector<int>> aug_adj(V);
        vector<vector<int>> aug_weight(V);
        vector<vector<int>> aug_adj_r(V);
        vector<vector<int>> aug_weight_r(V);

        for (size_t u = 0; u < adj.size(); ++u) {
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                if (rank[v] > rank[u]) {
                    int w = weight[u][i];
                    aug_adj[u].push_back(v);
                    aug_weight[u].push_back(w);
                }
            }
        }
        adj.clear();
        adj = move(aug_adj);
        weight.clear();
        weight = move(aug_weight);

        for (size_t u = 0; u < adj_r.size(); ++u) {
            for (size_t i = 0; i < adj_r[u].size(); ++i) {
                int v = adj_r[u][i];
                if (rank[v] > rank[u]) {
                    int w = weight_r[u][i];
                    aug_adj_r[u].push_back(v);
                    aug_weight_r[u].push_back(w);
                }
            }
        }
        adj_r.clear();
        adj_r = move(aug_adj_r);
        weight_r.clear();
        weight_r = move(aug_weight_r);
    }

    int compute_distance(int s, int t)
    {
        static pqueue pq;
        static pqueue pq_r;
        static vector<int> dist         = vector<int>(V);
        static vector<int> dist_r       = vector<int>(V);
        static vector<bool> processed   = vector<bool>(V);
        static vector<bool> processed_r = vector<bool>(V);

        pq = pqueue();
        pq_r = pqueue();
        fill(dist.begin(), dist.end(), INF);
        fill(dist_r.begin(), dist_r.end(), INF);
        fill(processed.begin(), processed.end(), false);
        fill(processed_r.begin(), processed_r.end(), false);

        int res = INF;

        dist[s] = dist_r[t] = 0;
        pq.push({0, s});
        pq_r.push({0, t});
        while (!pq.empty() || !pq_r.empty()) {
            int d, u;

            /* Forward search. */
            if (!pq.empty()) {
                tie(d, u) = pq.top();
                pq.pop();
                if (!processed[u] && dist[u] <= res) {
                    for (size_t i = 0; i < adj[u].size(); ++i) {
                        int v = adj[u][i];
                        int w = weight[u][i];
                        if (dist[v] > dist[u] + w) {
                            dist[v] = dist[u] + w;
                            pq.push({dist[v], v});
                        }
                    }
                    processed[u] = true;
                }
                if (processed_r[u] && dist[u] + dist_r[u] < res) {
                    res = dist[u] + dist_r[u];
                }
            }

            /* Backward search. */
            if (!pq_r.empty()) {
                tie(d, u) = pq_r.top();
                pq_r.pop();
                if (!processed_r[u] && dist_r[u] <= res) {
                    for (size_t i = 0; i < adj_r[u].size(); ++i) {
                        int v = adj_r[u][i];
                        int w = weight_r[u][i];
                        if (dist_r[v] > dist_r[u] + w) {
                            dist_r[v] = dist_r[u] + w;
                            pq_r.push({dist_r[v], v});
                        }
                    }
                    processed_r[u] = true;
                }
                if (processed[u] && dist[u] + dist_r[u] < res) {
                    res = dist[u] + dist_r[u];
                }
            }
        }

        return res != INF ? res : -1;
    }


private:
    struct Shortcut {
        int from, to, cost;
    };

    void witness_search(int u, int v, vector<bool> &contracted, int uplimit)
    {
        static pqueue pq;

        pq = pqueue();
        fill(witness_dist.begin(), witness_dist.end(), INF);
        witness_dist[u] = 0;
        pq.push({0, u});
        while (!pq.empty()) {
            int d, s;
            tie(d, s) = pq.top();
            pq.pop();

            if (d > uplimit) {
                return;
            }

            for (size_t i = 0; i < adj[s].size(); ++i) {
                int t = adj[s][i];
                if (contracted[t] || t == v) {
                    continue;
                }
                int w = weight[s][i];
                if (witness_dist[s] + w < witness_dist[s] &&
                    witness_dist[s] < uplimit) {
                    witness_dist[t] = witness_dist[s] + w;
                    pq.push({witness_dist[t], t});
                }
            }
        }
    }

    void calc_dist_to_nghbrs(int v,
                             vector<int> &forward_dist,
                             vector<int> &reverse_dist,
                             const vector<bool> &contracted)
    {
        static pqueue pq;
        static pqueue pq_r;

        pq = pqueue();
        pq_r = pqueue();
        fill(forward_dist.begin(), forward_dist.end(), INF);
        fill(reverse_dist.begin(), reverse_dist.end(), INF);

        // for (size_t i = 0; i < adj[v].size(); ++i) {
        //     forward_dist[adj[v][i]] = weight[v][i];
        // }
        // for (size_t i = 0; i < adj_r[v].size(); ++i) {
        //     reverse_dist[adj_r[v][i]] = weight_r[v][i];
        // }

        int forward_max = INF;
        int reverse_max = INF;
        auto forward_it = max_element(weight[v].begin(), weight[v].end());
        auto reverse_it = max_element(weight_r[v].begin(), weight_r[v].end());
        if (forward_it != weight[v].end()) {
            forward_max = *forward_it;
        }
        if (reverse_it != weight_r[v].end()) {
            reverse_max = *reverse_it;
        }

        forward_dist[v] = 0;
        pq.push({0, v});
        while (!pq.empty()) {
            int d, s;
            tie(d, s) = pq.top();
            pq.pop();

            if (d > forward_max) {
                continue;
            }

            for (size_t i = 0; i < adj[s].size(); ++i) {
                int t = adj[s][i];
                if (contracted[t]) {
                    continue;
                }
                int w = weight[s][i];
                if (forward_dist[t] > forward_dist[s] + w) {
                    forward_dist[t] = forward_dist[s] + w;
                    pq.push({forward_dist[t], t});
                }
            }
        }

        reverse_dist[v] = 0;
        pq_r.push({0, v});
        while (!pq_r.empty()) {
            int d, s;
            tie(d, s) = pq_r.top();
            pq_r.pop();

            if (d > reverse_max) {
                continue;
            }

            for (size_t i = 0; i < adj_r[s].size(); ++i) {
                int t = adj_r[s][i];
                if (contracted[t]) {
                    continue;
                }
                int w = weight_r[s][i];
                if (reverse_dist[t] > reverse_dist[s] + w) {
                    reverse_dist[t] = reverse_dist[s] + w;
                    pq_r.push({reverse_dist[t], t});
                }
            }
        }
    }

    // int dijkstra(int u, int w, vector<bool> &contracted) const
    // {
    //     static pqueue pq;
    //     static vector<int> dist(V);

    //     pq = pqueue;
    //     fill(dist.begin(),  dist.end(), INF);
    //     dist[u] = 0;
    //     pq.push({0, u});
    //     while (!pq.empty()) {
    //         int d, s;
    //         tie(d, s) = pq.top();
    //         pq.pop();

    //         for (size_t i = 0; i < adj[s].size(); ++i) {
    //             int t = adj[s][i];
    //             if (contracted[t]) {
    //                 continue;
    //             }
    //             int w = weight[s][i];
    //             if (witness_dist[t] > witness_dist[s] + w) {
    //                 witness_dist[t] = witness_dist[s] + w;
    //                 pq.push({witness_dist[t], t});
    //             }
    //         }
    //     }
    // }

    void add_shortcut(int v, int from, int to, int cost)
    {
        adj[from].push_back(to);
        weight[from].push_back(cost);
        adj_r[to].push_back(from);
        weight_r[to].push_back(cost);
        shortcuts[v].push_back({from, to, cost});
        covered_nghbrs[v].insert(from);
        covered_nghbrs[v].insert(to);
    }

    int calc_upper_bound(int v, const vector<bool> &contracted) const
    {
        int max1 = -1;
        int max2 = -1;
        int min1 = INF;

        for (size_t i = 0; i < adj[v].size(); ++i) {
            int u = adj[v][i];
            int w = weight[v][i];
            if (!contracted[u]) {
                max1 = max(max1, w);
            }
        }
        max1 = max(max1, 0);

        for (size_t i = 0; i < adj_r[v].size(); ++i) {
            int u = adj_r[v][i];
            int w = weight_r[v][i];
            if (!contracted[u]) {
                max2 = max(max2, w);
            }
        }
        max2 = max(max2, 0);

        for (int u : adj[v]) {
            if (contracted[u]) {
                continue;
            }
            for (size_t i = 0; i < adj_r[u].size(); ++i) {
                int u1 = adj_r[u][i];
                int w = weight_r[u][i];
                if (!contracted[u1] && u1 != v) {
                    min1 = min(min1, w);
                }
            }
        }
        min1 = min(min1, 0);

        return max1 + max2 - min1;
    }

    inline size_t degree(int u) const
    {
        return adj[u].size() + adj_r[u].size();
    }

    inline int edge_diff(int u) const
    {
        return static_cast<int>(shortcuts[u].size()) +
               static_cast<int>(degree(u));
    }

    void contract_node(int u, vector<bool> &contracted)
    {
        static int cur_rank = 0;

        contracted[u] = true;
        rank[u] = cur_rank++;

        for (int v : adj[u]) {
            contr_nghbrs[v]++;
            node_level[v] = max(node_level[v], node_level[u] + 1);
        }
        for (int v : adj_r[u]) {
            contr_nghbrs[v]++;
            node_level[v] = max(node_level[v], node_level[u] + 1);
        }
    }

    int importance(int u) const
    {
        return edge_diff(u) + contr_nghbrs[u] + node_level[u] +
               static_cast<int>(covered_nghbrs[u].size());
    }

    size_t V, E;

    vector<vector<int>> adj;
    vector<vector<int>> adj_r;
    vector<vector<int>> weight;
    vector<vector<int>> weight_r;

    vector<vector<Shortcut>> shortcuts;
    vector<set<int>> covered_nghbrs;
    vector<int> contr_nghbrs;
    vector<int> witness_dist;
    vector<int> node_level;
    vector<int> rank;
};

int dijkstra(const vector<vector<int>> &adj,
                 const vector<vector<int>> &weight,
                 int s, int t)
{
    const int INF = numeric_limits<int>::max() / 2;

    vector<int> dist(adj.size(), INF);
    priority_queue<pair<int, int>> pq;

    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int d;
        int v;
        tie(d, v) = pq.top();
        pq.pop();

        for (size_t i = 0; i < adj[v].size(); ++i) {
            int u = adj[v][i];
            int w = weight[v][i];
            if (dist[u] > w + dist[v]) {
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
        }
    }

    return dist[t] != INF ? dist[t] : -1;
}

void stress_test(void)
{
    const size_t V = 110;
    const size_t E = 170;
    const int W = 100;
    const int Q = 1;
    srand(time(NULL));

    while (true) {
        cerr << "Start generating" << endl;
        vector<vector<int>> adj(V);
        vector<vector<int>> adj_r(V);
        vector<vector<int>> weight(V);
        vector<vector<int>> weight_r(V);

        // size_t E;
        // do {
        //     E = rand() % V * (V - 1) / 2;
        // } while (!(E > 1));

        Graph graph(V, E);

        set<pair<int, int>> eset;
        vector<tuple<int, int, int>> evec;
        int u, v;
        do {
            u = rand() % (V - 1);
            do {
                v = rand() % (V - 1);
            } while (v == u);
            eset.insert({u, v});
        } while (eset.size() < E);
        assert(eset.size() == E);
        for (const auto &it: eset) {
            int u = it.first;
            int v = it.second;
            int w = rand() % W;
            evec.push_back(make_tuple(u, v, w));
        }
        assert(evec.size() == E);

        for (const auto &it : evec) {
            int u = get<0>(it);
            int v = get<1>(it);
            int w = get<2>(it);
            graph.add_edge(u, v, w);
            adj[u].push_back(v);
            weight[u].push_back(w);
            adj_r[v].push_back(u);
            weight_r[v].push_back(w);
        }

        set<pair<int, int>> qset;
        int s, t;
        do {
            s = rand() % (V - 1);
            t = rand() % (V - 1);
            qset.insert({s, t});
        } while (qset.size() < Q);
        assert(qset.size() == Q);

        cerr << "Finish generating" << endl;

        graph.preprocess();
        graph.contract_redundant_edges();

        int res1, res2;
        for (const auto &it1 : qset) {
            int s = it1.first;
            int t = it1.second;
            res1 = dijkstra(adj, weight, s, t);
            res2 = graph.compute_distance(s, t);
            if (res1 != res2) {
                cerr << "WRONG ANSWER: s == " << s << ", t == " << t << endl;
                cerr << "Dijkstra: " << res1 << endl;
                cerr << "CH: " << res2 << endl;
                cerr << "V == " << V << endl;
                // for (size_t i = 0; i < points.size(); ++i) {
                //     if (i > 0) {
                //         cerr << ", ";
                //     }
                //     cerr << points[i];
                // }
                // cerr << "}" << endl;
                cerr << "E == " << E << ":" << endl;
                for (const auto &it2 : evec) {
                    int u = get<0>(it2);
                    int v = get<1>(it2);
                    int w = get<2>(it2);
                    cerr << "\t" << u << "--" << w << "-->"
                         << v << endl;
                }
                cerr << "##########################################" << endl;
                cerr << endl;
                return;
            }
        }

        {
            cerr << "V == " << V << endl;
            // for (size_t i = 0; i < points.size(); ++i) {
            //     if (i > 0) {
            //         cerr << ", ";
            //     }
            //     cerr << points[i];
            // }
            // cerr << "}" << endl;
            cerr << "E == " << E << ":" << endl;
            for (const auto &it3 : evec) {
                int u = get<0>(it3);
                int v = get<1>(it3);
                int w = get<2>(it3);
                cerr << "\t" << u << "--" << w << "-->"
                     << v << endl;
            }
            cerr << "##########################################" << endl;
            cerr << endl;
        }
    }
}

void test1(void)
{
    const size_t V = 4;
    const size_t E = 4;
    const vector<tuple<int, int, int>> test_case = {
                                        {0, 1, 4},
                                        {0, 3, 7},
                                        {1, 3, 2},
                                        {3, 2, 11}
                                    };
    const int s = 0;
    const int t = 2;

    vector<vector<int>> adj(V);
    vector<vector<int>> weight(V);
    Graph graph(V, E);

    for (const auto &it : test_case) {
        int u = get<0>(it);
        int v = get<1>(it);
        int w = get<2>(it);
        adj[u].push_back(v);
        weight[u].push_back(w);
        graph.add_edge(u, v, w);
    }

    graph.preprocess();
    graph.contract_redundant_edges();

    cout << "Dijkstra: " << dijkstra(adj, weight, s, t) << endl;
    cout << "CH: " << graph.compute_distance(s, t) << endl;
}

void test2(void)
{
    const size_t V = 4;
    const size_t E = 6;
    const vector<tuple<int, int, int>> test_case = {
                                        {0, 2, 8},
                                        {0, 3, 16},
                                        {1, 0, 18},
                                        {1, 2, 7},
                                        {2, 3, 1},
                                        {3, 2, 6}
                                    };
    const int s = 0;
    const int t = 3;

    vector<vector<int>> adj(V);
    vector<vector<int>> weight(V);
    Graph graph(V, E);

    for (const auto &it : test_case) {
        int u = get<0>(it);
        int v = get<1>(it);
        int w = get<2>(it);
        adj[u].push_back(v);
        weight[u].push_back(w);
        graph.add_edge(u, v, w);
    }

    graph.preprocess();
    graph.contract_redundant_edges();

    cout << "Dijkstra: " << dijkstra(adj, weight, s, t) << endl;
    cout << "CH: " << graph.compute_distance(s, t) << endl;
}

int main()
{
    stress_test();
    return 0;

    size_t V, E;
    cin >> V >> E;

    Graph graph(V, E);
    for (size_t i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.add_edge(u - 1, v - 1, w);
    }

    graph.preprocess();
    graph.contract_redundant_edges();

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int s, t;
        cin >> s >> t;
        cout << graph.compute_distance(s - 1, t - 1) << endl;
    }

    return 0;
}
