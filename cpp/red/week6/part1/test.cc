#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdint>

#include "profile.h"

int main()
{
    const size_t N = 1'000'000;
    uint64_t acc;
    vector<int> v;
    set<int> s;
    map<int, int> m;

    for (size_t i = 0; i < N; ++i) {
        v.push_back(i);
        s.insert(i);
        m[i] = i;
    }

    {
        LOG_DURATION("Iterate throuth vector");
        acc = 0;
        for (int n : v) {
            acc += n;
        }
        cerr << "acc == " << acc << endl;
    }
    {
        LOG_DURATION("Iterate throuth set");
        acc = 0;
        for (int n : s) {
            acc += n;
        }
        cerr << "acc == " << acc << endl;
    }
    {
        LOG_DURATION("Iterate throuth map");
        acc = 0;
        for (auto it : m) {
            acc += it.first;
        }
        cerr << "acc == " << acc << endl;
    }

    return 0;
}

