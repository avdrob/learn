#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	vector<int> b;

	cin >> n;
	while (n > 0) {
		if (n % 2 == 1)
			b.push_back(1);
		else
			b.push_back(0);
		n >>= 1;
	}

	for (int i = b.size()-1; i >= 0; i--)
		cout << b[i];

	cout << endl;
	return 0;
}
