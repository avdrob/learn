#include <vector>
#include <iostream>

using namespace std;

int worried_cnt(const vector<bool>& v)
{
	int res = 0;

	for (auto p : v)
		if (p == true)
			res++;

	return res;
}

int main()
{
	int q;
	cin >> q;
	vector<bool> v;

	for (int i = 0; i < q; i++) {
		int j, k;
		string cmd;
		cin >> cmd;

		if (cmd == "WORRY") {
			cin >> j;
			v[j] = true;
			continue;
		}
		if (cmd == "QUIET") {
			cin >> j;
			v[j] = false;
			continue;
		}
		if (cmd == "COME") {
			cin >> k;
			if (k > 0)
				v.resize(v.size() + k, false);
			else
				v.resize(v.size() + k);
			continue;
		}
		if (cmd == "WORRY_COUNT") {
			cout << worried_cnt(v) << endl;
			continue;
		}
	}

	return 0;
}
