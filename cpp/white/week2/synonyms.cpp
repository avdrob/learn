#include <set>
#include <string>
#include <map>
#include <iostream>

using namespace std;

int main()
{
	int q;
	map<string, set<string>> synonyms;
	cin >> q;

	for (int i = 0; i < q; i++) {
		string cmd;
		cin >> cmd;

		if (cmd == "ADD") {
			string w1, w2;
			cin >> w1 >> w2;
			synonyms[w1].insert(w2);
			synonyms[w2].insert(w1);
			continue;
		}

		if (cmd == "COUNT") {
			string w;
			cin >> w;
			cout << synonyms[w].size() << endl;
			continue;
		}

		if (cmd == "CHECK") {
			string w1, w2;
			cin >> w1 >> w2;
			if (synonyms[w1].count(w2) > 0)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
			continue;
		}
	}

	return 0;
}
