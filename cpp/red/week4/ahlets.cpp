#include <list>
#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    const size_t max_sportsmen_num = 100'000;
    list<unsigned> row;
    vector<list<unsigned>::const_iterator> pos(max_sportsmen_num + 1,
                                               row.end());    

    unsigned n;
    cin >> n;
    for (unsigned i = 0; i < n; ++i) {
        unsigned num, next;
        cin >> num >> next;
        pos[num] = row.insert(pos[next], num);
    }

    for (const unsigned num : row) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}