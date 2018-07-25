#include <iostream>

using namespace std;

int main()
{
	double N, A, B, X, Y;
	double res;

	cin >> N >> A >> B >> X >> Y;
	res = N;

	if (N > A)
		res = N * (100 - X) / 100.0;
	if (N > B)
		res = N * (100 - Y) / 100.0;

	cout << res << endl;
	return 0;
}
