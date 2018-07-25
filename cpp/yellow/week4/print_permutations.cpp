#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	unsigned N;
	vector<unsigned> v;

	cin >> N;
	for (auto i = 1; i <= N; i++)
		v.push_back(i);

	reverse(v.begin(), v.end());
	do {
		for (const auto &i : v)
			cout << i << ' ';
		cout << endl;
	} while(prev_permutation(v.begin(), v.end()));

	return 0;

}
