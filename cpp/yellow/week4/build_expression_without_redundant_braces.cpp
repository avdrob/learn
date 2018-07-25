#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <deque>

using namespace std;

inline bool is_strong(string op)
{
	return (op == "*" || op == "/");
}

inline bool is_weak(string op)
{
	return (op == "+" || op == "-");
}

int main()
{
	int x, N;
	deque<string> expr;
	string new_op, old_op;

	cin >> x >> N;
	expr.push_back(to_string(x));;

	old_op = "*";
	for (int i = 0; i < N; i++) {
		int num;

		cin >> ws >> new_op >> ws >> num;
		if (is_strong(new_op) && is_weak(old_op)) {
			expr.push_front("(");
			expr.push_back(")");
		}

		expr.push_back(" " + new_op + " ");
		expr.push_back(to_string(num));

		old_op = new_op;
	}

	for (auto s : expr)
		cout << s;

	return 0;
}
