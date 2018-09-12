#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long hash_func(const string &s, long long p, unsigned x)
{
    long long res = 0;
    for (int i = 0; i < s.size(); i++) {
        res = (res * x + s[i]) % p;
    }
    return res % p;
}

long long precompute_hashes(
                    vector<long long> &H,
                    const string &pattern,
                    const string &text
                )
{
    const long long p = 1000000007;
    const unsigned x = 263;

    long long y = 1;
    for (int i = 1; i < pattern.size(); i++) {
        y = (y * x) % p;
    }

    H[0] = hash_func(text.substr(0, pattern.size()), p, x);
    long long first_term = text[0] * y % p;
    for (int i = 1; i <= text.size() - pattern.size(); i++) {
        H[i] = ((H[i - 1] - first_term) * x +\
                text[i + pattern.size() - 1]) % p;
        H[i] = (H[i] + p) % p;
        first_term = text[i] * y % p;
    }

    return hash_func(pattern, p, x);
}

void find_occurences(const string &pattern, const string &text)
{
    vector<long long> H(text.size() - pattern.size() + 1);
    long long phash = precompute_hashes(H, pattern, text);

    bool nonempty = false;
    for (int i = 0; i <= text.size() - pattern.size(); i++) {
        if (H[i] == phash && !text.compare(i, pattern.size(), pattern)) {
            nonempty = true;
            cout << i << " ";
        }
    }
    if (nonempty) {
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    string pattern, text;
    cin >> pattern >> text;

    find_occurences(pattern, text);

    return 0;
}