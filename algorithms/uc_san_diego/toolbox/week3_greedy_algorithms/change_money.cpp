#include <iostream>
#include <vector>

using namespace std;

vector<int> coins = {10, 5, 1};

vector<int> exchange_money(int m)
{
    vector<int> res = {};

    for (auto c : coins) {
        while (c <= m) {
            res.push_back(c);
            m -= c;
        }
    }

    return res;
}

int main(int argc, char *argv[])
{
    int m;

    cin >> m;
    cout << exchange_money(m).size() << endl;

    return 0;
}
