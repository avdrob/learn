#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
	map<vector<string>, int> buses;
	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		int n;
		vector<string> route;
		cin >> n;

		for (int j = 0; j < n; j++) {
			string stop;
			cin >> stop;
			route.push_back(stop);
		}

		if (buses.count(route) == 1)
			cout << "Already exists for " << buses[route] << endl;
		else {
			int num = buses.size() + 1;
			buses[route] = num;
			cout << "New bus " << num << endl;
		}
	}

	return 0;
}
