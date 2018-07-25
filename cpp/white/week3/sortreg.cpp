#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string lowcase(const string& s)
{
	string res = s;

	for (char& c : res)
		c = tolower(c);

	return res;
}

int main()
{
	int n;
	cin >> n;

	vector<string> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	sort(begin(v), end(v), [](string s1, string s2) {
			return lowcase(s1) < lowcase(s2);
		});

	for (const string& s : v)
		cout << s << ' ';
	cout << endl;

	return 0;
}
