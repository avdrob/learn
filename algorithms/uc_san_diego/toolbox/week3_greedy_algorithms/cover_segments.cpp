#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    unsigned long a, b;
};

istream &operator>>(istream &is, Segment &seg)
{
    is >> seg.a >> seg.b;
    return is;
}

vector<unsigned long> cover_segments(const vector<Segment> &segments)
{
    vector<unsigned long> points = {};
    int uncovered = 0;
    int n = segments.size();

    while (uncovered < n) {
        unsigned long point = segments[uncovered].b;
        points.push_back(point);
        while (point >= segments[uncovered].a && uncovered < n) {
            uncovered++;
        }
    }

    return points;
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    vector<Segment> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i];
    }

    sort(segments.begin(), segments.end(),
         [] (const Segment &lhs, const Segment &rhs) {
             return lhs.b < rhs.b;
         });
    vector <unsigned long> X = cover_segments(segments);
    cout << X.size() << endl;
    for (const auto &p : X) {
        cout << p << ' ';
    }
    cout << endl;

    return 0;
}