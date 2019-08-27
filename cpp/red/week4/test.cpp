#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int main()
{
    string s = "ab";
    string_view sv = s;

    sv.remove_prefix(sv.size());
    cout << sv << endl;
}