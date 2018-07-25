#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	double a, b, c;

	cin >> a >> b >> c;

	if (c == 0) {
		cout << 0 << ' ';
		if (a != 0)
			cout << -b / a;
		return 0;
	}

	if (a == 0) {
		if (b != 0)
			cout << -c / b;
		return 0;
	}

	double D = b * b - 4 * a * c;
	if (D < 0)
		return 0;
	if (D == 0) {
		cout << (-b + sqrt(D)) / (2 * a);
		return 0;
	}

	cout << (-b + sqrt(D)) / (2 * a) << ' ' <<
		(-b - sqrt(D)) / (2 * a);
	return 0;
}
