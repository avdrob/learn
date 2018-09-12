#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long dot_product(const vector<long> &a, const vector<long> b)
{
    unsigned long long res = 0;
    int n = a.size();

    for (int i = 0; i < n; i++) {
        res += a[i] * b[i];
    }

    return res;
}


int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    vector<long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end(), [] (long lhs, long rhs) { return lhs > rhs; });
    sort(b.begin(), b.end(), [] (long lhs, long rhs) { return lhs > rhs; });
    cout << dot_product(a, b) << endl;

    return 0;
}