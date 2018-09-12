#include <vector>
#include <utility>
#include <iostream>

using namespace std;

static inline int lchild(int i)
{
    return 2 * i + 1;
}

static inline int rchild(int i)
{
    return 2 * i + 2;
}

static inline int parent(int i)
{
    return (i - 1) / 2;
}

void heapify_down(vector<unsigned> &a, int i, vector<pair<int, int>> &swaps)
{
    while (true) {
        int min_ind = i;

        int l = lchild(i);
        if (l < a.size() && a[l] < a[min_ind]) {
            min_ind = l;
        }

        int r = rchild(i);
        if (r < a.size() && a[r] < a[min_ind]) {
            min_ind = r;
        }

        if (i == min_ind) {
            break;
        }
        else {
            swap(a[i], a[min_ind]);
            swaps.push_back(make_pair(min(i, min_ind), max(i, min_ind)));
            i = min_ind;
        }
    }
}

void build_heap(vector<unsigned> &a, vector<pair<int, int>> &swaps)
{
    for (int i = parent(a.size() - 1); i >= 0; i--) {
        heapify_down(a, i, swaps);
    }
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    vector<unsigned> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> swaps;
    build_heap(a, swaps);
    cout << swaps.size() << endl;
    for (const auto &it : swaps) {
        cout << it.first << ' ' << it.second << endl;
    }

    return 0;
}