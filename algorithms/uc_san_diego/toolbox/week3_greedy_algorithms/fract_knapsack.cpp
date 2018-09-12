#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>

using namespace std;

struct Item {
public:
    int value;
    int weight;
};

istream &operator>>(istream &is, Item &it)
{
    is >> it.value >> it.weight;
    return is;
}

ostream &operator<<(ostream &os, const Item &it)
{
    os << '(' << it.value << ", " << it.weight << ')';
    return os;
}

vector<pair<Item, double>> pack_frac_knapsack(const vector<Item> &items,
                                             int n, double W)
{
    vector<pair<Item, double>> res = {};

    for (int i = 0; i < n; i++) {
        if (W == 0.0) {
            break;
        }
        double amount = min(W, double(items[i].weight));
        W -= amount;
        res.push_back(make_pair(items[i], amount));
    }

    return res;
}

double total_value(const vector<pair<Item, double>> &knapsack)
{
    double res = 0.0;

    for (const auto &it : knapsack) {
        Item item = it.first;
        double amount = it.second;
        res += (double(item.value) / item.weight) * amount;
    }

    return res;
}

int main(int argc, char *argv[])
{
    int n;
    double W;

    cin >> n >> W;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i];
    }

    sort(items.begin(), items.end(),
         [] (const Item &lhs, const Item &rhs) {
             return ((double)lhs.value / lhs.weight) >
                    ((double)rhs.value / rhs.weight);
         });
    cout << fixed << setprecision(4) <<
        total_value(pack_frac_knapsack(items, n, W)) << endl;

    return 0;
}