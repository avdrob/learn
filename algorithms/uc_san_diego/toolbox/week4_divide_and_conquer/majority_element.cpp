#include <iostream>
#include <vector>

using namespace std;

int majority_element(const vector<unsigned> &a, int low, int high)
{
    if (high == low) {
        return a[low];
    }

    int mid = low + (high - low) / 2;
    int major_left = majority_element(a, low, mid);
    int major_right = majority_element(a, mid + 1, high);

    int count[2] = {0, 0};
    for (int i = low; i <= high; i++) {
        if (a[i] == major_left) {
            count[0]++;
        }
        else if (a[i] == major_right) {
            count[1]++;
        }
    }

    int n = high - low + 1;
    if (count[0] > n / 2) {
        return major_left;
    }
    else if (count[1] > n / 2) {
        return major_right;
    }
    else {
        return -1;
    }

}

int main(int argc, char *argv[])
{
    unsigned n;
    cin >> n;

    vector<unsigned> a(n);
    for (unsigned &u : a) {
        cin >> u;
    }

    if (majority_element(a, 0, a.size() - 1) >= 0) {
        cout << 1 << endl;
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}