#include <iostream>
#include <stack>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

const set<char> opening = {'(', '[', '{'};
const set<char> closing = {')', ']', '}'};
const set<char> brackets = {'(', ')', '[', ']', '{', '}'};
const map<char, char> cls_to_opn = {
                            {')', '('},
                            {']', '['},
                            {'}', '{'}
                        };

int check_brackets(const string &S)
{
    stack<pair<char, int>> pool;

    for (int i = 0; i < S.size(); i++) {
        char c = S[i];

        if (brackets.find(c) == brackets.end()) {
            continue;
        }

        if (opening.find(c) != opening.end()) {
            pool.push(make_pair(c, i));
            continue;
        }

        if (pool.empty() || cls_to_opn.at(c) != pool.top().first) {
            return i + 1;
        }
        else {
            pool.pop();
        }
    }

    if (pool.empty()) {
        return 0;
    }
    else {
        return pool.top().second + 1;
    }
}

int main(int argc, char *argv[])
{
    string S;
    cin >> S;

    int res = check_brackets(S);
    if (res == 0) {
        cout << "Success" << endl;
    }
    else {
        cout << res << endl;
    }

    return 0;
}