#include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<unsigned> &a,
                  vector<unsigned>::const_iterator low,
                  vector<unsigned>::const_iterator high,
                  unsigned key)
{
    if (high - low <= 0) {
        return -1;
    }

    auto mid = low + (high - low) / 2;
    if (*mid == key) {
        return mid - a.begin();
    }
    if (key < *mid) {
        return binary_search(a, low, mid, key);
    }
    else {
        return binary_search(a, mid + 1, high, key);
    }
}

int main(int argc, char *argv[])
{
    unsigned n, k;

    cin >> n;
    vector<unsigned> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> k;
    vector<unsigned> b(k);
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }

    for (const unsigned &key : b) {
        cout << binary_search(a, a.begin(), a.end(), key) << ' ';
    }
    cout << endl;

    return 0;
}