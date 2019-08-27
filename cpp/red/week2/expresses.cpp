#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish)
    {
        reachable[start].insert(finish);
        reachable[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const
    {
        int res = abs(finish - start);

        if (reachable.find(start) != reachable.end()) {
            const set<int> &dest = reachable.at(start);
            set<int>::const_iterator it = dest.lower_bound(finish);
            if (it != dest.end()) {
                res = min(res, *it - finish);
            }
            if (it != dest.begin()) {
                res = min(res, finish - *prev(it));
            }
        }

        return res;
    }


private:
    map<int, set<int>> reachable;
};


int main() {
    RouteManager routes;

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        string cmd;
        cin >> cmd;

        int start, finish;
        cin >> start >> finish;
        if (cmd == "ADD") {
            routes.AddRoute(start, finish);
        }
        else if (cmd == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
