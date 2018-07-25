#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <deque>

using namespace std;

int main()
{
	int x, N;
	deque<string> expr;

	cin >> x >> N;
	expr = {to_string(x)};

	for (int i = 0; i < N; i++) {
		char op;
		int num;

		cin >> ws >> op >> ws >> num;
		expr.push_front("(");
		expr.push_back(")");
		expr.push_back(" " + string(1, op) + " ");
		expr.push_back(to_string(num));
	}

	for (auto s : expr)
		cout << s;
	cout << endl;

	return 0;
}
