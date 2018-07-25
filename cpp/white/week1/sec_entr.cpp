#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s;
	bool fst, sec;
	int i;

	cin >> s;
	fst = sec = false;

	for (i = 0; i < s.size(); i++) {
		if (s[i] == 'f')
			if (!fst) {
				fst = true;
				continue;
			}
			else {
				sec = true;
				break;
			}
	}

	if (sec)
		cout << i << endl;
	else if (fst)
		cout << -1 << endl;
	else
		cout << -2;

	return 0;
}
