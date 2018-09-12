#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>

using namespace std;

tuple<int, int> partition3(vector<unsigned> &a, int low, int high)
{
    int mid = low + rand() % (high - low + 1);
    unsigned pivot = a[mid];
    swap(a[low], a[mid]);

    int last_less = low;
    int last_equal = low;
    for (int i = low + 1; i <= high; i++) {
        if (a[i] == pivot) {
            last_equal++;
            swap(a[i], a[last_equal]);
        }
        else if (a[i] < pivot) {
            last_equal++;
            swap(a[i], a[last_equal]);
            last_less++;
            swap(a[last_equal], a[last_less]);
        }
    }

    swap(a[last_less], a[low]);
    last_less--;

    return make_tuple(last_less, last_equal);
}

void qsort3(vector<unsigned> &a, int low, int high)
{
    if (low >= high) {
        return;
    }

    int last_less, last_equal;
    tie(last_less, last_equal) = partition3(a, low, high);
    qsort3(a, low, last_less);
    qsort3(a, last_equal + 1, high);
}

int main(int argc, char *argv[])
{
    unsigned n;
    cin >> n;

    vector<unsigned> a(n);
    for (unsigned &u : a) {
        cin >> u;
    }

    qsort3(a, 0, a.size() - 1);
    for (unsigned &u : a) {
        cout << u << ' ';
    }
    cout << endl;

    return 0;
}