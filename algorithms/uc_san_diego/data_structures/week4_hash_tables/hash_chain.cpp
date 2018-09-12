#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTable {
public:
    HashTable(int m)
        : table(m), table_size(m)
    {}

    void add(const string &s)
    {
        if (find(s) == "yes") {
            return;
        }

        auto &bucket = table[hash(s)];
        bucket.push_front(s);
    }

    void del(const string &s)
    {
        table[hash(s)].remove(s);
    }

    string find(const string &s)
    {
        auto &bucket = table[hash(s)];

        if (bucket.empty()) {
            return "no";
        }

        for (const string &item : bucket) {
            if (s == item) {
                return "yes";
            }
        }
        return "no";
    }

    void check(unsigned i)
    {
        auto &bucket = table[i];
        for (const string &item : bucket) {
            cout << item << " ";
        }
        cout << endl;
    }

private:
    vector<list<string>> table;
    const unsigned table_size;

    unsigned long long hash(const string &s)
    {
        static const unsigned long long p = 1000000007;
        static const unsigned long long x = 263;

        unsigned long long res = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            res = (res * x + unsigned(s[i])) % p;
        }

        return (res % p) % table_size;
    }
};

int main(int argc, char *argv[])
{
    int m, N;
    cin >> m >> N;

    HashTable ht(m);
    for (int i = 0; i < N; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "add") {
            string s;
            cin >> s;
            ht.add(s);
        }
        else if (cmd == "del") {
            string s;
            cin >> s;
            ht.del(s);
        }
        else if (cmd == "find") {
            string s;
            cin >> s;
            cout << ht.find(s) << endl;
        }
        else if (cmd == "check") {
            unsigned i;
            cin >> i;
            ht.check(i);
        }
        else {
            continue;
        }
    }

    return 0;
}