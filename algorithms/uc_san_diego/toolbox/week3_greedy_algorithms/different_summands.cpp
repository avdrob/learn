#include <iostream>
#include <vector>

using namespace std;

vector<unsigned long> decompose(unsigned long n)
{
    vector<unsigned long> res = {};

    for (unsigned long i = 1; ; i++) {
        res.push_back(i);
        unsigned long rem = n - (i + 1) * i / 2;
        if (rem <= i) {
            res[res.size() - 1] = n - (i - 1) * i / 2;
            break;
        }
    }

    return res;
}

int main(int argc, char *argv[])
{
    unsigned long n;
    cin >> n;

    vector<unsigned long> summands = decompose(n);
    cout << summands.size() << endl;
    for (const auto &s : summands) {
        cout << s << ' ';
    }
    cout << endl;

    return 0;
}