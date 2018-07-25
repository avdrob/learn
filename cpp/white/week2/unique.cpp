#include <string>
#include <iostream>
#include <set>

using namespace std;

int main()
{
	int n;
	cin >> n;

	set<string> s;
	for (int i; i < n; i++) {
		string buf;
		cin >> buf;
		s.insert(buf);
	}

	cout << s.size() << endl;

	return 0;
}
