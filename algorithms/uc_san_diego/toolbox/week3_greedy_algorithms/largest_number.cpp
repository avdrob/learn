#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

bool digits_greater(int lhs, int rhs)
{
   string first = to_string(lhs) + to_string(rhs);
   string second = to_string(rhs) + to_string(lhs);
   return first > second;
}

string greatest_num(vector<int> &numbers)
{
    stringstream ss("");

    sort(numbers.begin(), numbers.end(), digits_greater);
    for (const auto n : numbers) {
        ss << n;
    }

    return ss.str();
}

/*
string greatest_num_dumb(vector<int> &numbers)
{
    stringstream ss;
    string max = "";

    sort(numbers.begin(), numbers.end());
    do {
        ss.str("");
        for (const auto n : numbers) {
            ss << n;
        }
        if (ss.str() > max) {
            max = ss.str();
        }
    } while (next_permutation(numbers.begin(), numbers.end()));

    return max;
}

void stress_test(void)
{
    int n = 5;
    int max_num = 1000;
    vector<int> a(n);

    srand(time(NULL));

    while (true) {
        for (int i = 0; i < n; i++) {
            a[i] = rand() % max_num + 1;
        }

        string smart, dumb;
        for (int i = 0; i < 40; i++) {
            cout << "#";
        }
        cout << endl << "Test case: ";
        for (const auto &n : a) {
            cout << n << ' ';
        }
        cout << endl;
        smart = greatest_num(a);
        dumb = greatest_num_dumb(a);
        if (smart == dumb) {
            cout << "OK" << endl;
            for (int i = 0; i < 40; i++) {
                cout << "#";
            }
            cout << endl << endl;
        }
        else {
            cout << "WRONG ANSWER" << endl;
            cout << "Expected result: " << dumb << endl;
            cout << "Obtained result: " << smart << endl;
            for (int i = 0; i < 40; i++) {
                cout << "#";
            }
            cout << endl << endl;
            break;
        }
    }
}
*/

int main(int argc, char *argv[])
{
    // stress_test();

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    string num = greatest_num(a);
    cout << num << endl;

    return 0;
}