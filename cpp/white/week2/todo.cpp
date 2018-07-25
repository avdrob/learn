#include <vector>
#include <iostream>
#include <string>

using namespace std;

const vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
	int q, cm;
	vector<vector<string>> jobs(31);
	cin >> q;

	cm = 0;
	for (int j = 0; j < q; j++) {
		int i;
		string cmd, s;

		cin >> cmd;
		if (cmd == "ADD") {
			cin >> i >> s;
			jobs[i-1].push_back(s);
			continue;
		}
		if (cmd == "NEXT") {
			int nm = cm + 1;
			if (nm >= days.size())
				nm = 0;

			if (days[nm] >= days[cm]) {
				cm = nm;
				jobs.resize(days[nm]);
			}
			else for (int d = days[nm]; d < days[cm]; d++) {
				jobs[days[nm]-1].insert(end(jobs[days[nm]-1]),
					begin(jobs[d]), end(jobs[d]));
			}
			cm = nm;
			jobs.resize(days[nm]);
			continue;
		}
		if (cmd == "DUMP") {
			cin >> i;
			cout << jobs[i-1].size() << ' ';
			for (int k = 0; k < jobs[i-1].size(); k++)
				cout << jobs[i-1][k] << ' ';
			cout << endl;
			continue;
		}
	}

	return 0;
}
