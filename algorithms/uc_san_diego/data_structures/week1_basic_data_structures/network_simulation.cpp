#include <iostream>
#include <deque>
#include <vector>

using namespace std;

struct Packet {
    unsigned A, P;
};

istream &operator>>(istream &is, Packet &p)
{
    is >> p.A >> p.P;
    return is;
}

void process_packets(const vector<Packet> &packets, int S)
{
    deque<unsigned> finish_time;

    for (const Packet &packet : packets) {
        while (!finish_time.empty() && finish_time.front() <= packet.A) {
            finish_time.pop_front();
        }

        if (finish_time.size() >= S) {
            cout << -1 << endl;
        }
        else {
            unsigned start;

            if (finish_time.empty()) {
                start = packet.A;
            }
            else {
                start = finish_time.back();
            }
            cout << start << endl;
            finish_time.push_back(start + packet.P);
        }
    }
}

int main(int argc, char *argv[])
{
    int S, n;
    cin >> S >> n;

    if (n == 0) {
        return 0;
    }

    vector<Packet> packets(n);
    for (int i = 0; i < n; i++) {
        cin >> packets[i];
    }
    process_packets(packets, S);

    return 0;
}