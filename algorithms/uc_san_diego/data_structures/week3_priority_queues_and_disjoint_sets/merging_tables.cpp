#include <iostream>
#include <vector>

using namespace std;

class DisjointSets {
public:
    DisjointSets(int n)
        : parent(n), rank(n), size(n), table(n), max_size(0)
    {
        for (int i = 0; i < n; i++) {
            make_set(i);
        }
    }

    void make_set(int i)
    {
        parent[i] = i;
        rank[i] = 0;
        size[i] = 0;
        table[i] = i + 1;
    }

    int find(int i)
    {
        if (i != parent[i]) {
            parent[i] = find(parent[i]);
            table[i] = table[parent[i]];
        }
        return parent[i];
    }

    void unify(int dest, int src)
    {
        int dest_id = find(dest - 1);
        int src_id = find(src - 1);

        if (src_id == dest_id) {
            return;
        }

        if (rank[dest_id] > rank[src_id]) {
            parent[src_id] = dest_id;
            size[dest_id] += size[src_id];
            size[src_id] = 0;
            table[src_id] = table[dest_id];
        }
        else {
            parent[dest_id] = src_id;
            size[src_id] += size[dest_id];
            size[dest_id] = 0;
            table[dest_id] = table[src_id];
            if (rank[src_id] == rank[dest_id]) {
                rank[src_id] += 1;
            }
        }

        max_size = max(max_size, max(size[src_id], size[dest_id]));
    }

    void init_rows(const vector<int> &rows)
    {
        for (int i = 0; i < rows.size(); i++) {
            size[i] = rows[i];
            max_size = max(max_size, rows[i]);
        }
    }

    int get_max_size()
    {
        return max_size;
    }

private:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    vector<int> table;
    int max_size;
};

int main (int argc, char *argv[])
{
    int n, m;
    cin >> n >> m;

    DisjointSets ds(n);
    vector<int> rows(n);
    for (int i = 0; i < n; i++) {
        cin >> rows[i];
    }
    ds.init_rows(rows);

    for (int i = 0; i < m; i++) {
        int dest, src;
        cin >> dest >> src;
        ds.unify(dest, src);
        cout << ds.get_max_size() << endl;
    }


    return 0;
}