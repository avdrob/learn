#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <cmath>

#include <cstdlib>
#include <set>
#include <ctime>
#include <cassert>

using namespace std;

const int64_t inf = numeric_limits<int64_t>::max();

struct Edge {
	long double w;
	int u;
};

bool operator<(const Edge &e1, const Edge &e2)
{
	return e1.w != e2.w ? e1.w < e2.w : e1.u < e2.u;
}

class Heap {
public:
    Heap(size_t n) : hsize(0), hpos(n)
	{
		data.reserve(n);
		fill(hpos.begin(), hpos.end(), -1);
	}

    void heapify_down(int i)
    {
        int small = i;

        if (rchild(i) < hsize && data[rchild(i)] < data[small]) {
            small = rchild(i);
        }
        if (lchild(i) < hsize && data[lchild(i)] < data[small]) {
            small = lchild(i);
        }

        if (small != i) {
            hpos[data[i].u] = small;
            hpos[data[small].u] = i;
            swap(data[i], data[small]);
            heapify_down(small);
        }
    }

    void heapify_up(int i)
    {
        while (i > 0 && data[i] < data[parent(i)]) {
            hpos[data[i].u] = parent(i);
            hpos[data[parent(i)].u] = i;
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void push(const Edge &edge)
    {
        data.push_back(edge);
        hpos[edge.u] = hsize;
        hsize++;
        heapify_up(hsize - 1);
		assert(hsize == data.size());
    }

    Edge &pop(int i)
    {
        hsize--;
        hpos[data[hsize].u] = i;
        hpos[data[i].u] = -1;
        swap(data[i], data[hsize]);
		Edge &res = data.back();
		data.pop_back();
        heapify_down(i);
		assert(hsize == data.size());
        return res;
    }

    Edge &pop() { return pop(0); }
    int heap_ind(int i) const { return hpos[i]; }

    size_t size() const { return hsize; }
    bool empty() const { return hsize == 0; }
    void clear() { hsize = 0; }

private:
    static inline size_t lchild(int i) { return 2 * i + 1; }
    static inline size_t rchild(int i) { return 2 * i + 2; }
    static inline size_t parent(int i) { return i > 0 ? (i - 1) / 2 : 0; }

    size_t hsize;
    vector<Edge> data;
    vector<int> hpos;
};

struct Point {
    int x, y;

    long double dist_to(const Point &other) const
    {
        long double dx = other.x - x;
        long double dy = other.y - y;
        return sqrtl(dx * dx + dy * dy);
    }
};

istream& operator>>(istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}

ostream& operator<<(ostream &os, Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

bool operator<(const Point &p1, const Point &p2)
{
    return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
}

void compute_potentials(vector<long double> &pi,
                        const vector<Point> &points,
                        int t)
{
    const Point &target = points[t];
    for (size_t i = 0; i < pi.size(); ++i) {
        pi[i] = target.dist_to(points[i]);
    }
}

int64_t AStar(const vector<vector<int>> &adj,
              const vector<vector<int64_t>> &weight,
              const vector<vector<int>> &adj_r,
              const vector<vector<int64_t>> &weight_r,
              const vector<Point> &points,
              int s, int t)
{
    static vector<int64_t> dist     = vector<int64_t>(adj.size());
    static vector<int64_t> dist_r   = vector<int64_t>(adj_r.size());
    static vector<bool> processed   = vector<bool>(adj.size());
    static vector<bool> processed_r = vector<bool>(adj_r.size());
    static vector<long double> pi   = vector<long double>(points.size());
    static vector<long double> pi_r = vector<long double>(points.size());
    static vector<long double> pot  = vector<long double>(points.size());

    fill(dist.begin(), dist.end(), inf);
    fill(dist_r.begin(), dist_r.end(), inf);
    fill(processed.begin(), processed.end(), false);
    fill(processed_r.begin(), processed_r.end(), false);
    compute_potentials(pi, points, t);
    compute_potentials(pi_r, points, s);

    for (size_t i = 0; i < pot.size(); ++i) {
        pot[i] = (pi[i] - pi_r[i]) / 2;
    }

    priority_queue<pair<long double, int>,
                   vector<pair<long double, int>>,
                   greater<pair<long double, int>>> pq;
    priority_queue<pair<long double, int>,
                   vector<pair<long double, int>>,
                   greater<pair<long double, int>>> pq_r;
	// Heap pq(adj.size());
	// Heap pq_r(adj_r.size());
    dist[s] = 0;
    dist_r[t] = 0;
    pq.push({pot[s], s});
    pq_r.push({-pot[t], t});
    while (!pq.empty() || !pq_r.empty()) {
        long double d;
        int u;

        /* Forward search. */
        if (!pq.empty()) {
            tie(d, u) = pq.top();
            pq.pop();
			// u = pq.pop().u;
            for (size_t i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                int64_t w = weight[u][i];
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({static_cast<long double>(dist[v]) + pot[v], v});
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
			// u = pq_r.pop().u;
            for (size_t i = 0; i < adj_r[u].size(); ++i) {
                int v = adj_r[u][i];
                int64_t w = weight_r[u][i];
                if (dist_r[v] > dist_r[u] + w) {
                    dist_r[v] = dist_r[u] + w;
                    pq_r.push({static_cast<long double>(dist_r[v]) - pot[v], v});
                }
            }
            processed_r[u] = true;
            if (processed[u]) {
                break;
            }
        }
    }

    int64_t res = inf;
    for (size_t i = 0; i < processed.size(); ++i) {
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

// int64_t dijkstra(const vector<vector<int>> &adj,
//                  const vector<vector<int64_t>> &weight,
//                  int s, int t)
// {
//     vector<int64_t> dist(adj.size(), inf);
//     priority_queue<pair<int64_t, int>> pq;
// 
//     dist[s] = 0;
//     pq.push({0, s});
//     while (!pq.empty()) {
//         int64_t d;
//         int v;
//         tie(d, v) = pq.top();
//         pq.pop();
// 
//         for (size_t i = 0; i < adj[v].size(); ++i) {
//             int u = adj[v][i];
//             int64_t w = weight[v][i];
//             if (dist[u] > w + dist[v]) {
//                 dist[u] = dist[v] + w;
//                 pq.push({dist[u], u});
//             }
//         }
//     }
// 
//     return dist[t] != inf ? dist[t] : -1;
// }
// 
// void stress_test(void)
// {
//     const size_t V = 5;
//     const int L = 2 * 100'000;
//     const int64_t W = 15 * L / 10;
//     const int Q = 10;
//     srand(time(NULL));
// 
//     while (true) {
//         vector<Point> points;
//         vector<vector<int>> adj(V);
//         vector<vector<int>> adj_r(V);
//         vector<vector<int64_t>> weight(V);
//         vector<vector<int64_t>> weight_r(V);
// 
//         size_t E;
//         do {
//             E = rand() % V * (V - 1) / 2;
//         } while (!(E > 1));
// 
//         set<Point> pset;
//         int x, y;
//         do {
//             x = rand() % L - L / 2;
//             y = rand() % L - L / 2;
//             pset.insert({x, y});
//         } while (pset.size() < V);
//         assert(pset.size() == V);
//         for (const Point p : pset) {
//             points.push_back(p);
//         }
//         assert(points.size() == V);
// 
//         set<pair<int, int>> eset;
//         vector<tuple<int, int, int64_t>> evec;
//         int u, v;
//         do {
//             u = rand() % (V - 1);
//             do {
//                 v = rand() % (V - 1);
//             } while (v == u);
//             eset.insert({u, v});
//         } while (eset.size() < E);
//         assert(eset.size() == E);
//         for (const auto [u, v] : eset) {
//             int64_t w;
//             do {
//                 // w = rand();
//                 w = rand() % W;
//             } while (w < points[u].dist_to(points[v]));
//             evec.push_back(make_tuple(u, v, w));
//         }
//         assert(evec.size() == E);
// 
//         for (const auto &[u, v, w] : evec) {
//             adj[u].push_back(v);
//             weight[u].push_back(w);
//             adj_r[v].push_back(u);
//             weight_r[v].push_back(w);
//         }
// 
//         set<pair<int, int>> qset;
//         int s, t;
//         do {
//             s = rand() % (V - 1);
//             t = rand() % (V - 1);
//             qset.insert({s, t});
//         } while (qset.size() < Q);
//         assert(qset.size() == Q);
// 
//         int64_t res1, res2;
//         for (const auto &[s, t] : qset) {
//             res1 = dijkstra(adj, weight, s, t);
//             res2 = AStar(adj, weight, adj_r, weight_r, points, s, t);
//             if (res1 != res2) {
//                 cerr << "WRONG ANSWER: s == " << s << ", t == " << t << endl;
//                 cerr << "Dijkstra: " << res1 << endl;
//                 cerr << "AStar: " << res2 << endl;
//                 cerr << "V == " << V << "; {";
//                 for (size_t i = 0; i < points.size(); ++i) {
//                     if (i > 0) {
//                         cerr << ", ";
//                     }
//                     cerr << points[i];
//                 }
//                 cerr << "}" << endl;
//                 cerr << "E == " << E << ":" << endl;
//                 for (const auto &[u, v, w] : evec) {
//                     cerr << "\t" << u << "--" << w << "-->"
//                          << v << endl;
//                 }
//                 cerr << "##########################################" << endl;
//                 cerr << endl;
//                 return;
//             }
//         }
// 
//         {
//             cerr << "V == " << V << "; {";
//             for (size_t i = 0; i < points.size(); ++i) {
//                 if (i > 0) {
//                     cerr << ", ";
//                 }
//                 cerr << points[i];
//             }
//             cerr << "}" << endl;
//             cerr << "E == " << E << ":" << endl;
//             for (const auto &[u, v, w] : evec) {
//                 cerr << "\t" << u << "--" << w << "-->"
//                      << v << endl;
//             }
//             cerr << "##########################################" << endl;
//             cerr << endl;
//         }
//     }
// }
// 
// static const int stats = 2;
// static const int statt = 0;
// static const vector<Point> statpoints = {
//                                 {-61020, 74099},
//                                 {-55030, 20734},
//                                 {-24337, 13926},
//                                 {-4395, -96842}
//                             };
// static const vector<vector<int>> statadj = {
//                                     {2, 3},
//                                     {},
//                                     {0, 1, 3},
//                                     {0}
//                                 };
// static const vector<vector<int64_t>> statweight = {
//                                     {216756, 95925},
//                                     {},
//                                     {192412, 247515, 26539},
//                                     {11051}
//                                 };
// static const vector<vector<int>> statadj_r = {
//                                     {2, 3},
//                                     {2},
//                                     {0},
//                                     {0, 2}
//                                 };
// static const vector<vector<int64_t>> statweight_r = {
//                                     {192412, 11051},
//                                     {247515},
//                                     {216756},
//                                     {95925, 26539}
//                                 };

int main()
{
    // cerr << dijkstra(statadj, statweight, stats, statt) << endl;
    // cerr << AStar(statadj, statweight, statadj_r, statweight_r,
    //               statpoints, stats, statt) << endl;
    // return 0;
    // stress_test();
    // return 0;

    int V, E;
    cin >> V >> E;

    vector<Point> points(V);
    for (Point &p : points) {
        cin >> p;
    }

    vector<vector<int>> adj(V);
    vector<vector<int>> adj_r(V);
    vector<vector<int64_t>> weight(V);
    vector<vector<int64_t>> weight_r(V);
    for (int i = 0; i < E; ++i) {
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
        cout << AStar(adj, weight, adj_r, weight_r, points, s - 1, t - 1);
        cout << endl;
    }

    return 0;
}
