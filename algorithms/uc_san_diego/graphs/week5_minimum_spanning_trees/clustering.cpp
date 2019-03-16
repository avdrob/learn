#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <numeric>
#include <tuple>

using namespace std;

struct Point {
    int x, y;
};

istream &operator>>(istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}

double dist(const Point &p1, const Point &p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) +
                (p2.y - p1.y) * (p2.y - p1.y));
}

class DisjointSets {
public:
    DisjointSets(int n) : parent(n), rank(n, 0)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void join(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (rank[x] > rank[y]) {
            parent[y] = x;
        }
        else {
            parent[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

vector<tuple<double, int, int>> make_edges(const vector<Point> &points)
{
    vector<tuple<double, int, int>> edges;
    for (size_t u = 0; u < points.size(); ++u) {
        for (size_t v = u + 1; v < points.size(); ++v) {
            edges.push_back(make_tuple(dist(points[u], points[v]), u, v));
        }
    }
    return edges;
}

double clustering(const vector<Point> &points, int k)
{
    vector<tuple<double, int, int>> edges = make_edges(points);
    sort(edges.begin(), edges.end());

    DisjointSets dsets(points.size());
    vector<double> picked_edges;
    for (auto &e : edges) {
        double w;
        int u, v;
        tie(w, u, v) = e;
        if (dsets.find(u) != dsets.find(v)) {
            dsets.join(u, v);
            picked_edges.push_back(w);
        }
    }

    return picked_edges[picked_edges.size() - k + 1];
}

int main() {
    size_t n;
    cin >> n;

    vector<Point> points(n);
    for (Point &p : points) {
        cin >> p;
    }
    int k;
    cin >> k;

    cout << fixed << setprecision(10) << clustering(points, k) << endl;
    return 0;
}
