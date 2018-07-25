#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> v(n);

	for (int i = 0; i < n; i++)
		cin >> v[i];

	sort(begin(v), end(v), [](int i, int j) {return abs(i) < abs(j);});

	for (int i = 0; i < v.size(); i++)
		cout << v[i] << ' ';
	cout << endl;

	return 0;
}
